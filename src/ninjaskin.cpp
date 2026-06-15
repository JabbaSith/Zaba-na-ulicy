/**
 * @file ninjaskin.cpp
 */

#include "ninjaskin.h"
#include <QPainter>

NinjaSkin::NinjaSkin() : PlayerSkin("Ninja", 500) {}

QPixmap NinjaSkin::getSprite() const {
    QPixmap pix(40, 40);
    pix.fill(Qt::transparent);
    QPainter p(&pix);
    p.setBrush(QColor(30, 30, 30));
    p.setPen(QColor(80, 80, 80));
    p.drawEllipse(2, 2, 36, 36);
    p.setBrush(Qt::red);
    p.drawEllipse(9, 12, 7, 7);
    p.drawEllipse(24, 12, 7, 7);
    return pix;
}

QPixmap NinjaSkin::getAnimFrame(int tick) const {
    Q_UNUSED(tick);
    return getSprite();
}
