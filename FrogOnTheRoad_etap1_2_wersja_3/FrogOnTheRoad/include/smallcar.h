#pragma once
/**
 * @file smallcar.h
 * @brief Mały, szybki samochód.
 */
#include "car.h"

/**
 * @class SmallCar
 * @brief Szybki pojazd z małym hitboxem (50x28 px).
 */
class SmallCar : public Car {
    Q_OBJECT
public:
    /**
     * @param laneIndex  Numer pasa (0-5).
     * @param startX     Startowe X (spawn point).
     * @param speed      Prędkość px/tick (+ prawo, - lewo).
     */
    explicit SmallCar(int laneIndex, float startX = 0.0f,
                      float speed = 3.5f, QObject *parent = nullptr);
    void    move()            override;
    QRect   getBoundingRect() const override;
    QString getType()         const override;
};
