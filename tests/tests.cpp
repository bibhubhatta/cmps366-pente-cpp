#include <gtest/gtest.h>

#include "Serial.h"

class SerialTestFixture : public ::testing::Test
{
  public:
    void SetUp() override
    {
        serial_string_provided = "Board:\n"
                                 "OOOOOOOOOOOOOOOOOOO\n"
                                 "OOOOOOOOOOOOOOOOOOO\n"
                                 "OOOOOOOOOOOOOOOOOOO\n"
                                 "OOOOOOOOOOOOOOOOOOO\n"
                                 "OOOOOOOOOOOOOOOOOOO\n"
                                 "OOOOOOOOOOOOOOOOOOO\n"
                                 "OOOOOOOOOOOOOOOOOOO\n"
                                 "OOOOOOOOOOOOOOOOOOO\n"
                                 "OOOOOOOOOOOOOOOOOOO\n"
                                 "OOOOOOOOOWOOOOOOOOO\n"
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
                                 "Next Player: Human - Black";

        serial_string_custom = "Board:\n"
                               "OOOOOOOOOOOOOOOOOOO\n"
                               "OOOOOOOOOOOOOOOOOOO\n"
                               "OOOOOOOOOOOOOOOOOOO\n"
                               "OOOOOOOOOOOOOOOOOOO\n"
                               "OOOOOOOOOOOOOOOOOOO\n"
                               "OOOOOOOOOOOOOOOOOOO\n"
                               "OOOOOOOOOOOOOOOOOOO\n"
                               "OOOOOOOOOOOOOOOOOOO\n"
                               "OOOOOOOOOOOOOOOOOOO\n"
                               "OOOOOOOOOWOOOOOOOOO\n"
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
                               "Captured pairs: 10\n"
                               "Score: 50\n"
                               "\n"
                               "Computer:\n"
                               "Captured pairs: 20\n"
                               "Score: 100\n"
                               "\n"
                               "Next Player: Human - Black";
    }

    std::string serial_string_provided;
    std::string serial_string_custom;
};

TEST_F(SerialTestFixture, HumanScore)
{
    auto serial = Serial(serial_string_provided);
    EXPECT_EQ(serial.get_human_score(), 0);

    serial = Serial(serial_string_custom);
    EXPECT_EQ(serial.get_human_score(), 50);
}

TEST_F(SerialTestFixture, HumanCapturedPairs)
{
    auto serial = Serial(serial_string_provided);
    EXPECT_EQ(serial.get_human_captured_pairs(), 0);

    serial = Serial(serial_string_custom);
    EXPECT_EQ(serial.get_human_captured_pairs(), 10);
}

TEST_F(SerialTestFixture, ComputerScore)
{
    auto serial = Serial(serial_string_provided);
    EXPECT_EQ(serial.get_computer_score(), 0);

    serial = Serial(serial_string_custom);
    EXPECT_EQ(serial.get_computer_score(), 100);
}

TEST_F(SerialTestFixture, ComputerCapturedPairs)
{
    auto serial = Serial(serial_string_provided);
    EXPECT_EQ(serial.get_computer_captured_pairs(), 0);

    serial = Serial(serial_string_custom);
    EXPECT_EQ(serial.get_computer_captured_pairs(), 20);
}
