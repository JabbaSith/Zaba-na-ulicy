/**
 * @file defaultskin.cpp
 */

#include "defaultskin.h"
#include <QPainter>

DefaultSkin::DefaultSkin() : PlayerSkin("Default", 0) {}

QPixmap DefaultSkin::getSprite() const {
    QPixmap pix(40, 40);
    pix.fill(Qt::transparent);
    QPainter p(&pix);
    p.setBrush(Qt::green);
    p.setPen(Qt::darkGreen);
    p.drawEllipse(2, 2, 36, 36);
    // oczy
    p.setBrush(Qt::white); p.drawEllipse(8, 8, 8, 8); p.drawEllipse(24, 8, 8, 8);
    p.setBrush(Qt::black); p.drawEllipse(10,10, 4, 4); p.drawEllipse(26,10, 4, 4);
    return pix;
}

QPixmap DefaultSkin::getAnimFrame(int tick) const {
    Q_UNUSED(tick);
    return getSprite();
}
