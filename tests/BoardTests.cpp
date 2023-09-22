#include <gtest/gtest.h>

#include "Board.h"
#include "BoardDisplay.h"
#include "Exceptions.h"

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

TEST_F(BoardTests, getAvailablePositions_ThirdMove)
{
    std::string board_str;
    for (int i = 0; i < 19; i++)
    {
        for (int j = 0; j < 19; j++)
        {
            board_str += "O";
        }
    }

    board_str[9 * 19 + 9] = 'W';
    board_str[0] = 'B';

    Board              board = Board::from_string(board_str, 0, 0, 19, 19);
    std::set<Position> available_positions = board.get_available_positions();

    // All the positions except the center and A1 are available
    std::set<Position> expected_available_positions;

    for (int row = 0; row < 19; row++)
    {
        for (int col = 0; col < 19; col++)
        {
            expected_available_positions.insert({row, col});
        }
    }

    expected_available_positions.erase({0, 0});
    expected_available_positions.erase({9, 9});

    EXPECT_EQ(expected_available_positions, available_positions);
}

TEST_F(BoardTests, makeMove)
{
    Board board;
    board.make_move(std::string("J10"));
    EXPECT_EQ(board.get_stone(Position(9, 9)), 'W');
}

TEST_F(BoardTests, makeIllegalFirstMove)
{
    Board board;
    EXPECT_THROW(board.make_move(std::string("J9")), InvalidMove);
}

TEST_F(BoardTests, makeIllegalSecondMove)
{
    Board board;
    board.make_move(std::string("J10"));
    EXPECT_THROW(board.make_move(std::string("J9")), InvalidMove);
}

TEST_F(BoardTests, makeIllegalThirdMove)
{
    Board board;
    board.make_move(std::string("J10"));
    board.make_move(std::string("A11"));
    EXPECT_THROW(board.make_move(std::string("J10")), InvalidMove);
}

TEST_F(BoardTests, makeMoveOutsideBoard)
{
    Board board;

    board.make_move(std::string("J10"));
    board.make_move(std::string("A11"));
    EXPECT_THROW(board.make_move(std::string("T20")), InvalidMove);
}

TEST_F(BoardTests, capturePairToLeft)
{
    Board board;

    board.make_move(std::string("J10"));
    board.make_move(std::string("M10"));
    board.make_move(std::string("K10"));
    board.make_move(std::string("L10"));

    EXPECT_EQ(board.get_no_captured_pairs('B'), 0);
    board.make_move(std::string("N10"));

    EXPECT_EQ(board.get_stone(std::string("K10")), 'W');
    EXPECT_EQ(board.get_stone(std::string("L10")), 'O');
    EXPECT_EQ(board.get_stone(std::string("M10")), 'O');
    EXPECT_EQ(board.get_stone(std::string("N10")), 'W');

    EXPECT_EQ(board.get_no_captured_pairs('B'), 1);
}

TEST_F(BoardTests, capturePairToRight)
{
    Board board;

    board.make_move(std::string("J10"));
    board.make_move(std::string("G10"));
    board.make_move(std::string("I10"));
    board.make_move(std::string("H10"));

    EXPECT_EQ(board.get_no_captured_pairs('B'), 0);
    board.make_move(std::string("F10"));

    EXPECT_EQ(board.get_stone(std::string("F10")), 'W');
    EXPECT_EQ(board.get_stone(std::string("G10")), 'O');
    EXPECT_EQ(board.get_stone(std::string("H10")), 'O');
    EXPECT_EQ(board.get_stone(std::string("I10")), 'W');

    EXPECT_EQ(board.get_no_captured_pairs('B'), 1);
}

TEST_F(BoardTests, capturePairBelow)
{
    Board board;

    std::vector<std::string> moves = {"J10", "G10", "G9", "G11"};

    for (auto& move : moves)
    {
        board.make_move(move);
    }

    EXPECT_EQ(board.get_no_captured_pairs('B'), 0);
    board.make_move(std::string("G12"));

    EXPECT_EQ(board.get_stone(std::string("G9")), 'W');
    EXPECT_EQ(board.get_stone(std::string("G10")), 'O');
    EXPECT_EQ(board.get_stone(std::string("G11")), 'O');
    EXPECT_EQ(board.get_stone(std::string("G12")), 'W');

    EXPECT_EQ(board.get_no_captured_pairs('B'), 1);
}

TEST_F(BoardTests, capturePairAbove)
{
    Board board;

    std::vector<std::string> moves = {"J10", "N17", "N19", "N18"};

    for (auto& move : moves)
    {
        board.make_move(move);
    }

    EXPECT_EQ(board.get_no_captured_pairs('B'), 0);
    board.make_move(std::string("N16"));

    EXPECT_EQ(board.get_stone(std::string("N16")), 'W');
    EXPECT_EQ(board.get_stone(std::string("N17")), 'O');
    EXPECT_EQ(board.get_stone(std::string("N18")), 'O');
    EXPECT_EQ(board.get_stone(std::string("N19")), 'W');

    EXPECT_EQ(board.get_no_captured_pairs('B'), 1);
}

