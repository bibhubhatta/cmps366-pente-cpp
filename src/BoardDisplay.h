#pragma once

#include <unordered_map>

#include "Board.h"

class BoardDisplay
{
  public:
    BoardDisplay(const Board& board);
    void render() const;

  private:
    const Board&                                board;
    const std::unordered_map<char, std::string> stone_representation = {
        {'O', ""}, {'B', "B"}, {'W', "W"}};
};