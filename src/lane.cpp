/**
 * @file lane.cpp
 */

#include "lane.h"
#include "smallcar.h"
#include "truck.h"
#include "suv.h"
#include "gamedefs.h"
#include <cstdlib>
#include <cmath>
#include <algorithm>

Lane::Lane(int laneIndex, QObject *parent)
    : QObject(parent)
    , m_laneIndex(laneIndex)
    , m_spawnTimer(0)
    , m_spawnInterval(0)   // nieużywane – spawn przez odległość
{}

// ── Helpers ───────────────────────────────────────────────────────────────────

/// Szerokość pojazdu danego typu (do obliczania odstępu).
static int carWidth(int type) {
    if (type == 0) return 50;   // SmallCar
    if (type == 1) return 90;   // Truck
    return 70;                  // SUV
}

// ── Czy można spawnować ────────────────────────────────────────────────────────
/**
 * Nowe auto pojawi się gdy:
 *  - pas jest pusty, LUB
 *  - ostatnie auto odjechało na odległość >= MIN_GAP od krawędzi spawnu
 *    (krawędź spawnu to lewy lub prawy brzeg sceny zależnie od kierunku).
 */
bool Lane::canSpawn() const {
    if (m_cars.empty()) return true;

    bool goRight = (m_laneIndex % 2 == 0);

    if (goRight) {
        float minX = m_cars[0]->getX();
        for (auto &c : m_cars) minX = std::min(minX, c->getX());
        return minX > (float)MIN_GAP;
    } else {
        float maxX = m_cars[0]->getX();
        for (auto &c : m_cars) maxX = std::max(maxX, c->getX());
        return maxX < (float)(SCENE_WIDTH - MIN_GAP);
    }
}

void Lane::update() {
    for (auto &car : m_cars)
        car->move();

    // Usuń auta które wyjechały całkowicie poza scenę
    m_cars.erase(
        std::remove_if(m_cars.begin(), m_cars.end(),
                       [](const std::unique_ptr<Car> &c) {
                           return c->getX() > SCENE_WIDTH + 200 ||
                                  c->getX() + 200 < -200;
                       }),
        m_cars.end());

    // Spawn jeśli warunek odległości spełniony
    if (canSpawn())
        spawnCar();
}

// ── spawnCar ──────────────────────────────────────────────────────────────────
void Lane::spawnCar() {
    bool goRight = (m_laneIndex % 2 == 0);

    int type = std::rand() % 3;
    // ═══ WSZYSTKIE AUTA – JEDNAKOWA PRĘDKOŚĆ ═══
    float speed = goRight ? CAR_SPEED : -CAR_SPEED;

    // Pozycja spawnu: poza ekranem po odpowiedniej stronie
    float startX = goRight
                       ? (float)(-carWidth(type) - 10)
                       : (float)(SCENE_WIDTH + 10);

    std::unique_ptr<Car> car;
    if (type == 0) car = std::make_unique<SmallCar>(m_laneIndex, startX, speed);
    else if (type == 1) car = std::make_unique<Truck>(m_laneIndex, startX, speed);
    else                car = std::make_unique<SUV>  (m_laneIndex, startX, speed);

    m_cars.push_back(std::move(car));
}

// ── draw / clear / getCars ────────────────────────────────────────────────────
void Lane::draw(QGraphicsScene *scene) const {
    for (const auto &car : m_cars)
        car->draw(scene);
}

void Lane::clear() { m_cars.clear(); }

const std::vector<std::unique_ptr<Car>>& Lane::getCars() const { return m_cars; }