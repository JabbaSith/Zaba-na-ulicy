/**
 * @file test_skinmanager.cpp
 * @brief Testy jednostkowe SkinManager oraz hierarchii PlayerSkin.
 */

#include <gtest/gtest.h>
#include "skinmanager.h"

TEST(SkinManagerTest, AllSkinsUnlockedAtStart) {
    SkinManager sm;
    EXPECT_TRUE(sm.isUnlocked(0));  // Default
    EXPECT_TRUE(sm.isUnlocked(1));  // Ninja  – odblokowana od razu
    EXPECT_TRUE(sm.isUnlocked(2));  // Golden – odblokowana od razu
}

TEST(SkinManagerTest, ActiveSkinIsNeverNull) {
    SkinManager sm;
    ASSERT_NE(sm.getActiveSkin(), nullptr);
    EXPECT_EQ(sm.getActiveSkin()->getName(), "Default");
}

TEST(SkinManagerTest, SetActiveSkinWorks) {
    SkinManager sm;
    sm.setActiveSkin(1);
    EXPECT_EQ(sm.getActiveSkin()->getName(), "Ninja");
    sm.setActiveSkin(2);
    EXPECT_EQ(sm.getActiveSkin()->getName(), "Golden");
    sm.setActiveSkin(0);
    EXPECT_EQ(sm.getActiveSkin()->getName(), "Default");
}

TEST(SkinManagerTest, CycleSkinsViaIndex) {
    SkinManager sm;
    int count = static_cast<int>(sm.getAllSkins().size());
    EXPECT_EQ(count, 3);
    for (int i = 0; i < count; ++i) {
        sm.setActiveSkin(i);
        EXPECT_EQ(sm.getActiveIndex(), i);
    }
}

TEST(SkinManagerTest, AllSkinsHaveValidSprites) {
    SkinManager sm;
    for (const auto &skin : sm.getAllSkins()) {
        EXPECT_FALSE(skin->getSprite().isNull());
        EXPECT_FALSE(skin->getAnimFrame(0).isNull());
    }
}
