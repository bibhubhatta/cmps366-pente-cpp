#pragma once

#include <map>
#include <memory>
#include <vector>

#include "Player.h"

using Score = int;

class Roster
{
  public:
    Roster() = default;

    void add_player(Player* player);

    void add_score(Player* player, Score score);

    Score get_score(Player* player) const;

    std::vector<Player*> get_players() const;

    Player* get_player_by_name(const std::string& name) const;

    Player* get_winner() const;

  private:
    // Storing pointers because Player is an abstract class
    std::vector<Player*>     players;
    std::map<Player*, Score> scores;
};
