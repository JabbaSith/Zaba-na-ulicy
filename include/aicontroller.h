#pragma once

/**
 * @file aicontroller.h
 * @brief Kontroler AI uczący się metodą Q-learning (tabela Q).
 *
 * Stan gry kodowany jest jako:
 *   state = playerRow * 16 + dangerBits
 * gdzie:
 *   - playerRow   – numer rzędu żaby (0..ROWS-1), rząd 0 = META (cel)
 *   - dangerBits  – 4 bity (Up,Down,Left,Right), bit=1 oznacza że ruch
 *                   w tym kierunku zakończy się kolizją z autem w TYM ticku
 *
 * Akcje: Up, Down, Left, Right (0..3).
 *
 * Nagrody (przyznawane przez GameWindow, patrz gamewindow.cpp):
 *   +1   – ruch zmniejszający rząd (bliżej mety)
 *   -1   – ruch Down (oddala od mety)
 *    0   – ruch Left/Right lub ruch zablokowany granicą sceny
 *   +50  – dodatkowy bonus gdy żaba dotrze do mety
 *   -100 – żaba zginęła (kolizja)
 *
 * Tabela Q jest zapisywana/wczytywana z pliku tekstowego "qtable.txt"
 * w katalogu roboczym, dzięki czemu uczenie jest kumulatywne między
 * uruchomieniami trybu "Trening AI".
 */

#include <QObject>
#include <QString>
#include <array>
#include <vector>
#include <memory>
#include "gamedefs.h"
#include "player.h"
#include "lane.h"

class AIController : public QObject {
    Q_OBJECT
public:
    explicit AIController(QObject *parent = nullptr);
    ~AIController() override;

    /// Liczba rzędów planszy (SCENE_HEIGHT / PLAYER_STEP, zaokrąglone w górę).
    static constexpr int ROWS         = 17;
    /// 4 bity zagrożenia (Up,Down,Left,Right) => 16 kombinacji.
    static constexpr int DANGER_COUNT = 16;
    /// Łączna liczba stanów.
    static constexpr int STATE_COUNT  = ROWS * DANGER_COUNT;
    /// Liczba możliwych akcji.
    static constexpr int ACTION_COUNT = 4;

    /**
     * @brief Wybiera kierunek ruchu (epsilon-greedy na podstawie tabeli Q).
     */
    Direction decideMove(const Player &player,
                         const std::vector<std::unique_ptr<Lane>> &lanes);

    /**
     * @brief Aktualizuje tabelę Q wg reguły Q-learning:
     *        Q(s,a) += alpha * (reward + gamma * max_a' Q(s',a') - Q(s,a))
     * @param prevState  Stan przed akcją.
     * @param nextState  Stan po akcji (ignorowany jeśli @p done == true).
     * @param action     Wykonana akcja.
     * @param reward     Otrzymana nagroda.
     * @param done       Czy epizod się zakończył (kolizja).
     */
    void train(int prevState, int nextState, Direction action, float reward, bool done);

    /// Zwraca zakodowany stan na podstawie aktualnej sytuacji w grze.
    int getState(const Player &player,
                  const std::vector<std::unique_ptr<Lane>> &lanes) const;

    /// Czy ruch w danym kierunku zakończy się kolizją w tym ticku.
    bool isDanger(const Player &player,
                   const std::vector<std::unique_ptr<Lane>> &lanes,
                   Direction dir) const;

    int   getStepCount()    const;
    float getTotalReward()  const;
    int   getEpisodeCount() const;

    /// Resetuje liczniki epizodu (wywoływane przy starcie nowej gry AI).
    void resetEpisode();

    /// Konwersja kierunek <-> indeks akcji.
    static int       actionToIndex(Direction d);
    static Direction indexToAction(int idx);

private:
    void loadQTable();
    void saveQTable() const;

    std::array<std::array<float, ACTION_COUNT>, STATE_COUNT> m_q;

    float m_alpha;   ///< Współczynnik uczenia.
    float m_gamma;   ///< Współczynnik dyskontowania nagród przyszłych.
    float m_epsilon; ///< Prawdopodobieństwo eksploracji (ruch losowy).

    int   m_stepCount;
    int   m_episodeCount;
    float m_totalReward;

    QString m_qtablePath;
};
