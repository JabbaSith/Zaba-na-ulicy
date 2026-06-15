/**
 * @file scoremanager.cpp
 */

#include "scoremanager.h"
#include <QFile>
#include <QTextStream>

const QString ScoreManager::kHighScorePath = "highscore.txt";

ScoreManager::ScoreManager(QObject *parent)
    : QObject(parent), m_currentScore(0), m_highScore(0)
{
    loadHighScore();
}

void ScoreManager::addPoints(int amount) {
    m_currentScore += amount;
    if (m_currentScore > m_highScore) {
        m_highScore = m_currentScore;
        saveHighScore();
    }
    emit scoreChanged(m_currentScore);
}

void ScoreManager::updateHighScore(int score) {
    if (score > m_highScore) {
        m_highScore = score;
        saveHighScore();
    }
}

void ScoreManager::reset() {
    m_currentScore = 0;
    emit scoreChanged(0);
}

int ScoreManager::getCurrentScore() const { return m_currentScore; }
int ScoreManager::getHighScore()    const { return m_highScore; }

void ScoreManager::loadHighScore() {
    QFile file(kHighScorePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;
    QTextStream in(&file);
    int value = 0;
    in >> value;
    if (value > 0) m_highScore = value;
}

void ScoreManager::saveHighScore() const {
    QFile file(kHighScorePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) return;
    QTextStream out(&file);
    out << m_highScore;
}
