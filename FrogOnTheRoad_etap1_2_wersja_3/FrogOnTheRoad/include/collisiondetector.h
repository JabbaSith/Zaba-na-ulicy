#pragma once

/**
 * @file collisiondetector.h
 * @brief Wykrywa kolizje żaby z pojazdami.
 */

#include <QObject>
#include <vector>
#include "player.h"
#include "lane.h"

/**
 * @class CollisionDetector
 * @brief Sprawdza przecięcie hitboxa gracza z hitboxami pojazdów.
 */
class CollisionDetector : public QObject {
    Q_OBJECT
public:
    explicit CollisionDetector(QObject *parent = nullptr);

    /**
     * @brief Sprawdza kolizję gracza z każdym pojazdem na liście pasów.
     * @param player  Gracz.
     * @param lanes   Wektor aktywnych pasów.
     * @return true jeśli nastąpiła kolizja.
     */
    bool checkCollision(const Player &player,
                        const std::vector<std::unique_ptr<Lane>> &lanes) const;
};
