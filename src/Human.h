#pragma once

#include "Player.h"

class Human : public Player
{
  public:
    using Player::Player;

    Position get_move(const Board& board) const override;
};