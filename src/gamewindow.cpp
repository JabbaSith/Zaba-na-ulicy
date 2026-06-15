/**
 * @file gamewindow.cpp
 */

#include "gamewindow.h"
#include "ui/ui/ui_gamewindow.h"
#include <QKeyEvent>
#include <QVBoxLayout>
#include <QTimer>
#include <QFrame>
#include <QDebug>


GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GameWindow)
    , m_gameMode(GameMode::PlayerControlled)
    , m_won(false)
    , m_aiHasPrevState(false)
    , m_aiPrevState(0)
    , m_aiPrevAction(Direction::Up)
{
    ui->setupUi(this);        // ← buduje cały UI z pliku .ui
    resize(SCENE_WIDTH, SCENE_HEIGHT + 60);
    setMinimumSize(400,300);

    initLogic();

    // Scena podpięta pod gameView z Designer
    m_scene = new QGraphicsScene(0, 0, SCENE_WIDTH, SCENE_HEIGHT, this);
    ui->gameView->setScene(m_scene);
    ui->gameView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->gameView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->gameView->setFrameShape(QFrame::NoFrame);

    ui->gameView->setFocusPolicy(Qt::NoFocus);
    setFocusPolicy(Qt::StrongFocus);

    // MenuScreen wstawiamy do strony 0 stacka
    m_menu = new MenuScreen(m_audio.get(), m_skinManager.get(), this);
    ui->stackedWidget->insertWidget(0, m_menu);

    connectMenuSignals();
    showMenu();
    setFocus();
}

GameWindow::~GameWindow() { delete ui; }

// ── Wspólna inicjalizacja logiki (niezależna od trybu UI) ────────────────────
void GameWindow::initLogic() {
    m_audio        = std::make_unique<AudioManager>(nullptr);
    m_skinManager  = std::make_unique<SkinManager>(nullptr);
    m_aiController = std::make_unique<AIController>(nullptr);
}

void GameWindow::connectMenuSignals() {
    connect(m_menu, &MenuScreen::modeSelected,
            this,   &GameWindow::onModeSelected);
}

// ── Nawigacja ────────────────────────────────────────────────────────────────
void GameWindow::showMenu() {
    m_menu->refreshSkinButton();
    ui->scoreLabel->setText("");   // wyczyść komunikat końca gry
    ui->stackedWidget->setCurrentIndex(0);
    m_audio->playMenuMusic();
}

void GameWindow::showGame() {
    m_game = std::make_unique<Game>(m_scene, m_skinManager.get(), nullptr);
    connect(m_game.get(), &Game::gameOver,     this, &GameWindow::onGameOver);
    connect(m_game.get(), &Game::scoreUpdated, this, &GameWindow::onScoreUpdated);
    connect(m_game.get(), &Game::playerDied,   this, &GameWindow::onPlayerDied);
    connect(m_game.get(), &Game::goalReached,  this, &GameWindow::onGoalReached);

    m_aiHasPrevState = false;
    m_won = false;

    if (m_gameMode == GameMode::AITraining) {
        m_aiController->resetEpisode();
        m_game->setTickInterval(AI_TICK_MS);
        connect(m_game.get(), &Game::tickReady, this, &GameWindow::onAiTick);
        m_game->warmup(AI_WARMUP_TICKS);
        qDebug() << "[GameWindow] Tryb AI – Q-learning aktywny (epizod"
                 << m_aiController->getEpisodeCount() << "), mapa rozgrzana.";
    }

    ui->stackedWidget->setCurrentIndex(1);
    m_audio->playGameMusic();
    setFocus();
    m_game->startGame();
}

// ── Klawiatura ───────────────────────────────────────────────────────────────
void GameWindow::keyPressEvent(QKeyEvent *event) {
    if (!m_game || !m_game->isRunning()) return;
    Direction dir = Direction::None;
    switch (event->key()) {
        case Qt::Key_Up:    dir = Direction::Up;    break;
        case Qt::Key_Down:  dir = Direction::Down;  break;
        case Qt::Key_Left:  dir = Direction::Left;  break;
        case Qt::Key_Right: dir = Direction::Right; break;
        case Qt::Key_Escape:
            m_game->endGame();
            showMenu();
            setFocus();
            return;
        default: break;
    }
    if (dir != Direction::None && m_gameMode == GameMode::PlayerControlled)
        m_game->handleInput(dir);
}

