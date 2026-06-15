/**
 * @file goldenskin.cpp
 */

#include "goldenskin.h"
#include <QPainter>

GoldenSkin::GoldenSkin() : PlayerSkin("Golden", 1500) {}

QPixmap GoldenSkin::getSprite() const {
    QPixmap pix(40, 40);
    pix.fill(Qt::transparent);
    QPainter p(&pix);
    p.setBrush(QColor(255, 215, 0));
    p.setPen(QColor(184, 134, 11));
    p.drawEllipse(2, 2, 36, 36);
    p.setBrush(Qt::white);
    p.drawEllipse(9, 10, 8, 8);
    p.drawEllipse(23, 10, 8, 8);
    p.setBrush(QColor(50, 30, 0));
    p.drawEllipse(11, 12, 4, 4);
    p.drawEllipse(25, 12, 4, 4);
    return pix;
}

QPixmap GoldenSkin::getAnimFrame(int tick) const {
    Q_UNUSED(tick);
    return getSprite();
}
