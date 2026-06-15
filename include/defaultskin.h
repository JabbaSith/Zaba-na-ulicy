#pragma once

/**
 * @file defaultskin.h
 * @brief Domyślna skórka żaby, zawsze odblokowana.
 */

#include "playerskin.h"

/**
 * @class DefaultSkin
 * @brief Zielona żaba – dostępna od początku gry.
 */
class DefaultSkin : public PlayerSkin {
public:
    DefaultSkin();
    QPixmap getSprite()            const override;
    QPixmap getAnimFrame(int tick) const override;
};
