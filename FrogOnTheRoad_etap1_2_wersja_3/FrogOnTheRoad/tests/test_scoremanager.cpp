/**
 * @file test_scoremanager.cpp
 * @brief Testy jednostkowe klasy ScoreManager.
 */

#include <gtest/gtest.h>
#include "scoremanager.h"

TEST(ScoreManagerTest, InitialScoreZero) {
    ScoreManager sm;
    EXPECT_EQ(sm.getCurrentScore(), 0);
    EXPECT_EQ(sm.getHighScore(),    0);
}

TEST(ScoreManagerTest, AddPoints) {
    ScoreManager sm;
    sm.addPoints(100);
    EXPECT_EQ(sm.getCurrentScore(), 100);
}

TEST(ScoreManagerTest, HighScoreTracked) {
    ScoreManager sm;
    sm.addPoints(200);
    sm.addPoints(300);
    EXPECT_EQ(sm.getHighScore(), 500);
}

TEST(ScoreManagerTest, ResetClearsCurrentScore) {
    ScoreManager sm;
    sm.addPoints(500);
    sm.reset();
    EXPECT_EQ(sm.getCurrentScore(), 0);
}

TEST(ScoreManagerTest, ResetPreservesHighScore) {
    ScoreManager sm;
    sm.addPoints(500);
    sm.reset();
    EXPECT_EQ(sm.getHighScore(), 500);
}

TEST(ScoreManagerTest, MultipleResets) {
    ScoreManager sm;
    sm.addPoints(100);
    sm.reset();
    sm.addPoints(50);
    EXPECT_EQ(sm.getCurrentScore(), 50);
    EXPECT_EQ(sm.getHighScore(),    100);
}
