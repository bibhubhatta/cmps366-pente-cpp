#pragma once

#include "Board.h"
#include "Computer.h"
#include "Human.h"
#include "Roster.h"

class Round
{
  public:
    Round(const Roster& roster);
    void  play();
    Score get_score(Player* player) const;

  private:
    Roster                   roster;
    Board                    board {19, 19};
    std::map<Player*, Stone> player_to_stone;

    Player* winner = nullptr;
    bool    is_draw = false;
    bool    is_over = false;

    Player*              first_player() const;
    std::vector<Player*> sorted_players() const;
    Human*               get_human_player() const;
    Player*              get_computer_player() const;
    Player*              next_player(Player* player) const;
};