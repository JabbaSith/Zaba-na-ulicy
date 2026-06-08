#pragma once

/**
 * @file playerskin.h
 * @brief Abstrakcyjna klasa bazowa dla skórek gracza.
 */

#include <QString>
#include <QPixmap>

/**
 * @class PlayerSkin
 * @brief Abstrakcja wyglądu żaby – klasy pochodne dostarczają sprite'y.
 */
class PlayerSkin {
public:
    explicit PlayerSkin(const QString &name, int unlockCost);
    virtual ~PlayerSkin() = default;

    /** @brief Główny sprite skórki. */
    virtual QPixmap getSprite() const = 0;

    /** @brief Klatka animacji dla danego tiku gry. */
    virtual QPixmap getAnimFrame(int tick) const = 0;

    QString getName()       const;
    int     getUnlockCost() const;
    bool    isUnlocked()    const;
    void    setUnlocked(bool unlocked);

protected:
    QString m_name;
    int     m_unlockCost;
    bool    m_unlocked;
};
