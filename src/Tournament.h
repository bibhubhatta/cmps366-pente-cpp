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

    Roster  get_roster() const;
    Player* get_winner() const;

    void update_from_file(const std::string& filename);

  private:
    Roster             roster;
    void               update_scores(const Round& round);
    std::vector<Round> rounds;
    void               add_new_round();
};