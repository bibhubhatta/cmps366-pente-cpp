#pragma once

#include <string>

#include "Board.h"

class MoveAnalysis
{
  public:
    template <typename T> MoveAnalysis(const Board& board, const T& move);
    bool is_only_move() const;
    bool is_winning_move() const;
    bool is_capturing_move() const;

    /// Checks if the move prevents the opponent from winning on their next move
    /// Returns false if the opponent can win on their next move, otherwise
    /// it will return true; even if the move is a winning move for the player
    /// \return
    bool is_win_blocking_move() const;
    bool is_losing_move() const;

    Score pseudo_score_after_move() const;

    const Board    board;
    const Position move;
    int            capture_differential() const;
};
