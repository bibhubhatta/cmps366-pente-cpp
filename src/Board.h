#pragma once

#include <string>
#include <vector>

class Position
{
  public:
    Position(int row, int col);
    const int row;
    const int col;
};

class Board
{
  public:
    Board();
    char         get_stone_color(Position position);
    static Board from_string(const std::string& board_string);
};