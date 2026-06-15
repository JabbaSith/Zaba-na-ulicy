#pragma once

/**
 * @file goldenskin.h
 * @brief Skórka Golden – odblokowanie kosztuje 1500 pkt.
 */

#include "playerskin.h"

/**
 * @class GoldenSkin
 * @brief Złota skórka premium.
 */
class GoldenSkin : public PlayerSkin {
public:
    GoldenSkin();
    QPixmap getSprite()            const override;
    QPixmap getAnimFrame(int tick) const override;
};
