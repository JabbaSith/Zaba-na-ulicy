/**
 * @file skinmanager.cpp
 */

#include "skinmanager.h"
#include "defaultskin.h"
#include "ninjaskin.h"
#include "goldenskin.h"

SkinManager::SkinManager(QObject *parent)
    : QObject(parent), m_activeIndex(0)
{
    m_skins.push_back(std::make_unique<DefaultSkin>());
    m_skins.push_back(std::make_unique<NinjaSkin>());
    m_skins.push_back(std::make_unique<GoldenSkin>());

    for (auto &skin : m_skins)
        skin->setUnlocked(true);
}

void SkinManager::tryUnlock(int pointsTotal) {
    for (auto &skin : m_skins) {
        if (!skin->isUnlocked() && pointsTotal >= skin->getUnlockCost())
            skin->setUnlocked(true);
    }
}

void SkinManager::setActiveSkin(int index) {
    if (index >= 0 && index < (int)m_skins.size() && m_skins[index]->isUnlocked())
        m_activeIndex = index;
}

PlayerSkin* SkinManager::getActiveSkin() const {
    return m_skins[m_activeIndex].get();
}

int SkinManager::getActiveIndex() const {
    return m_activeIndex;
}

bool SkinManager::isUnlocked(int index) const {
    if (index < 0 || index >= (int)m_skins.size()) return false;
    return m_skins[index]->isUnlocked();
}

const std::vector<std::unique_ptr<PlayerSkin>>& SkinManager::getAllSkins() const {
    return m_skins;
}
