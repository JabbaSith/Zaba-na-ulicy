/**
 * @file aicontroller.cpp
 * @brief Implementacja AI sterującego żabą metodą Q-learning.
 */

#include "aicontroller.h"
#include "gamedefs.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <cstdlib>
#include <algorithm>

AIController::AIController(QObject *parent)
    : QObject(parent)
    , m_alpha(0.2f)
    , m_gamma(0.9f)
    , m_epsilon(AI_EPSILON_INITIAL)
    , m_stepCount(0)
    , m_episodeCount(0)
    , m_totalReward(0.0f)
    , m_qtablePath("qtable.txt")
{
    for (auto &row : m_q)
        row.fill(0.0f);

    loadQTable();
}

AIController::~AIController() {
    saveQTable();
}

// ── Akcje <-> indeksy ─────────────────────────────────────────────────────────
int AIController::actionToIndex(Direction d) {
    switch (d) {
        case Direction::Up:    return 0;
        case Direction::Down:  return 1;
        case Direction::Left:  return 2;
        case Direction::Right: return 3;
        default:               return 0;
    }
}

Direction AIController::indexToAction(int idx) {
    switch (idx) {
        case 0: return Direction::Up;
        case 1: return Direction::Down;
        case 2: return Direction::Left;
        case 3: return Direction::Right;
        default: return Direction::Up;
    }
}

// ── Detekcja zagrożenia ───────────────────────────────────────────────────────
bool AIController::isDanger(const Player &player,
                              const std::vector<std::unique_ptr<Lane>> &lanes,
                              Direction dir) const
{
    int x = player.getX();
    int y = player.getY();

    switch (dir) {
        case Direction::Up:    y -= PLAYER_STEP; break;
        case Direction::Down:  y += PLAYER_STEP; break;
        case Direction::Left:  x -= PLAYER_STEP; break;
        case Direction::Right: x += PLAYER_STEP; break;
        default: break;
    }

    x = std::clamp(x, 0, SCENE_WIDTH  - PLAYER_SIZE);
    y = std::clamp(y, 0, SCENE_HEIGHT - PLAYER_SIZE);

    QRect next(x, y, PLAYER_SIZE, PLAYER_SIZE);

    for (const auto &lane : lanes) {
        for (const auto &car : lane->getCars()) {
            if (next.intersects(car->getBoundingRect()))
                return true;
        }
    }
    return false;
}

// ── Kodowanie stanu ───────────────────────────────────────────────────────────
int AIController::getState(const Player &player,
                            const std::vector<std::unique_ptr<Lane>> &lanes) const
{
    int row = player.getY() / PLAYER_STEP;
    row = std::clamp(row, 0, ROWS - 1);

    int danger = 0;
    if (isDanger(player, lanes, Direction::Up))    danger |= 0b1000;
    if (isDanger(player, lanes, Direction::Down))  danger |= 0b0100;
    if (isDanger(player, lanes, Direction::Left))  danger |= 0b0010;
    if (isDanger(player, lanes, Direction::Right)) danger |= 0b0001;

    return row * DANGER_COUNT + danger;
}

// ── Wybór akcji (epsilon-greedy) ───────────────────────────────────────────────
Direction AIController::decideMove(const Player &player,
                                    const std::vector<std::unique_ptr<Lane>> &lanes)
{
    int state = getState(player, lanes);
    ++m_stepCount;

    // Eksploracja
    if ((static_cast<float>(std::rand()) / RAND_MAX) < m_epsilon) {
        int idx = std::rand() % ACTION_COUNT;
        return indexToAction(idx);
    }

    // Eksploatacja – wybierz akcję z najwyższą wartością Q
    const auto &row = m_q[state];
    int best = 0;
    for (int i = 1; i < ACTION_COUNT; ++i)
        if (row[i] > row[best]) best = i;

    return indexToAction(best);
}

// ── Aktualizacja Q ────────────────────────────────────────────────────────────
void AIController::train(int prevState, int nextState, Direction action, float reward, bool done)
{
    int a = actionToIndex(action);
    float maxNext = 0.0f;
    if (!done) {
        maxNext = m_q[nextState][0];
        for (int i = 1; i < ACTION_COUNT; ++i)
            maxNext = std::max(maxNext, m_q[nextState][i]);
    }

    float &q = m_q[prevState][a];
    q += m_alpha * (reward + m_gamma * maxNext - q);

    m_totalReward += reward;

    if (done) ++m_episodeCount;
}

// ── Gettery / reset ──────────────────────────────────────────────────────────
int   AIController::getStepCount()    const { return m_stepCount; }
float AIController::getTotalReward()  const { return m_totalReward; }
int   AIController::getEpisodeCount() const { return m_episodeCount; }

void AIController::resetEpisode() {
    m_stepCount   = 0;
    m_totalReward = 0.0f;
}

// ── Zapis / wczytanie tabeli Q (prosty format tekstowy) ────────────────────────
void AIController::loadQTable() {
    QFile file(m_qtablePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;

    QTextStream in(&file);
    int state = 0;
    while (!in.atEnd() && state < STATE_COUNT) {
        QString line = in.readLine();
        QStringList parts = line.split(' ', Qt::SkipEmptyParts);
        if (parts.size() != ACTION_COUNT) continue;
        for (int a = 0; a < ACTION_COUNT; ++a)
            m_q[state][a] = parts[a].toFloat();
        ++state;
    }
    qDebug() << "[AIController] Wczytano tabelę Q z" << m_qtablePath
             << "(" << state << "stanów)";
}

void AIController::saveQTable() const {
    QFile file(m_qtablePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "[AIController] Nie udało się zapisać tabeli Q";
        return;
    }
    QTextStream out(&file);
    for (const auto &row : m_q) {
        for (int a = 0; a < ACTION_COUNT; ++a) {
            out << row[a];
            if (a != ACTION_COUNT - 1) out << ' ';
        }
        out << '\n';
    }
    qDebug() << "[AIController] Zapisano tabelę Q do" << m_qtablePath;
}
