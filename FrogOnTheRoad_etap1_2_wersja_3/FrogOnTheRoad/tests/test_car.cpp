/**
 * @file test_car.cpp
 * @brief Testy jednostkowe klas pojazdów.
 */

#include <gtest/gtest.h>
#include "smallcar.h"
#include "truck.h"
#include "suv.h"
#include "gamedefs.h"

TEST(SmallCarTest, TypeString) {
    SmallCar c(0);
    EXPECT_EQ(c.getType(), "SmallCar");
}

TEST(SmallCarTest, BoundingRectNonEmpty) {
    SmallCar c(0);
    QRect r = c.getBoundingRect();
    EXPECT_GT(r.width(),  0);
    EXPECT_GT(r.height(), 0);
}

TEST(SmallCarTest, MovesForwardRight) {
    SmallCar c(0, 100.0f, SPEED_SMALL);
    float before = c.getX();
    c.move();
    EXPECT_FLOAT_EQ(c.getX(), before + SPEED_SMALL);
}

TEST(SmallCarTest, MovesForwardLeft) {
    SmallCar c(0, 100.0f, -SPEED_SMALL);
    float before = c.getX();
    c.move();
    EXPECT_FLOAT_EQ(c.getX(), before - SPEED_SMALL);
}

TEST(SmallCarTest, CenteredInLane) {
    SmallCar c(0);
    int laneTop = laneTopY(0);
    int laneBottom = laneTop + LANE_HEIGHT;
    EXPECT_GT(c.getY(), laneTop);
    EXPECT_LT((int)c.getY() + 28, laneBottom);
}

TEST(TruckTest, TypeString) {
    Truck t(1);
    EXPECT_EQ(t.getType(), "Truck");
}

TEST(TruckTest, SlowerThanSmallCar) {
    EXPECT_LT(SPEED_TRUCK, SPEED_SMALL);
}

TEST(TruckTest, LaneIndexStored) {
    Truck t(2);
    EXPECT_EQ(t.getLaneIndex(), 2);
}

TEST(SUVTest, TypeString) {
    SUV s(2);
    EXPECT_EQ(s.getType(), "SUV");
}

TEST(SUVTest, LaneIndexStored) {
    SUV s(3);
    EXPECT_EQ(s.getLaneIndex(), 3);
}

TEST(SUVTest, CenteredInBottomSection) {
    // Pas 3 to pierwszy pas dolnej sekcji
    SUV s(3);
    int laneTop = laneTopY(3);
    int laneBottom = laneTop + LANE_HEIGHT;
    EXPECT_GT((int)s.getY(), laneTop);
    EXPECT_LT((int)s.getY() + 35, laneBottom);
}
