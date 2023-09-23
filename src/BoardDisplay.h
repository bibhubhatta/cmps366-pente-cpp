#pragma once

#include <unordered_map>

#include "tabulate/table.hpp"

#include "Board.h"

class BoardDisplay
{
  public:
    BoardDisplay(const Board& board);

    tabulate::Table board_grid() const;

    void render() const;

  private:
    const Board&                                board;
    const std::unordered_map<char, std::string> stone_representation = {
        {'O', ""}, {'B', "B"}, {'W', "W"}};
};