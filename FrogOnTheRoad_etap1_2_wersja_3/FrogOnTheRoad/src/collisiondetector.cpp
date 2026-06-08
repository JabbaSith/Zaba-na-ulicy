/**
 * @file collisiondetector.cpp
 */

#include "collisiondetector.h"

CollisionDetector::CollisionDetector(QObject *parent) : QObject(parent) {}

bool CollisionDetector::checkCollision(
    const Player &player,
    const std::vector<std::unique_ptr<Lane>> &lanes) const
{
    QRect playerRect = player.getBoundingRect();
    for (const auto &lane : lanes) {
        for (const auto &car : lane->getCars()) {
            if (playerRect.intersects(car->getBoundingRect()))
                return true;
        }
    }
    return false;
}