TEST_F(BoardTests, capturePairDiagonalDownRight)
{
    Board board;

    std::vector<std::string> moves = {"J10", "Q1", "O3", "M5", "P2"};

    for (auto& move : moves)
    {
        board.make_move(move);
    }

    EXPECT_EQ(board.get_no_captured_pairs('W'), 0);

    board.make_move(std::string("N4"));

    EXPECT_EQ(board.get_stone(std::string("N4")), 'B');
    EXPECT_EQ(board.get_stone(std::string("O3")), 'O');
    EXPECT_EQ(board.get_stone(std::string("P2")), 'O');
    EXPECT_EQ(board.get_stone(std::string("Q1")), 'B');

    EXPECT_EQ(board.get_no_captured_pairs('W'), 1);
}

TEST_F(BoardTests, capturePairDiagonalUpRight)
{
    Board board;

    std::vector<std::string> moves = {"J10", "D18", "E19", "C17"};

    for (auto& move : moves)
    {
        board.make_move(move);
    }

    EXPECT_EQ(board.get_no_captured_pairs('B'), 0);

    board.make_move(std::string("B16"));

    EXPECT_EQ(board.get_stone(std::string("B16")), 'W');
    EXPECT_EQ(board.get_stone(std::string("C17")), 'O');
    EXPECT_EQ(board.get_stone(std::string("D18")), 'O');
    EXPECT_EQ(board.get_stone(std::string("E19")), 'W');
}

TEST_F(BoardTests, capturePairDiagonalDownLeft)
{
    Board board;

    std::vector<std::string> moves = {"J10", "A1", "B2", "E5", "C3"};

    for (auto& move : moves)
    {
        board.make_move(move);
    }

    EXPECT_EQ(board.get_no_captured_pairs('W'), 0);

    board.make_move(std::string("D4"));

    EXPECT_EQ(board.get_stone(std::string("D4")), 'B');
    EXPECT_EQ(board.get_stone(std::string("C3")), 'O');
    EXPECT_EQ(board.get_stone(std::string("B2")), 'O');
    EXPECT_EQ(board.get_stone(std::string("A1")), 'B');

    EXPECT_EQ(board.get_no_captured_pairs('W'), 1);
}

TEST_F(BoardTests, capturePairDiagonalUpLeft)
{
    Board board;

    std::vector<std::string> moves = {"J10", "R17", "P19", "Q18"};

    for (auto& move : moves)
    {
        board.make_move(move);
    }

    EXPECT_EQ(board.get_no_captured_pairs('B'), 0);

    board.make_move(std::string("S16"));

    EXPECT_EQ(board.get_stone(std::string("S16")), 'W');
    EXPECT_EQ(board.get_stone(std::string("R17")), 'O');
    EXPECT_EQ(board.get_stone(std::string("Q18")), 'O');
    EXPECT_EQ(board.get_stone(std::string("P19")), 'W');

    EXPECT_EQ(board.get_no_captured_pairs('B'), 1);
}

TEST_F(BoardTests, multipleCaptures)
{
    Board board;

    std::vector<std::string> moves = {
        "J10", "B6", "A7", "B4", "A4",  "B2", "A1", "C5", "D7",  "C4", "D1",
        "C3",  "G7", "D6", "G4", "D5",  "G1", "D3", "S1", "D2",  "S3", "E5",
        "S5",  "E4", "S7", "E3", "S13", "F6", "S9", "F4", "S11", "F2"};

    for (auto& move : moves)
    {
        board.make_move(move);
    }

    EXPECT_EQ(board.get_no_captured_pairs('B'), 0);

    try
    {
        board.make_move(std::string("D4"));
    }
    catch (const GameWon& e)
    {
        // This is expected because the move captures more than 5 pairs
    }

    for (int i = 0; i < moves.size(); i += 2)
    {
        EXPECT_EQ(board.get_stone(moves[i]), 'W');
    }

    for (int i = 1; i < moves.size(); i += 2)
    {
        EXPECT_EQ(board.get_stone(moves[i]), 'O');
    }

    EXPECT_EQ(board.get_no_captured_pairs('B'), 8);
}

TEST_F(BoardTests, winBy5InRow)
{
    Board board;

    std::vector<std::string> moves = {"J10", "C16", "K10", "D16",
                                      "L10", "E16", "M10", "F16"};

    for (auto& move : moves)
    {
        board.make_move(move);
    }

    BoardDisplay board_display(board);
    board_display.render();

    try
    {
        board.make_move(std::string("N10"));
        FAIL() << "Expected GameWon exception"
               << "\n";
    }
    catch (const GameWon& e)
    {
        EXPECT_EQ(e.winner, 'W');
        EXPECT_EQ(e.reason, "5 in a row");
    }
}

