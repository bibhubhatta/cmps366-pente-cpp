#pragma once

#include "Board.h"

class BoardDisplay
{
  public:
    BoardDisplay(const Board& board);
    void render() const;

  private:
    const Board& board;
};
