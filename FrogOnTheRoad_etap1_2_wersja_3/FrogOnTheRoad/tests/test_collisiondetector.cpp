/**
 * @file test_collisiondetector.cpp
 * @brief Testy wykrywania kolizji.
 */

#include <gtest/gtest.h>
#include "collisiondetector.h"
#include "defaultskin.h"
#include <vector>
#include <memory>

class CollisionTest : public ::testing::Test {
protected:
    void SetUp() override {
        skin   = std::make_unique<DefaultSkin>();
        player = std::make_unique<Player>(400, 400);
        player->setSkin(skin.get());
        detector = std::make_unique<CollisionDetector>();
    }
    std::unique_ptr<DefaultSkin>        skin;
    std::unique_ptr<Player>             player;
    std::unique_ptr<CollisionDetector>  detector;
};

TEST_F(CollisionTest, NoLanesNoCollision) {
    std::vector<std::unique_ptr<Lane>> emptyLanes;
    EXPECT_FALSE(detector->checkCollision(*player, emptyLanes));
}

TEST_F(CollisionTest, NoCollisionWhenCarsAreAway) {
    std::vector<std::unique_ptr<Lane>> lanes;
    // Pas z samochodem daleko po lewej stronie
    auto lane = std::make_unique<Lane>(0);
    // SmallCar startuje na x=-200 (poza kadrem)
    // Lane.spawnCar() nie jest wywoływana, więc pas jest pusty
    lanes.push_back(std::move(lane));
    EXPECT_FALSE(detector->checkCollision(*player, lanes));
}
