/**
 * @file gamewindow.cpp
 *
 * ┌─────────────────────────────────────────────────────────────────────────┐
 * │  JAK PODŁĄCZYĆ QT DESIGNER – instrukcja w 3 krokach                    │
 * │                                                                         │
 * │  1. Stwórz ui/gamewindow.ui wg poradnik_qt_designer.html               │
 * │     (objectNames: scoreLabel, stackedWidget, gameView)                 │
 * │     Strona 0 stacka = menu (pusta), strona 1 = gameView               │
 * │                                                                         │
 * │  2. W gamewindow.h:                                                     │
 * │     - odkomentuj: #include "ui_gamewindow.h"                           │
 * │     - odkomentuj: Ui::GameWindow *ui;                                  │
 * │     - usuń:       m_stack, m_scoreLabel, m_gameView                   │
 * │                                                                         │
 * │  3. W tym pliku:                                                        │
 * │     - usuń blok "=== TYMCZASOWY KOD ==="                               │
 * │     - odkomentuj blok "=== DESIGNER ==="                               │
 * │     - w onGameOver() i onScoreUpdated() zamień m_scoreLabel → ui->scoreLabel │
 * │     - w setupGameView() zamień m_gameView/m_stack → ui->gameView/ui->stackedWidget │
 * └─────────────────────────────────────────────────────────────────────────┘
 */

#include "gamewindow.h"
#include "ui/ui/ui_gamewindow.h"
#include <QKeyEvent>
#include <QVBoxLayout>
#include <QTimer>
#include <QFrame>
#include <QDebug>

// ════════════════════════════════════════════════════════════════════════════
//  === DESIGNER === odkomentuj po stworzeniu ui/gamewindow.ui
// ════════════════════════════════════════════════════════════════════════════

GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GameWindow)
    , m_gameMode(GameMode::PlayerControlled)
{
    ui->setupUi(this);        // ← buduje cały UI z pliku .ui
    setFixedSize(SCENE_WIDTH, SCENE_HEIGHT + 30);

    initLogic();

    // Scena podpięta pod gameView z Designer
    m_scene = new QGraphicsScene(0, 0, SCENE_WIDTH, SCENE_HEIGHT, this);
    ui->gameView->setScene(m_scene);
    ui->gameView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->gameView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->gameView->setFrameShape(QFrame::NoFrame);

    // MenuScreen wstawiamy do strony 0 stacka
    m_menu = new MenuScreen(m_audio.get(), this);
    ui->stackedWidget->insertWidget(0, m_menu);

    connectMenuSignals();
    showMenu();
}

GameWindow::~GameWindow() { delete ui; }

// ════════════════════════════════════════════════════════════════════════════


// ════════════════════════════════════════════════════════════════════════════
//  === TYMCZASOWY KOD === usuń po podłączeniu Designer

// ════════════════════════════════════════════════════════════════════════════


// ── Wspólna inicjalizacja logiki (niezależna od trybu UI) ────────────────────
void GameWindow::initLogic() {
    m_audio       = std::make_unique<AudioManager>(this);
    m_skinManager = std::make_unique<SkinManager>(this);
}

void GameWindow::connectMenuSignals() {
    connect(m_menu, &MenuScreen::modeSelected,
            this,   &GameWindow::onModeSelected);
}

// ── Nawigacja ────────────────────────────────────────────────────────────────
void GameWindow::showMenu() {
    // Działa zarówno z Designer (ui->stackedWidget) jak i bez
    // Po podłączeniu .ui zmień m_stack → ui->stackedWidget
    ui->stackedWidget->setCurrentIndex(0);
    m_audio->playMenuMusic();
}

void GameWindow::showGame() {
    m_game = std::make_unique<Game>(m_scene, m_skinManager.get(), this);
    connect(m_game.get(), &Game::gameOver,     this, &GameWindow::onGameOver);
    connect(m_game.get(), &Game::scoreUpdated, this, &GameWindow::onScoreUpdated);

    if (m_gameMode == GameMode::AITraining) {
        m_aiController = std::make_unique<AIController>(this);
        qDebug() << "[GameWindow] Tryb AI – stub aktywny";
    } else {
        m_aiController.reset();
    }

    // Po podłączeniu .ui zmień m_stack → ui->stackedWidget
    ui->stackedWidget->setCurrentIndex(1);
    m_audio->playGameMusic();
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
    // Po podłączeniu .ui zmień m_scoreLabel → ui->scoreLabel
    ui->scoreLabel->setText(
        QString("KONIEC GRY!   Wynik: %1   |   Rekord: %2").arg(cur).arg(hi));
    QTimer::singleShot(2000, this, &GameWindow::showMenu);
}

void GameWindow::onScoreUpdated(int score) {
    int hi = m_game ? m_game->getScore()->getHighScore() : 0;
    // Po podłączeniu .ui zmień m_scoreLabel → ui->scoreLabel
  ui->scoreLabel->setText(
        QString("Wynik: %1   |   Rekord: %2").arg(score).arg(hi));
    if (m_skinManager) m_skinManager->tryUnlock(score);
}
