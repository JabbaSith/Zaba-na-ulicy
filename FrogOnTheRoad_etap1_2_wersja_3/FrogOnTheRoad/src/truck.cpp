/**
 * @file truck.cpp
 */

#include "truck.h"
#include "gamedefs.h"

Truck::Truck(int laneIndex, float startX, float speed, QObject *parent)
    : Car(startX,
          laneTopY(laneIndex) + (LANE_HEIGHT - 40) / 2,
          speed, laneIndex, 90, 40, parent)
{}

void Truck::move() {
    m_x += m_speed;
    if (m_speed > 0 && m_x > SCENE_WIDTH)        m_x = (float)-m_width;
    if (m_speed < 0 && m_x + m_width < 0)        m_x = (float)SCENE_WIDTH;
}

QRect   Truck::getBoundingRect() const { return {(int)m_x, (int)m_y, m_width, m_height}; }
QString Truck::getType()         const { return "Truck"; }
