#pragma once

/**
 * @file ninjaskin.h
 * @brief Skórka Ninja – odblokowanie kosztuje 500 pkt.
 */

#include "playerskin.h"

/**
 * @class NinjaSkin
 * @brief Ciemna skórka z czerwonymi oczami.
 */
class NinjaSkin : public PlayerSkin {
public:
    NinjaSkin();
    QPixmap getSprite()            const override;
    QPixmap getAnimFrame(int tick) const override;
};
