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

TEST(MoveAnalysisTests, winBlockingMove)
{
    Board                    board;
    std::vector<std::string> moves = {"J10", "M10", "I10", "K10",
                                      "H10", "L10", "G10"};

    for (const auto& move : moves)
    {
        board.make_move(move);
    }

    std::string win_blocking_move = "F10";

    auto move_analysis = MoveAnalysis(board, win_blocking_move);

    ASSERT_TRUE(move_analysis.is_win_blocking_move());

    // Sanity check; commented out because it takes a long time to run
    //    auto available_positions = board.get_available_positions();
    //    available_positions.erase(win_blocking_move);
    //
    //    for (const auto& position : available_positions)
    //    {
    //        ASSERT_FALSE(MoveAnalysis(board,
    //        position).is_win_blocking_move());
    //    }
}

TEST(MoveAnalysisTests, capturingMove)
{
    Board                    board;
    std::vector<std::string> moves = {"J10", "C4", "E4", "D4"};

    for (const auto& move : moves)
    {
        board.make_move(move);
    }

    std::string capturing_move = "B4";

    auto move_analysis = MoveAnalysis(board, capturing_move);

    ASSERT_TRUE(move_analysis.is_capturing_move());

    // Sanity check
    auto available_moves = board.get_available_positions();
    available_moves.erase(capturing_move);
    for (auto move : available_moves)
    {
        ASSERT_FALSE(MoveAnalysis(board, move).is_capturing_move());
    }
}

TEST(MoveAnalysisTest, pseudoScoreAfterMove)
{
    Board board;

    std::vector<std::pair<std::string, Score>> moves = {
        {"J10", 0}, {"C4", 0}, {"J9", 2}, {"D5", 2}, {"I9", 4}, {"E6", 3}};

    for (const auto& [move, score] : moves)
    {
        MoveAnalysis move_analysis(board, move);
        ASSERT_EQ(move_analysis.pseudo_score_after_move(), score);
        board.make_move(move);
    }
}

TEST(MoveAnalysisTest, opponentWinningMove)
{
    Board board;

    std::vector<std::string> moves = {"J10", "C4", "J9", "D5",
                                      "J8",  "E6", "J7"};

    for (const auto& move : moves)
    {
        MoveAnalysis move_analysis(board, move);
        ASSERT_FALSE(move_analysis.is_opponent_winning_move());
        board.make_move(move);
    }

    std::vector<std::string> opponent_winning_moves = {"J6", "J11"};

    for (const auto& move : opponent_winning_moves)
    {
        MoveAnalysis move_analysis(board, move);
        ASSERT_TRUE(move_analysis.is_opponent_winning_move());
    }
}

TEST(MoveAnalysisTest, opponentWinningMove2)
{
    Board board;

    std::vector<std::string> moves = {
        "J10", "B6", "A7", "B4", "A4", "B2", "A1",  "C5", "D7", "C4",
        "D1",  "C3", "G7", "D6", "G4", "D5", "G1",  "D3", "S1", "D2",
        "S3",  "E5", "S5", "E4", "S7", "E3", "S13", "F6", "S9", "F4",
    };

    for (const auto& move : moves)
    {
        MoveAnalysis move_analysis(board, move);
        std::cout << move;
        ASSERT_FALSE(move_analysis.is_opponent_winning_move());
        board.make_move(move);
    }

    std::vector<std::string> opponent_winning_moves = {"D4"};

    for (const auto& move : opponent_winning_moves)
    {
        MoveAnalysis move_analysis(board, move);
        ASSERT_TRUE(move_analysis.is_opponent_winning_move());
    }
}