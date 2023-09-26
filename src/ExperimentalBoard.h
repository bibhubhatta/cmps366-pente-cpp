#pragma once

#include "Board.h"

class ExperimentalBoard : public Board
{
  public:
    template <typename T> void set_stone(const T& position, Stone stone);
    ExperimentalBoard() = default;
    ExperimentalBoard(const Board& board) : Board(board) {};
};

template <typename T>
void ExperimentalBoard::set_stone(const T& position, Stone stone)
{
    Board::set_stone(position, stone);
    Board::handle_capture(position);
}
