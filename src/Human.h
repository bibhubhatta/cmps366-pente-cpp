#pragma once

#include "Player.h"

class Human : public Player
{
  public:
    using Player::Player;

    Position get_move(const Board& board) const override;

    static bool won_toss();
    static bool wants_to_play_again();
};