TEST_F(BoardTests, winBy5InCol)
{
    Board board;

    std::vector<std::string> moves = {"J10", "S15", "J9",  "S16", "J8",
                                      "S17", "J7",  "S18", "J5"};

    for (auto& move : moves)
    {
        board.make_move(move);
    }

    BoardDisplay board_display(board);
    board_display.render();

    try
    {
        board.make_move(std::string("S19"));
        FAIL() << "Expected GameWon exception"
               << "\n";
    }
    catch (const GameWon& e)
    {
        EXPECT_EQ(e.winner, 'B');
        EXPECT_EQ(e.reason, "5 in a column");
    }
}

TEST_F(BoardTests, winBy5InMainDiagonal)
{
    Board board;

    std::vector<std::string> moves = {"J10", "S15", "I5",  "S16", "H4",
                                      "S17", "G3",  "S18", "F2",  "S1"};

    for (auto& move : moves)
    {
        board.make_move(move);
    }

    BoardDisplay board_display(board);
    board_display.render();

    try
    {
        board.make_move(std::string("E1"));
        FAIL() << "Expected GameWon exception"
               << "\n";
    }
    catch (const GameWon& e)
    {
        EXPECT_EQ(e.winner, 'W');
        EXPECT_EQ(e.reason, "5 in a diagonal");
    }
}

TEST_F(BoardTests, winBy5InAntiDiagonal)
{
    Board board;

    std::vector<std::string> moves = {"J10", "O19", "J11", "P18", "I10",
                                      "Q17", "H9",  "R16", "G8"};

    for (auto& move : moves)
    {
        board.make_move(move);
    }

    BoardDisplay board_display(board);
    board_display.render();

    try
    {
        board.make_move(std::string("S15"));
        FAIL() << "Expected GameWon exception"
               << "\n";
    }
    catch (const GameWon& e)
    {
        EXPECT_EQ(e.winner, 'B');
        EXPECT_EQ(e.reason, "5 in a diagonal");
    }
}

TEST_F(BoardTests, winBy5Captures)
{
    Board board;

    std::vector<std::string> moves = {
        "J10", "B6", "A7", "B4", "A4",  "B2", "A1", "C5", "D7",  "C4", "D1",
        "C3",  "G7", "D6", "G4", "D5",  "G1", "D3", "S1", "D2",  "S3", "E5",
        "S5",  "E4", "S7", "E3", "S13", "F6", "S9", "F4", "S11", "F2"};

    for (auto& move : moves)
    {
        board.make_move(move);
    }

    BoardDisplay board_display(board);
    board_display.render();

    try
    {
        board.make_move(std::string("D4"));
        FAIL() << "Expected GameWon exception"
               << "\n";
    }
    catch (const GameWon& e)
    {
        EXPECT_EQ(e.winner, 'W');
        EXPECT_EQ(e.reason, "5 or more pairs captures");
    }
}

TEST_F(BoardTests, getStoneSequences)
{
    Board board;

    std::vector<std::string> moves = {"J10", "N10", "K10", "O10", "L10", "C10",
                                      "F10", "D10", "G10", "B10", "Q10"};

    for (auto& move : moves)
    {
        board.make_move(move);
    }

    BoardDisplay board_display(board);
    board_display.render();

    std::vector<StoneSequence> expected_stone_sequences = {
        StoneSequence(3, Board::BLACK_STONE),
        StoneSequence(2, Board::WHITE_STONE),
        StoneSequence(3, Board::WHITE_STONE),
        StoneSequence(2, Board::BLACK_STONE),
        StoneSequence(1, Board::WHITE_STONE),
    };

    std::string                position = "J10";
    StoneSequence              row = board.get_row(position);
    std::vector<StoneSequence> stone_sequences =
        Board::get_stone_sequences(row);

    EXPECT_EQ(stone_sequences, expected_stone_sequences);
}

TEST_F(BoardTests, getStoneSequencesForParticularStone)
{
    Board board;

    std::vector<int> row_nums {10, 1, 9, 3, 17, 4, 8, 5, 16, 6};

    for (const int& row_num : row_nums)
    {
        std::string move {"J" + std::to_string(row_num)};
        board.make_move(move);
    }

    BoardDisplay board_display(board);
    board_display.render();

    std::vector<StoneSequence> expected_black_stone_sequences = {
        StoneSequence(1, Board::BLACK_STONE),
        StoneSequence(4, Board::BLACK_STONE),
    };

    std::vector<StoneSequence> expected_white_stone_sequences = {
        StoneSequence(3, Board::WHITE_STONE),
        StoneSequence(2, Board::WHITE_STONE),
    };

    std::string   position = "J10";
    StoneSequence col = board.get_col(position);

    std::vector<StoneSequence> stone_sequences =
        Board::get_stone_sequences(col);

    EXPECT_EQ(Board::get_stone_sequences(col, Board::WHITE_STONE),
              expected_white_stone_sequences);

    EXPECT_EQ(Board::get_stone_sequences(col, Board::BLACK_STONE),
              expected_black_stone_sequences);
}
