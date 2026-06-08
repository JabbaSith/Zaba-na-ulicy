/**
 * @file suv.cpp
 */

#include "suv.h"
#include "gamedefs.h"

SUV::SUV(int laneIndex, float startX, float speed, QObject *parent)
    : Car(startX,
          laneTopY(laneIndex) + (LANE_HEIGHT - 35) / 2,
          speed, laneIndex, 70, 35, parent)
{}

void SUV::move() {
    m_x += m_speed;
    if (m_speed > 0 && m_x > SCENE_WIDTH)        m_x = (float)-m_width;
    if (m_speed < 0 && m_x + m_width < 0)        m_x = (float)SCENE_WIDTH;
}

QRect   SUV::getBoundingRect() const { return {(int)m_x, (int)m_y, m_width, m_height}; }
QString SUV::getType()         const { return "SUV"; }
