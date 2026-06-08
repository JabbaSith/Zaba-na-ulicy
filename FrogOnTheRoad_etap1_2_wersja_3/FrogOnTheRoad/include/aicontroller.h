#pragma once

/**
 * @file aicontroller.h
 * @brief Stub kontrolera AI (Q-learning).
 *
 * W Etapie 1 AI zawsze zwraca Direction::Up (idzie do przodu).
 * TODO (Etap 2): implementacja tablicy Q i treningu.
 */

#include <QObject>
#include "gamedefs.h"
#include "player.h"
#include "lane.h"
#include <vector>
#include <memory>

/**
 * @class AIController
 * @brief Podejmuje decyzję ruchu na podstawie stanu gry.
 */
class AIController : public QObject {
    Q_OBJECT
public:
    explicit AIController(QObject *parent = nullptr);

    /**
     * @brief Wybiera kierunek ruchu dla żaby.
     * @param player  Aktualny stan gracza.
     * @param lanes   Aktywne pasy ruchu.
     * @return Wybrany kierunek.
     */
    Direction decideMove(const Player &player,
                         const std::vector<std::unique_ptr<Lane>> &lanes);

    /**
     * @brief Zapisuje wynik akcji (do późniejszego treningu Q-learning).
     * @param state   Zakodowany stan (placeholder: int).
     * @param action  Wykonana akcja.
     * @param reward  Nagroda/kara.
     */
    void train(int state, Direction action, float reward);

    /** @brief Zwraca uproszczony stan jako integer (placeholder). */
    int getState(const Player &player,
                 const std::vector<std::unique_ptr<Lane>> &lanes) const;

private:
    int   m_stepCount;   ///< Licznik kroków (do logowania)
    float m_totalReward; ///< Sumaryczna nagroda w epizodzie
};
