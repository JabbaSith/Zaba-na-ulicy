/**
 * @file test_player.cpp
 * @brief Testy jednostkowe klasy Player.
 */

#include <gtest/gtest.h>
#include "player.h"
#include "defaultskin.h"

class PlayerTest : public ::testing::Test {
protected:
    void SetUp() override {
        skin   = std::make_unique<DefaultSkin>();
        player = std::make_unique<Player>(400, START_Y);
        player->setSkin(skin.get());
    }
    std::unique_ptr<DefaultSkin> skin;
    std::unique_ptr<Player>      player;
};

TEST_F(PlayerTest, InitialPosition) {
    EXPECT_EQ(player->getX(), 400);
    EXPECT_EQ(player->getY(), START_Y);
}

TEST_F(PlayerTest, InitialAlive) {
    EXPECT_TRUE(player->isAlive());
}

TEST_F(PlayerTest, MoveUp) {
    int before = player->getY();
    player->move(Direction::Up);
    EXPECT_EQ(player->getY(), before - PLAYER_STEP);
}

TEST_F(PlayerTest, MoveDown) {
    int before = player->getY();
    player->move(Direction::Down);
    // Przy START_Y ruch w dół jest ograniczony przez granicę sceny
    EXPECT_GE(player->getY(), before);
}

TEST_F(PlayerTest, MoveLeft) {
    int before = player->getX();
    player->move(Direction::Left);
    EXPECT_EQ(player->getX(), before - PLAYER_STEP);
}

TEST_F(PlayerTest, MoveRight) {
    int before = player->getX();
    player->move(Direction::Right);
    EXPECT_EQ(player->getX(), before + PLAYER_STEP);
}

TEST_F(PlayerTest, NoBoundaryViolationTop) {
    for (int i = 0; i < 30; ++i)
        player->move(Direction::Up);
    EXPECT_GE(player->getY(), 0);
}

TEST_F(PlayerTest, NoBoundaryViolationLeft) {
    for (int i = 0; i < 30; ++i)
        player->move(Direction::Left);
    EXPECT_GE(player->getX(), 0);
}

TEST_F(PlayerTest, NoBoundaryViolationRight) {
    for (int i = 0; i < 30; ++i)
        player->move(Direction::Right);
    EXPECT_LE(player->getX(), SCENE_WIDTH - PLAYER_SIZE);
}

TEST_F(PlayerTest, DeadPlayerDoesNotMove) {
    player->setAlive(false);
    int bx = player->getX(), by = player->getY();
    player->move(Direction::Up);
    EXPECT_EQ(player->getX(), bx);
    EXPECT_EQ(player->getY(), by);
}

TEST_F(PlayerTest, Reset) {
    player->move(Direction::Up);
    player->setAlive(false);
    player->reset();
    EXPECT_EQ(player->getX(), 400);
    EXPECT_EQ(player->getY(), START_Y);
    EXPECT_TRUE(player->isAlive());
}

TEST_F(PlayerTest, BoundingRectSize) {
    QRect r = player->getBoundingRect();
    EXPECT_EQ(r.width(),  PLAYER_SIZE);
    EXPECT_EQ(r.height(), PLAYER_SIZE);
}
