#pragma once

/**
 * @file lane.h
 * @brief Pas ruchu – generuje i zarządza samochodami.
 */

#include <QObject>
#include <QGraphicsScene>
#include <vector>
#include <memory>
#include "car.h"

/**
 * @class Lane
 * @brief Jeden pas ruchu na planszy.
 *
 * Kierunek: pasy parzyste (0,2,4) → prawo; nieparzyste (1,3,5) → lewo.
 * Spawn oparty na odległości – nowe auto pojawi się gdy poprzednie
 * odjechało co najmniej MIN_GAP od krawędzi wjazdu.
 */
class Lane : public QObject {
    Q_OBJECT
public:
    explicit Lane(int laneIndex, QObject *parent = nullptr);

    void update();
    void spawnCar();
    void draw(QGraphicsScene *scene) const;
    void clear();

    const std::vector<std::unique_ptr<Car>>& getCars() const;

private:
    bool canSpawn() const;

    int  m_laneIndex;
    int  m_spawnTimer;
    int  m_spawnInterval;
    std::vector<std::unique_ptr<Car>> m_cars;
};
