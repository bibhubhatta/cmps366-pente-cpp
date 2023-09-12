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

TEST_F(BoardTests, getNoStoneOnBoard)
{
    Board board = Board::from_string(test_board, 0, 0);

    EXPECT_EQ(board.get_no_stone_on_board('O'), 19 * 19 - 1);
    EXPECT_EQ(board.get_no_stone_on_board('W'), 1);
    EXPECT_EQ(board.get_no_stone_on_board('B'), 0);
}

TEST_F(BoardTests, getTotalNoStoneOnBoard)
{
    // Board after capturing a black pair at B1 and C1
    test_board[0] = 'W';
    test_board[3] = 'W';
    int   no_black_pairs_captured = 1;
    int   no_white_pairs_captured = 0;
    Board board = Board::from_string(test_board, no_white_pairs_captured,
                                     no_black_pairs_captured);

    EXPECT_EQ(board.get_total_no_stone_played('W'), 3);
    EXPECT_EQ(board.get_total_no_stone_played('B'), 2);
}

TEST_F(BoardTests, getTurn)
{
    Board board = Board::from_string(test_board, 0, 0);
    EXPECT_EQ(board.get_turn(), 'B');
}

TEST_F(BoardTests, getTurn2)
{
    // Board after capturing a black pair at B1 and C1
    test_board[0] = 'W';
    test_board[3] = 'W';
    int   no_black_pairs_captured = 1;
    int   no_white_pairs_captured = 0;
    Board board = Board::from_string(test_board, no_white_pairs_captured,
                                     no_black_pairs_captured);
    EXPECT_EQ(board.get_turn(), 'B');
}

TEST_F(BoardTests, getTurn3)
{
    // Board at the start of the game
    Board board;
    EXPECT_EQ(board.get_turn(), 'W');
}

TEST_F(BoardTests, getInvalidTurn)
{
    test_board[0] = 'W';

    Board board = Board::from_string(test_board, 0, 0);
    EXPECT_THROW(board.get_turn(), std::runtime_error);
}

TEST_F(BoardTests, getAvailablePositions_FirstMove)
{
    Board              board(19, 19);
    std::set<Position> available_positions = board.get_available_positions();

    EXPECT_EQ(available_positions.size(), 1);
    EXPECT_EQ(available_positions.begin()->to_string(), "J10");
}

TEST_F(BoardTests, getAvailablePositions_SecondMove)
{
    // Use a 7x7 board to make the test easier
    std::string board_str;
    for (int i = 0; i < 7; i++)
    {
        board_str += "OOOOOOO";
    }
    board_str[24] = 'W';

    Board              board = Board::from_string(board_str, 0, 0, 7, 7);
    std::set<Position> available_positions = board.get_available_positions();

    // All the positions 3 intersections away from the center are available
    // In a 7x7 board, they are all at the edge of the board
    EXPECT_EQ(available_positions.size(), 24);

    std::set<Position> expected_available_positions;

    for (int i = 0; i < 7; i++)
    {
        expected_available_positions.insert({0, i});
        expected_available_positions.insert({6, i});
        expected_available_positions.insert({i, 0});
        expected_available_positions.insert({i, 6});
    }

    EXPECT_EQ(expected_available_positions, available_positions);
}