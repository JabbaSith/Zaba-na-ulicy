#pragma once

/**
 * @file player.h
 * @brief Klasa reprezentująca żabę – gracza.
 */

#include <QObject>
#include <QRect>
#include <QGraphicsScene>
#include "gamedefs.h"
#include "playerskin.h"

/**
 * @class Player
 * @brief Żaba poruszająca się po planszy.
 *
 * Przechowuje pozycję i stan życia. Metoda move() przesuwa gracza
 * o PLAYER_STEP, pilnując granic sceny.
 */
class Player : public QObject {
    Q_OBJECT
public:
    explicit Player(int startX, int startY, QObject *parent = nullptr);

    /** @brief Przesuwa gracza w podanym kierunku. */
    void move(Direction dir);

    /** @brief Rysuje gracza na scenie. */
    void draw(QGraphicsScene *scene, int tick) const;

    /** @brief Resetuje pozycję i przywraca życie. */
    void reset();

    QRect getBoundingRect() const;
    int   getX()     const;
    int   getY()     const;
    bool  isAlive()  const;
    void  setAlive(bool alive);

    /** @brief Ustawia skórkę (właścicielem jest SkinManager). */
    void setSkin(PlayerSkin *skin);

private:
    int         m_x, m_y;
    int         m_startX, m_startY;
    bool        m_alive;
    PlayerSkin *m_skin;   ///< surowy wskaźnik – nie zwalniamy tutaj
};
