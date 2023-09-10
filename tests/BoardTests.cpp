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

        test_diagonal = test_board;
        test_diagonal[19 + 2] = 'B';
    }

    std::string test_board;
    std::string test_diagonal;
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

TEST_F(BoardTests, getMainDiagonal)
{
    Board board = Board::from_string(test_board, 0, 0);

    std::string       position = "J10";
    std::vector<char> center_diagonal = board.get_main_diagonal(position);

    std::vector<char> expected_diagonal = {'O', 'O', 'O', 'O', 'O', 'O', 'O',
                                           'O', 'O', 'W', 'O', 'O', 'O', 'O',
                                           'O', 'O', 'O', 'O', 'O'};
    EXPECT_EQ(center_diagonal, expected_diagonal);

    Board             board2 = Board::from_string(test_diagonal, 0, 0);
    std::string       position2 = "C2";
    std::vector<char> diagonal2 = board2.get_main_diagonal(position2);

    std::vector<char> expected_diagonal2(18, 'O');
    expected_diagonal2[1] = 'B';

    EXPECT_EQ(diagonal2, expected_diagonal2);
}

TEST_F(BoardTests, getAntiDiagonal)
{
    Board board = Board::from_string(test_board, 0, 0);

    std::string       position = "J10";
    std::vector<char> center_anti_diagonal = board.get_anti_diagonal(position);

    std::vector<char> expected_anti_diagonal = {
        'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'W',
        'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O'};
    EXPECT_EQ(center_anti_diagonal, expected_anti_diagonal);

    Board             board2 = Board::from_string(test_diagonal, 0, 0);
    std::string       position2 = "C2";
    std::vector<char> anti_diagonal2 = board2.get_anti_diagonal(position2);

    std::vector<char> expected_anti_diagonal2(4, 'O');
    expected_anti_diagonal2[1] = 'B';

    EXPECT_EQ(anti_diagonal2, expected_anti_diagonal2);
}
