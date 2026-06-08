/**
 * @file game.cpp
 */

#include "game.h"
#include <QGraphicsRectItem>
#include <QDebug>

// ── Kolory planszy ────────────────────────────────────────────────────────────
static const QColor COL_GRASS       { 34, 139,  34};  ///< Trawa (strefy start/meta/median)
static const QColor COL_ROAD        { 60,  60,  60};  ///< Asfalt
static const QColor COL_ROAD_LINE   {220, 220,   0};  ///< Żółta przerywana linia
static const QColor COL_ROAD_EDGE   {255, 255, 255};  ///< Biała linia krawędziowa
static const QColor COL_MEDIAN_STRIP{ 20, 100,  20};  ///< Ciemniejsza zieleń pasa środkowego

Game::Game(QGraphicsScene *scene, SkinManager *skinManager, QObject *parent)
    : QObject(parent)
    , m_scene(scene)
    , m_skinManager(skinManager)
    , m_running(false)
    , m_tick(0)
{
    m_player = std::make_unique<Player>(
        SCENE_WIDTH / 2 - PLAYER_SIZE / 2,
        START_Y, this);
    m_player->setSkin(m_skinManager->getActiveSkin());

    for (int i = 0; i < LANE_COUNT; ++i)
        m_lanes.push_back(std::make_unique<Lane>(i, this));

    m_collision = std::make_unique<CollisionDetector>(this);
    m_score     = std::make_unique<ScoreManager>(this);

    connect(&m_timer, &QTimer::timeout, this, &Game::tick);
    connect(m_score.get(), &ScoreManager::scoreChanged,
            this,           &Game::scoreUpdated);
}

void Game::startGame() { resetGame(); m_running = true; m_timer.start(GAME_TICK_MS); }

void Game::pauseGame() {
    m_running ? m_timer.stop() : m_timer.start(GAME_TICK_MS);
    m_running = !m_running;
}

void Game::endGame() { m_timer.stop(); m_running = false; emit gameOver(); }

void Game::handleInput(Direction dir) {
    if (!m_running) return;
    m_player->move(dir);
    if (m_player->getY() <= GOAL_Y) {
        m_score->addPoints(100);
        m_player->reset();
    }
}

Player*       Game::getPlayer() const { return m_player.get(); }
ScoreManager* Game::getScore()  const { return m_score.get(); }
bool          Game::isRunning() const { return m_running; }

// ── Tick ──────────────────────────────────────────────────────────────────────
void Game::tick() {
    ++m_tick;
    for (auto &lane : m_lanes) lane->update();

    if (m_collision->checkCollision(*m_player, m_lanes)) {
        m_player->setAlive(false);
        endGame();
        return;
    }
    renderFrame();
}

void Game::resetGame() {
    m_tick = 0;
    m_player->reset();
    m_player->setSkin(m_skinManager->getActiveSkin());
    for (auto &lane : m_lanes) lane->clear();
    m_score->reset();
}

// ── renderFrame ───────────────────────────────────────────────────────────────
void Game::renderFrame() {
    m_scene->clear();

    // 1. Tło – cała scena trawa (wypełnienie domyślne)
    m_scene->setBackgroundBrush(COL_GRASS);

    // 2. Górna strefa drogi (3 pasy, laneIndex 0-2)
    drawRoadSection(ROAD_TOP_Y, 3);

    // 3. Pas zieleni (median)
    auto *median = m_scene->addRect(0, MEDIAN_Y, SCENE_WIDTH, MEDIAN_HEIGHT,
                                    Qt::NoPen, COL_MEDIAN_STRIP);
    median->setZValue(0);
    // Dekoracja mediany – dwa rzędy "krzaków"
    for (int x = 20; x < SCENE_WIDTH; x += 60) {
        m_scene->addEllipse(x, MEDIAN_Y + 15, 30, 22, Qt::NoPen, QColor(10,80,10))->setZValue(1);
        m_scene->addEllipse(x + 30, MEDIAN_Y + 40, 28, 20, Qt::NoPen, QColor(15,90,15))->setZValue(1);
    }

    // 4. Dolna strefa drogi (3 pasy, laneIndex 3-5)
    drawRoadSection(ROAD_BOTTOM_Y, 3);

    // 5. Pojazdy
    for (auto &lane : m_lanes) lane->draw(m_scene);

    // 6. Gracz
    m_player->draw(m_scene, m_tick);
}

// ── drawRoadSection ───────────────────────────────────────────────────────────
/**
 * Rysuje @p count pasów asfaltu zaczynając od Y = @p topY.
 * Struktura każdego pasa:
 *   - szary prostokąt (asfalt)
 *   - biała linia na GÓRNEJ krawędzi pasa (krawędziowa)
 *   - żółta przerywana linia na Y = topY + LANE_HEIGHT/2 - 1
 *     (środek pasa, między pasami – NIE na asfalcie po którym jedzie auto)
 */
void Game::drawRoadSection(int topY, int count) {
    // Cały blok asfaltu
    m_scene->addRect(0, topY, SCENE_WIDTH, count * LANE_HEIGHT,
                     Qt::NoPen, COL_ROAD)->setZValue(0);

    // Białe linie krawędziowe (góra i dół całego bloku)
    m_scene->addRect(0, topY,                        SCENE_WIDTH, 3,
                     Qt::NoPen, COL_ROAD_EDGE)->setZValue(2);
    m_scene->addRect(0, topY + count * LANE_HEIGHT - 3, SCENE_WIDTH, 3,
                     Qt::NoPen, COL_ROAD_EDGE)->setZValue(2);

    // Żółte przerywane linie MIĘDZY pasami (nie na samym asfalcie po którym jedzie auto)
    for (int i = 1; i < count; ++i) {
        int lineY = topY + i * LANE_HEIGHT - 2;  // linia dokładnie MIĘDZY pasami
        for (int x = 0; x < SCENE_WIDTH; x += 56) {
            m_scene->addRect(x, lineY, 36, 4,
                             Qt::NoPen, COL_ROAD_LINE)->setZValue(2);
        }
    }
}