// ── Sloty ────────────────────────────────────────────────────────────────────
void GameWindow::onModeSelected(GameMode mode) {
    m_gameMode = mode;
    showGame();
}

void GameWindow::onGameOver() {
    int cur = m_game->getScore()->getCurrentScore();
    int hi  = m_game->getScore()->getHighScore();

    QString msg = m_won
        ? QString("WYGRANA! Żaba przeszła ulicę!   Wynik: %1   |   Rekord: %2")
        : QString("KONIEC GRY!   Wynik: %1   |   Rekord: %2");

    // Po podłączeniu .ui zmień m_scoreLabel → ui->scoreLabel
    ui->scoreLabel->setText(msg.arg(cur).arg(hi));
    QTimer::singleShot(2000, this, &GameWindow::showMenu);
}

// ── Kolizja ─────────────────────────────────────────────────────────────────
void GameWindow::onPlayerDied() {
    if (m_gameMode == GameMode::AITraining) {
        // Tryb AI: kolizja kończy epizod Q-learning (kara), ale gra
        // NIE kończy się – żaba startuje od nowa i próbuje dalej.
        if (m_aiHasPrevState) {
            m_aiController->train(m_aiPrevState, /*nextState=*/0, m_aiPrevAction,
                                   /*reward=*/-100.0f, /*done=*/true);
            m_aiHasPrevState = false;
            qDebug() << "[AI] Epizod" << m_aiController->getEpisodeCount()
                     << "zakończony (kolizja). Suma nagród:" << m_aiController->getTotalReward()
                     << "kroki:" << m_aiController->getStepCount();
        }
        m_game->resetPlayer();
        // Krótka rozgrzewka po restarcie – auta zdążą wjechać na pasy
        // zanim AI podejmie pierwszą decyzję w nowym epizodzie.
        m_game->warmup(AI_WARMUP_TICKS / 2);
    } else {
        // Tryb gracza: kolizja = koniec gry (przegrana).
        m_won = false;
        m_game->endGame();
    }
}

// ── Meta ────────────────────────────────────────────────────────────────────
void GameWindow::onGoalReached() {
    if (m_gameMode == GameMode::AITraining && m_aiHasPrevState) {
        // Sukces – duża nagroda, koniec epizodu.
        m_aiController->train(m_aiPrevState, /*nextState=*/0, m_aiPrevAction,
                               /*reward=*/100.0f, /*done=*/true);
        m_aiHasPrevState = false;
        qDebug() << "[AI] Epizod" << m_aiController->getEpisodeCount()
                 << "zakończony (META!). Suma nagród:" << m_aiController->getTotalReward()
                 << "kroki:" << m_aiController->getStepCount();
    }

    // Dotarcie do mety zawsze kończy bieżącą rundę (oba tryby) – powrót do menu.
    m_won = true;
    m_game->endGame();
}

void GameWindow::onScoreUpdated(int score) {
    int hi = m_game ? m_game->getScore()->getHighScore() : 0;
  ui->scoreLabel->setText(
        QString("Wynik: %1   |   Rekord: %2").arg(score).arg(hi));
    if (m_skinManager) m_skinManager->tryUnlock(score);
}

// ── AI: jeden krok Q-learning na każdy tick gry ───────────────────────────────
void GameWindow::onAiTick() {
    if (!m_game) return;

    Player &player = *m_game->getPlayer();
    const auto &lanes = m_game->getLanes();

    int currentState = m_aiController->getState(player, lanes);

    // Wytrenuj poprzedni krok na podstawie tego, co się stało w tym ticku
    // (zmiana rzędu = nowy stan; kolizja jest obsłużona w onGameOver).
    if (m_aiHasPrevState) {
        int prevRow = m_aiPrevState / AIController::DANGER_COUNT;
        int newRow  = currentState  / AIController::DANGER_COUNT;

        float reward;
        if (newRow < prevRow)      reward = 1.0f;   // bliżej mety
        else if (newRow > prevRow) reward = -1.0f;  // dalej od mety
        else                       reward = 0.0f;   // ruch w bok / blokada

        m_aiController->train(m_aiPrevState, currentState, m_aiPrevAction, reward, false);
    }

    Direction action = m_aiController->decideMove(player, lanes);
    m_game->handleInput(action);

    if (!m_game->isRunning()) {
        m_aiHasPrevState = false;
        return;
    }

    m_aiPrevState   = currentState;
    m_aiPrevAction  = action;
    m_aiHasPrevState = true;
}
