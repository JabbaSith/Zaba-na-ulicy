#pragma once
/**
 * @file truck.h
 * @brief Ciężarówka – wolna, duży hitbox.
 */
#include "car.h"

/**
 * @class Truck
 * @brief Wolny pojazd z dużym hitboxem (90x40 px).
 */
class Truck : public Car {
    Q_OBJECT
public:
    explicit Truck(int laneIndex, float startX = 0.0f,
                   float speed = 1.8f, QObject *parent = nullptr);
    void    move()            override;
    QRect   getBoundingRect() const override;
    QString getType()         const override;
};
