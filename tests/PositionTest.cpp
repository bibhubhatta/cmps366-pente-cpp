#include <gtest/gtest.h>

#include "Board.h"

TEST(DistanceTest, samePosition)
{
    Position p1 {0, 0};
    Position p2 {0, 0};
    EXPECT_EQ(0, Position::distance(p1, p2));
}

TEST(DistanceTest, adjacentPosition)
{
    Position p1 {0, 0};
    Position p2 {0, 1};
    EXPECT_EQ(1, Position::distance(p1, p2));
}

TEST(DistanceTest, diagonalPosition)
{
    Position p1 {0, 0};
    Position p2 {1, 1};
    EXPECT_EQ(1, Position::distance(p1, p2));
}

TEST(DistanceTest, diagonalPosition2)
{
    Position p1 {1, 1};
    Position p2 {3, 4};
    EXPECT_EQ(3, Position::distance(p1, p2));
}

TEST(DistanceTest, randomPosition)
{
    Position p1 {3, 5};
    Position p2 {10, 1};

    EXPECT_EQ(7, Position::distance(p1, p2));
}