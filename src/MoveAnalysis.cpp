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
    Board board_ = board;

    // Check if the opponent can win after this move
    bool opponent_can_win = false;
    try
    {
        std::set available_positions = board_.get_available_positions();
        for (const auto& position : available_positions)
        {
            auto board_after_move = board_;
            board_.make_move(position);

            auto opponent_moves = board_after_move.get_available_positions();

            for (const auto& opponent_move : opponent_moves)
            {
                if (MoveAnalysis(board_after_move, opponent_move)
                        .is_winning_move())
                {
                    opponent_can_win = true;
                    break;
                }
            }
        }
    }
    catch (const std::exception& e)
    {
        return false;
    }

    if (opponent_can_win)
    {
        auto board_after_move = board;
        board_after_move.make_move(move);

        for (const auto& position : board_after_move.get_available_positions())
        {
            if (MoveAnalysis(board_after_move, position).is_winning_move())
            {
                return true;
            }
        }
    }

    return false;
}
