/**
 * @file aicontroller.cpp
 * @brief Stub AI – etap 1. Zawsze idzie w górę.
 */

#include "aicontroller.h"
#include <QDebug>

AIController::AIController(QObject *parent)
    : QObject(parent), m_stepCount(0), m_totalReward(0.0f)
{}

Direction AIController::decideMove(
    const Player &player,
    const std::vector<std::unique_ptr<Lane>> &lanes)
{
    Q_UNUSED(player);
    Q_UNUSED(lanes);
    // TODO (Etap 2): Q-table lookup
    ++m_stepCount;
    return Direction::Up;
}

void AIController::train(int state, Direction action, float reward) {
    Q_UNUSED(state);
    Q_UNUSED(action);
    m_totalReward += reward;
    // TODO (Etap 2): Q-table update
}

int AIController::getState(
    const Player &player,
    const std::vector<std::unique_ptr<Lane>> &lanes) const
{
    Q_UNUSED(lanes);
    // Najprostsze kodowanie stanu: Y gracza
    return player.getY();
}
