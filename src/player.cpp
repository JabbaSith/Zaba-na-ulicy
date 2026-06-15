/**
 * @file player.cpp
 */

#include "player.h"
#include <QGraphicsPixmapItem>

Player::Player(int startX, int startY, QObject *parent)
    : QObject(parent)
    , m_x(startX), m_y(startY)
    , m_startX(startX), m_startY(startY)
    , m_alive(true), m_skin(nullptr)
{}

void Player::move(Direction dir) {
    if (!m_alive) return;
    switch (dir) {
        case Direction::Up:    m_y -= PLAYER_STEP; break;
        case Direction::Down:  m_y += PLAYER_STEP; break;
        case Direction::Left:  m_x -= PLAYER_STEP; break;
        case Direction::Right: m_x += PLAYER_STEP; break;
        default: break;
    }
    // Granice sceny
    m_x = qBound(0, m_x, SCENE_WIDTH  - PLAYER_SIZE);
    m_y = qBound(0, m_y, SCENE_HEIGHT - PLAYER_SIZE);
}

void Player::draw(QGraphicsScene *scene, int tick) const {
    if (!scene || !m_skin) return;
    QPixmap pix = m_skin->getAnimFrame(tick)
                       .scaled(PLAYER_SIZE, PLAYER_SIZE,
                               Qt::KeepAspectRatio,
                               Qt::SmoothTransformation);
    auto *item = scene->addPixmap(pix);
    item->setPos(m_x, m_y);
    item->setZValue(10);
}

void Player::reset() {
    m_x = m_startX;
    m_y = m_startY;
    m_alive = true;
}

QRect Player::getBoundingRect() const { return {m_x, m_y, PLAYER_SIZE, PLAYER_SIZE}; }
int   Player::getX()     const { return m_x; }
int   Player::getY()     const { return m_y; }
bool  Player::isAlive()  const { return m_alive; }
void  Player::setAlive(bool a) { m_alive = a; }
void  Player::setSkin(PlayerSkin *s) { m_skin = s; }
