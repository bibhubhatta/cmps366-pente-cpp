#include <gtest/gtest.h>
#include "SerialFile.h"

TEST(SerialFile, ScoresAndPairs)
{
    SerialFile serial{"serials/provided.txt"};
    EXPECT_EQ(serial.get_human_score(), 0);
    EXPECT_EQ(serial.get_computer_score(), 0);
    EXPECT_EQ(serial.get_human_captured_pairs(), 0);
    EXPECT_EQ(serial.get_computer_captured_pairs(), 0);
}