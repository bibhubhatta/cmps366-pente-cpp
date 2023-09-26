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
    bool is_opponent_winning_move() const;
    bool is_opponent_scoring_move() const;
    bool is_opponent_capturing_move() const;

    Score pseudo_score_after_move() const;
    Score calculate_pseudo_score(const Board& board_, const Stone& stone) const;

    const Board    board;
    const Position move;
    int            capture_delta() const;
    int            score_delta() const;
    int            opponent_score_delta() const;
    int            opponent_capture_delta() const;
    Score          opponent_pseudo_score_after_move() const;
};
