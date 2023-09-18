#include "MoveAnalysis.h"
#include "Exceptions.h"
#include <algorithm>

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
