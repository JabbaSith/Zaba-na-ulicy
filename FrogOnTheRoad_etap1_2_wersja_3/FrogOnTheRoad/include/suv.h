#pragma once
/**
 * @file suv.h
 * @brief SUV – średnia prędkość i rozmiar.
 */
#include "car.h"

/**
 * @class SUV
 * @brief Pojazd o średnich parametrach (70x35 px).
 */
class SUV : public Car {
    Q_OBJECT
public:
    explicit SUV(int laneIndex, float startX = 0.0f,
                 float speed = 2.6f, QObject *parent = nullptr);
    void    move()            override;
    QRect   getBoundingRect() const override;
    QString getType()         const override;
};
