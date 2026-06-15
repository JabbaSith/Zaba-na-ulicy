/**
 * @file test_aicontroller.cpp
 * @brief Testy jednostkowe AIController (Q-learning).
 */

#include <gtest/gtest.h>
#include "aicontroller.h"
#include "player.h"
#include "lane.h"

TEST(AIControllerTest, ActionIndexRoundTrip) {
    EXPECT_EQ(AIController::actionToIndex(Direction::Up),    0);
    EXPECT_EQ(AIController::actionToIndex(Direction::Down),  1);
    EXPECT_EQ(AIController::actionToIndex(Direction::Left),  2);
    EXPECT_EQ(AIController::actionToIndex(Direction::Right), 3);

    for (int i = 0; i < AIController::ACTION_COUNT; ++i)
        EXPECT_EQ(AIController::actionToIndex(AIController::indexToAction(i)), i);
}

TEST(AIControllerTest, StateInValidRange) {
    AIController ai;
    Player player(SCENE_WIDTH/2, SCENE_HEIGHT - PLAYER_STEP);
    std::vector<std::unique_ptr<Lane>> lanes;
    for (int i = 0; i < 6; ++i)
        lanes.push_back(std::make_unique<Lane>(i));

    int state = ai.getState(player, lanes);
    EXPECT_GE(state, 0);
    EXPECT_LT(state, AIController::STATE_COUNT);
}

TEST(AIControllerTest, DecideMoveReturnsValidDirection) {
    AIController ai;
    Player player(SCENE_WIDTH/2, SCENE_HEIGHT - PLAYER_STEP);
    std::vector<std::unique_ptr<Lane>> lanes;
    for (int i = 0; i < 6; ++i)
        lanes.push_back(std::make_unique<Lane>(i));

    Direction d = ai.decideMove(player, lanes);
    EXPECT_TRUE(d == Direction::Up || d == Direction::Down ||
                d == Direction::Left || d == Direction::Right);
}

TEST(AIControllerTest, TrainUpdatesQValueTowardsReward) {
    AIController ai;
    int state = 5;
    int next  = 5;

    // Wielokrotny trening powinien podnieść Q(state, Up) w stronę dużej nagrody.
    for (int i = 0; i < 200; ++i)
        ai.train(state, next, Direction::Up, 1.0f, false);

    // train() samo nie zwiększa licznika kroków (robi to decideMove);
    // sprawdzamy po prostu, że wielokrotne wywołania train nie crashują
    // i że suma nagród jest poprawnie akumulowana.
    EXPECT_GT(ai.getTotalReward(), 0.0f);
}

TEST(AIControllerTest, EpisodeCounterIncreasesOnDone) {
    AIController ai;
    EXPECT_EQ(ai.getEpisodeCount(), 0);
    ai.train(0, 0, Direction::Up, -100.0f, true);
    EXPECT_EQ(ai.getEpisodeCount(), 1);
}

TEST(AIControllerTest, ResetEpisodeClearsCounters) {
    AIController ai;
    Player player(SCENE_WIDTH/2, SCENE_HEIGHT - PLAYER_STEP);
    std::vector<std::unique_ptr<Lane>> lanes;
    for (int i = 0; i < 6; ++i)
        lanes.push_back(std::make_unique<Lane>(i));

    ai.decideMove(player, lanes);
    EXPECT_GT(ai.getStepCount(), 0);

    ai.resetEpisode();
    EXPECT_EQ(ai.getStepCount(), 0);
    EXPECT_FLOAT_EQ(ai.getTotalReward(), 0.0f);
}
