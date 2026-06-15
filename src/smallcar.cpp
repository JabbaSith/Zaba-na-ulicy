/**
 * @file smallcar.cpp
 */

#include "smallcar.h"
#include "gamedefs.h"

SmallCar::SmallCar(int laneIndex, float startX, float speed, QObject *parent)
    : Car(startX,
          laneTopY(laneIndex) + (LANE_HEIGHT - 28) / 2,  // centrowanie w pasie
          speed, laneIndex, 50, 28, parent)
{}

void SmallCar::move() {
    m_x += m_speed;
    if (m_speed > 0 && m_x > SCENE_WIDTH)        m_x = (float)-m_width;
    if (m_speed < 0 && m_x + m_width < 0)        m_x = (float)SCENE_WIDTH;
}

QRect   SmallCar::getBoundingRect() const { return {(int)m_x, (int)m_y, m_width, m_height}; }
QString SmallCar::getType()         const { return "SmallCar"; }
