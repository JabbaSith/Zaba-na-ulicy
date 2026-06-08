#pragma once

/**
 * @file scoremanager.h
 * @brief Zarządza wynikiem bieżącej gry i rekordem.
 */

#include <QObject>

/**
 * @class ScoreManager
 * @brief Przechowuje currentScore i highScore.
 *
 * Emituje sygnał scoreChanged() przy każdej zmianie punktów.
 * TODO (Etap 2): zapis/odczyt highScore z pliku.
 */
class ScoreManager : public QObject {
    Q_OBJECT
public:
    explicit ScoreManager(QObject *parent = nullptr);

    /** @brief Dodaje punkty i emituje scoreChanged. */
    void addPoints(int amount);

    /** @brief Resetuje currentScore do 0. */
    void reset();

    int getCurrentScore() const;
    int getHighScore()    const;

signals:
    /** @brief Emitowany po zmianie wyniku. */
    void scoreChanged(int newScore);

private:
    int m_currentScore;
    int m_highScore;
};
