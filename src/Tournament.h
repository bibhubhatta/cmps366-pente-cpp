#pragma once

#include "Board.h"
#include "Roster.h"
#include "Round.h"

class Tournament
{
  public:
    Tournament();

    void add_player(Player* player);
    void play_a_round();

  private:
    Roster roster;
    void   update_scores(const Round& round);
};