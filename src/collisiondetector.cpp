/**
 * @file collisiondetector.cpp
 */

#include "collisiondetector.h"
#include "gamedefs.h"

CollisionDetector::CollisionDetector(QObject *parent) : QObject(parent) {}

bool CollisionDetector::checkCollision(
    const Player &player,
    const std::vector<std::unique_ptr<Lane>> &lanes) const
{
    // Hitboxy są pomniejszane o COLLISION_MARGIN z każdej strony, żeby
    // kolizja była wykrywana tylko gdy sprite'y realnie się przecinają
    // (a nie już przy "dotknięciu" przezroczystych krawędzi pixmapy).
    QRect playerRect = player.getBoundingRect()
                           .adjusted(COLLISION_MARGIN, COLLISION_MARGIN,
                                     -COLLISION_MARGIN, -COLLISION_MARGIN);

    for (const auto &lane : lanes) {
        for (const auto &car : lane->getCars()) {
            QRect carRect = car->getBoundingRect()
                                .adjusted(COLLISION_MARGIN, COLLISION_MARGIN,
                                          -COLLISION_MARGIN, -COLLISION_MARGIN);
            if (playerRect.intersects(carRect))
                return true;
        }
    }
    return false;
}
