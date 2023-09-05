#include "Serial.h"
#include <gtest/gtest.h>

TEST(Serial, ScoresAndPairs)
{
    const std::string serial_string {"Board:\n"
                                     "OOOOOOOOOOOOOOOOOOO\n"
                                     "OOOOOOOOOOOOOOOOOOO\n"
                                     "OOOOOOOOOOOOOOOOOOO\n"
                                     "OOOOOOOOOOOOOOOOOOO\n"
                                     "OOOOOOOOOOOOOOOOOOO\n"
                                     "OOOOOOOOOOOOOOOOOOO\n"
                                     "OOOOOOOOOOOOOOOOOOO\n"
                                     "OOOOOOOOOOOOOOOOOOO\n"
                                     "OOOOOOOOOOOOOOOOOOO\n"
                                     "OOOOOOOOOOWOOOOOOOO\n"
                                     "OOOOOOOOOOOOOOOOOOO\n"
                                     "OOOOOOOOOOOOOOOOOOO\n"
                                     "OOOOOOOOOOOOOOOOOOO\n"
                                     "OOOOOOOOOOOOOOOOOOO\n"
                                     "OOOOOOOOOOOOOOOOOOO\n"
                                     "OOOOOOOOOOOOOOOOOOO\n"
                                     "OOOOOOOOOOOOOOOOOOO\n"
                                     "OOOOOOOOOOOOOOOOOOO\n"
                                     "OOOOOOOOOOOOOOOOOOO\n"
                                     "\n"
                                     "Human:\n"
                                     "Captured pairs: 0\n"
                                     "Score: 0\n"
                                     "\n"
                                     "Computer:\n"
                                     "Captured pairs: 0\n"
                                     "Score: 0\n"
                                     "\n"
                                     "Next Player: Human - Black"};

    auto serial = Serial(serial_string);
    EXPECT_EQ(serial.get_human_score(), 0);
    EXPECT_EQ(serial.get_computer_score(), 0);
    EXPECT_EQ(serial.get_human_captured_pairs(), 0);
    EXPECT_EQ(serial.get_computer_captured_pairs(), 0);
}

TEST(Serial, ScoresAndPairs2)
{
    const std::string serial_string {"Board:\n"
                                     "OOOOOOOOOOOOOOOOOOO\n"
                                     "OOOOOOOOOOOOOOOOOOO\n"
                                     "OOOOOOOOOOOOOOOOOOO\n"
                                     "OOOOOOOOOOOOOOOOOOO\n"
                                     "OOOOOOOOOOOOOOOOOOO\n"
                                     "OOOOOOOOOOOOOOOOOOO\n"
                                     "OOOOOOOOOOOOOOOOOOO\n"
                                     "OOOOOOOOOOOOOOOOOOO\n"
                                     "OOOOOOOOOOOOOOOOOOO\n"
                                     "OOOOOOOOOOWOOOOOOOO\n"
                                     "OOOOOOOOOOOOOOOOOOO\n"
                                     "OOOOOOOOOOOOOOOOOOO\n"
                                     "OOOOOOOOOOOOOOOOOOO\n"
                                     "OOOOOOOOOOOOOOOOOOO\n"
                                     "OOOOOOOOOOOOOOOOOOO\n"
                                     "OOOOOOOOOOOOOOOOOOO\n"
                                     "OOOOOOOOOOOOOOOOOOO\n"
                                     "OOOOOOOOOOOOOOOOOOO\n"
                                     "OOOOOOOOOOOOOOOOOOO\n"
                                     "\n"
                                     "Human:\n"
                                     "Captured pairs: 2\n"
                                     "Score: 25\n"
                                     "\n"
                                     "Computer:\n"
                                     "Captured pairs: 3\n"
                                     "Score: 50\n"
                                     "\n"
                                     "Next Player: Human - Black"};

    Serial serial {serial_string};

    EXPECT_EQ(serial.get_human_score(), 25);
    EXPECT_EQ(serial.get_computer_score(), 50);
    EXPECT_EQ(serial.get_human_captured_pairs(), 2);
    EXPECT_EQ(serial.get_computer_captured_pairs(), 3);
}