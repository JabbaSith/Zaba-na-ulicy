/**
 * @file playerskin.cpp
 * @brief Implementacja metod nieabstrakcyjnych PlayerSkin.
 */

#include "playerskin.h"

PlayerSkin::PlayerSkin(const QString &name, int unlockCost)
    : m_name(name), m_unlockCost(unlockCost), m_unlocked(unlockCost == 0) {}

QString PlayerSkin::getName()       const { return m_name; }
int     PlayerSkin::getUnlockCost() const { return m_unlockCost; }
bool    PlayerSkin::isUnlocked()    const { return m_unlocked; }
void    PlayerSkin::setUnlocked(bool u)   { m_unlocked = u; }
