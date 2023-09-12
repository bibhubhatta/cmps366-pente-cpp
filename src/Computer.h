#pragma once

#include "Player.h"

class Computer : public Player
{
  public:
    using Player::Player;

    Position get_move(const Board& board) const override;
};