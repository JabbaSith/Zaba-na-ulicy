/**
 * @file car.cpp
 */

#include "car.h"
#include "gamedefs.h"
#include <QPainter>
#include <QGraphicsPixmapItem>

Car::Car(float x, float y, float speed, int laneIndex, int w, int h, QObject *parent)
    : QObject(parent)
    , m_x(x), m_y(y), m_speed(speed)
    , m_laneIndex(laneIndex), m_width(w), m_height(h)
{}

void Car::draw(QGraphicsScene *scene) const {
    if (!scene) return;
    QPixmap pix(m_width, m_height);
    pix.fill(Qt::transparent);
    QPainter p(&pix);
    p.setRenderHint(QPainter::Antialiasing);
    p.setBrush(Qt::red);
    p.setPen(Qt::darkRed);
    p.drawRoundedRect(0, 4, m_width, m_height - 8, 4, 4);
    p.setPen(Qt::white);
    p.setFont(QFont("Arial", 7, QFont::Bold));
    p.drawText(pix.rect(), Qt::AlignCenter, getType().left(3));
    auto *item = scene->addPixmap(pix);
    item->setPos(static_cast<int>(m_x), static_cast<int>(m_y));
    item->setZValue(5);
}

float Car::getX()         const { return m_x; }
float Car::getY()         const { return m_y; }
int   Car::getLaneIndex() const { return m_laneIndex; }
