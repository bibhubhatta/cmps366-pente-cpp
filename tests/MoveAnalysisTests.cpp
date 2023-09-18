#include <gtest/gtest.h>

#include "MoveAnalysis.h"

TEST(MoveAnalysisTests, firstMove)
{
    Board       board;
    std::string move = "J10";
    auto        move_analysis = MoveAnalysis(board, move);

    ASSERT_TRUE(move_analysis.is_only_move());
}

TEST(MoveAnalysisTests, winningMove)
{
    Board                    board;
    std::vector<std::string> moves = {"J10", "B2",  "N12", "C2", "O11",
                                      "D2",  "P10", "E2",  "Q9"};

    for (const auto& move : moves)
    {
        board.make_move(move);
    }

    std::string black_winning_move = "F2";

    auto move_analysis = MoveAnalysis(board, black_winning_move);

    ASSERT_FALSE(move_analysis.is_only_move()); // testing another method
    ASSERT_TRUE(move_analysis.is_winning_move());

    std::string stall_move = "P2";
    ASSERT_FALSE(MoveAnalysis(board, stall_move).is_winning_move());
    board.make_move(stall_move);

    auto white_winning_move =
        Position(std::string("R8")); // testing another constructor
    ASSERT_TRUE(MoveAnalysis(board, white_winning_move).is_winning_move());
}