/**
 * @file scoremanager.cpp
 */

#include "scoremanager.h"

ScoreManager::ScoreManager(QObject *parent)
    : QObject(parent), m_currentScore(0), m_highScore(0)
{}

void ScoreManager::addPoints(int amount) {
    m_currentScore += amount;
    if (m_currentScore > m_highScore)
        m_highScore = m_currentScore;
    emit scoreChanged(m_currentScore);
}

void ScoreManager::reset() {
    m_currentScore = 0;
    emit scoreChanged(0);
}

int ScoreManager::getCurrentScore() const { return m_currentScore; }
int ScoreManager::getHighScore()    const { return m_highScore; }
