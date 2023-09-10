#include <gtest/gtest.h>

#include "Board.h"

class BoardTests : public ::testing::Test
{
  public:
    void SetUp() override
    {
        test_board = "OOOOOOOOOOOOOOOOOOO"
                     "OOOOOOOOOOOOOOOOOOO"
                     "OOOOOOOOOOOOOOOOOOO"
                     "OOOOOOOOOOOOOOOOOOO"
                     "OOOOOOOOOOOOOOOOOOO"
                     "OOOOOOOOOOOOOOOOOOO"
                     "OOOOOOOOOOOOOOOOOOO"
                     "OOOOOOOOOOOOOOOOOOO"
                     "OOOOOOOOOOOOOOOOOOO"
                     "OOOOOOOOOWOOOOOOOOO"
                     "OOOOOOOOOOOOOOOOOOO"
                     "OOOOOOOOOOOOOOOOOOO"
                     "OOOOOOOOOOOOOOOOOOO"
                     "OOOOOOOOOOOOOOOOOOO"
                     "OOOOOOOOOOOOOOOOOOO"
                     "OOOOOOOOOOOOOOOOOOO"
                     "OOOOOOOOOOOOOOOOOOO"
                     "OOOOOOOOOOOOOOOOOOO"
                     "OOOOOOOOOOOOOOOOOOO";
    }

    std::string test_board;
};

TEST_F(BoardTests, getRow)
{
    Board board = Board::from_string(test_board, 0, 0);

    std::string       position = "J10";
    std::vector<char> center_row = board.get_row(position);

    std::vector<char> expected_row = {'O', 'O', 'O', 'O', 'O', 'O', 'O',
                                      'O', 'O', 'W', 'O', 'O', 'O', 'O',
                                      'O', 'O', 'O', 'O', 'O'};
    EXPECT_EQ(center_row, expected_row);
}

TEST_F(BoardTests, getCol)
{
    Board board = Board::from_string(test_board, 0, 0);

    std::string       position = "J10";
    std::vector<char> center_col = board.get_col(position);

    std::vector<char> expected_col = {'O', 'O', 'O', 'O', 'O', 'O', 'O',
                                      'O', 'O', 'W', 'O', 'O', 'O', 'O',
                                      'O', 'O', 'O', 'O', 'O'};
    EXPECT_EQ(center_col, expected_col);
}
