#include <gtest/gtest.h>

#include "Board.h"
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

        serial_string_custom =
            "Board:\n"
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
            "Captured pairs: 10\n" // Black captured 10 white pairs
            "Score: 50\n"
            "\n"
            "Computer:\n"
            "Captured pairs: 20\n" // White captured 20 black pairs
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

TEST_F(SerialTestFixture, Board)
{
    auto  serial = Serial(serial_string_provided);
    Board board = serial.get_board();
    for (char col = 'A'; col <= 'S'; col++)
    {
        for (int row = 1; row <= 19; row++)
        {
            std::string position = std::string(1, col) + std::to_string(row);

            // Center is white
            if (position == "J10")
            {
                EXPECT_EQ(board.get_stone(position), 'W');
                continue;
            }

            EXPECT_EQ(board.get_stone(position), 'O');
        }
    }
}

TEST_F(SerialTestFixture, BoardAllData)
{
    auto  serial = Serial(serial_string_custom);
    Board board = serial.get_board();
    for (char col = 'A'; col <= 'S'; col++)
    {
        for (int row = 1; row <= 19; row++)
        {
            std::string position = std::string(1, col) + std::to_string(row);

            // Center is white
            if (position == "J10")
            {
                EXPECT_EQ(board.get_stone(position), 'W');
                continue;
            }

            EXPECT_EQ(board.get_stone(position), 'O');
        }
    }

    EXPECT_EQ(board.get_no_captured_pairs('W'), 10);
    EXPECT_EQ(board.get_no_captured_pairs('B'), 20);
}