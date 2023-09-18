#include <algorithm>

#include "Exceptions.h"
#include "MoveAnalysis.h"

template <typename T>
MoveAnalysis::MoveAnalysis(const Board& board, const T& move)
    : board(board), move(move)
{
}

template MoveAnalysis::MoveAnalysis(const Board&       board,
                                    const std::string& move);
template MoveAnalysis::MoveAnalysis(const Board& board, const Position& move);

bool MoveAnalysis::is_only_move() const
{
    return board.get_available_positions().size() == 1;
}

bool MoveAnalysis::is_winning_move() const
{
    Board board_ = board;

    try
    {
        board_.make_move(move);
    }
    catch (const GameWon& e)
    {
        return true;
    }
    catch (const std::exception& e)
    {
        return false;
    }

    return false;
}

bool MoveAnalysis::is_win_blocking_move() const
{
    if (is_winning_move())
    {
        return true;
    }

    Board board_ = board;

    board_.make_move(move);

    auto available_positions = board_.get_available_positions();

    for (const auto& position : available_positions)
    {
        if (MoveAnalysis(board_, position).is_winning_move())
        {
            return false;
        }
    }

    return true;
}

bool MoveAnalysis::is_capturing_move() const
{
    auto current_player = board.get_turn();
    auto opponent = current_player == Board::WHITE_STONE ? Board::BLACK_STONE
                                                         : Board::WHITE_STONE;
    auto captured_pairs_before = board.get_no_captured_pairs(opponent);

    Board board_ = board;

    board_.make_move(move);

    auto captured_pairs_after = board_.get_no_captured_pairs(opponent);

    return captured_pairs_after > captured_pairs_before;
}
