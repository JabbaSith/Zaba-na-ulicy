/**
 * @file test_scoremanager.cpp
 * @brief Testy jednostkowe klasy ScoreManager.
 */

#include <gtest/gtest.h>
#include <QFile>
#include "scoremanager.h"

/**
 * @class ScoreManagerTest
 * @brief Fixture usuwający "highscore.txt" przed każdym testem, aby testy
 *        nie wpływały na siebie przez trwały (zapisywany na dysk) rekord.
 */
class ScoreManagerTest : public ::testing::Test {
protected:
    void SetUp() override { QFile::remove("highscore.txt"); }
    void TearDown() override { QFile::remove("highscore.txt"); }
};

TEST_F(ScoreManagerTest, InitialScoreZero) {
    ScoreManager sm;
    EXPECT_EQ(sm.getCurrentScore(), 0);
    EXPECT_EQ(sm.getHighScore(),    0);
}

TEST_F(ScoreManagerTest, AddPoints) {
    ScoreManager sm;
    sm.addPoints(100);
    EXPECT_EQ(sm.getCurrentScore(), 100);
}

TEST_F(ScoreManagerTest, HighScoreTracked) {
    ScoreManager sm;
    sm.addPoints(200);
    sm.addPoints(300);
    EXPECT_EQ(sm.getHighScore(), 500);
}

TEST_F(ScoreManagerTest, ResetClearsCurrentScore) {
    ScoreManager sm;
    sm.addPoints(500);
    sm.reset();
    EXPECT_EQ(sm.getCurrentScore(), 0);
}

TEST_F(ScoreManagerTest, ResetPreservesHighScore) {
    ScoreManager sm;
    sm.addPoints(500);
    sm.reset();
    EXPECT_EQ(sm.getHighScore(), 500);
}

TEST_F(ScoreManagerTest, MultipleResets) {
    ScoreManager sm;
    sm.addPoints(100);
    sm.reset();
    sm.addPoints(50);
    EXPECT_EQ(sm.getCurrentScore(), 50);
    EXPECT_EQ(sm.getHighScore(),    100);
}

TEST_F(ScoreManagerTest, HighScorePersistsAcrossInstances) {
    {
        ScoreManager sm1;
        sm1.addPoints(777);
        EXPECT_EQ(sm1.getHighScore(), 777);
    }
    // Nowa instancja (np. po powrocie do menu i ponownym wejściu do gry)
    // powinna wczytać rekord zapisany przez poprzednią.
    ScoreManager sm2;
    EXPECT_EQ(sm2.getHighScore(), 777);
    EXPECT_EQ(sm2.getCurrentScore(), 0); // currentScore zawsze startuje od 0
}
