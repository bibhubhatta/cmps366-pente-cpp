#pragma once
#include "Board.h"

class Round
{
  public:
    Round(Player white_player = Computer(), Player black_player = Human(),
          Board board = Board(), char next_stone_color = 'W',
          int no_white_pairs_captured = 0, int no_black_pairs_captured = 0);
    Board get_board();

  private:
    Board board;
};