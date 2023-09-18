#include "MoveAnalysis.h"
#include "Exceptions.h"

template <typename T>
MoveAnalysis::MoveAnalysis(const Board board, T move) : board(board), move(move)
{
}

template MoveAnalysis::MoveAnalysis(const Board board, std::string move);
template MoveAnalysis::MoveAnalysis(const Board board, Position move);

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
