#pragma once

#include "Board.h"

using StrategicMove = std::pair<Position, std::string>;

class Strategy
{
  public:
    Strategy(Board board) {};

    StrategicMove get_move();

  private:
    Board board;
};
