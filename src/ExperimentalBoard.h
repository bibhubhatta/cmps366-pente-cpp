#pragma once

#include "Board.h"

class ExperimentalBoard : public Board
{
  public:
    template <typename T> void set_stone(const T& position, Stone stone);
};

template <typename T>
void ExperimentalBoard::set_stone(const T& position, Stone stone)
{
    Board::set_stone(position, stone);
}
