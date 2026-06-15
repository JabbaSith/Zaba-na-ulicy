#pragma once

/**
 * @file scoremanager.h
 * @brief Zarządza wynikiem bieżącej gry i rekordem.
 */

#include <QObject>
#include <QString>

/**
 * @class ScoreManager
 * @brief Przechowuje currentScore i highScore.
 *
 * Rekord (highScore) jest trwały między rozegranymi partiami i sesjami
 * aplikacji – zapisywany/wczytywany z pliku tekstowego (domyślnie
 * "highscore.txt" w katalogu roboczym).
 *
 * Emituje sygnał scoreChanged() przy każdej zmianie punktów.
 */
class ScoreManager : public QObject {
    Q_OBJECT
public:
    explicit ScoreManager(QObject *parent = nullptr);

    /** @brief Dodaje punkty, emituje scoreChanged i ewentualnie zapisuje nowy rekord. */
    void addPoints(int amount);

    /**
     * @brief Aktualizuje rekord jeśli @p score go pobija — bez zmiany currentScore.
     * Wywoływane co tick z wynikiem na podstawie pozycji żaby.
     */
    void updateHighScore(int score);

    /** @brief Resetuje currentScore do 0 (highScore NIE jest resetowany). */
    void reset();

    int getCurrentScore() const;
    int getHighScore()    const;

    /** @brief Wczytuje highScore z pliku (wywoływane automatycznie w konstruktorze). */
    void loadHighScore();

    /** @brief Zapisuje highScore do pliku. */
    void saveHighScore() const;

signals:
    /** @brief Emitowany po zmianie wyniku. */
    void scoreChanged(int newScore);

private:
    int m_currentScore;
    int m_highScore;

    static const QString kHighScorePath;
};
