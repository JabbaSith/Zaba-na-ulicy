#pragma once

/**
 * @file car.h
 * @brief Abstrakcyjna klasa bazowa dla pojazdów.
 */

#include <QObject>
#include <QRect>
#include <QGraphicsScene>
#include <QString>

/**
 * @class Car
 * @brief Pojazd poruszający się po jednym pasie ruchu.
 *
 * Klasy pochodne (SmallCar, Truck, SUV) implementują move() i getType().
 * Gdy pojazd wyjdzie poza krawędź sceny, wraca z przeciwnej strony.
 */
class Car : public QObject {
    Q_OBJECT
public:
    Car(float x, float y, float speed, int laneIndex, int w, int h,
        QObject *parent = nullptr);
    virtual ~Car() = default;

    /** @brief Przesuwa pojazd o jeden krok (zawija na krawędziach). */
    virtual void move() = 0;

    /** @brief Prostokąt kolizji. */
    virtual QRect getBoundingRect() const = 0;

    /** @brief Nazwa typu ("SmallCar" / "Truck" / "SUV"). */
    virtual QString getType() const = 0;

    /** @brief Rysuje pojazd – placeholder kolorowy prostokąt. */
    virtual void draw(QGraphicsScene *scene) const;

    float getX()        const;
    float getY()        const;
    int   getLaneIndex() const;

protected:
    float m_x, m_y;
    float m_speed;
    int   m_laneIndex;
    int   m_width, m_height;
};
