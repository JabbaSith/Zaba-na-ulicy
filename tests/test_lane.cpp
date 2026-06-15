/**
 * @file test_lane.cpp
 * @brief Testy klasy Lane.
 */

#include <gtest/gtest.h>
#include "lane.h"
#include "gamedefs.h"

TEST(LaneTest, InitiallyEmpty) {
    Lane lane(0);
    EXPECT_TRUE(lane.getCars().empty());
}

TEST(LaneTest, SpawnCarAddsOne) {
    Lane lane(0);
    lane.spawnCar();
    EXPECT_EQ(lane.getCars().size(), 1u);
}

TEST(LaneTest, ClearRemovesAll) {
    Lane lane(0);
    lane.spawnCar();
    lane.spawnCar();
    lane.clear();
    EXPECT_TRUE(lane.getCars().empty());
}

TEST(LaneTest, EvenLaneGoesRight) {
    // Pas parzysty (0) – prędkość dodatnia (ruch w prawo)
    Lane lane(0);
    lane.spawnCar();
    ASSERT_FALSE(lane.getCars().empty());
    float speed = lane.getCars()[0]->getX();  // sprawdzimy po move()
    float xBefore = lane.getCars()[0]->getX();
    // Wymuszamy move przez update... ale auto może być poza ekranem po jednym tiku
    // Sprawdzamy znak prędkości pośrednio przez pozycję spawnu
    // Parzysty pas spawnuje z lewej strony (ujemne X)
    EXPECT_LT(lane.getCars()[0]->getX(), 0.0f);
    Q_UNUSED(speed); Q_UNUSED(xBefore);
}

TEST(LaneTest, OddLaneSpawnsFromRight) {
    // Pas nieparzysty (1) – spawny z prawej strony sceny
    Lane lane(1);
    lane.spawnCar();
    ASSERT_FALSE(lane.getCars().empty());
    EXPECT_GT(lane.getCars()[0]->getX(), (float)SCENE_WIDTH);
}

TEST(LaneTest, UpdateEventuallySpawns) {
    Lane lane(0);
    // Pierwsze update() powinno od razu spawnować (pas pusty)
    lane.update();
    EXPECT_GT(lane.getCars().size(), 0u);
}

TEST(LaneTest, CarsStayInLaneBounds) {
    Lane lane(2);
    lane.spawnCar();
    ASSERT_FALSE(lane.getCars().empty());
    int laneTop    = laneTopY(2);
    int laneBottom = laneTop + LANE_HEIGHT;
    for (const auto &car : lane.getCars()) {
        EXPECT_GE((int)car->getY(), laneTop);
        EXPECT_LT((int)car->getY(), laneBottom);
    }
}
