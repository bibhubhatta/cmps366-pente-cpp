#pragma once

#include <string>

#include "Board.h"
#include "Position.h"

class Player
{
  public:
    Player(const std::string& name) : name(name) {};

    const std::string name;

    virtual Position get_move(const Board& board) const = 0;
};
