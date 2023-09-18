#pragma once

#include <string>

#include "Board.h"

class MoveAnalysis
{
  public:
    template <typename T> MoveAnalysis(const Board& board, const T& move);
    bool is_only_move() const;
    bool is_winning_move() const;
    bool is_win_blocking_move() const;

    const Board    board;
    const Position move;
};
