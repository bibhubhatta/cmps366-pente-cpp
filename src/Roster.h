#pragma once

#include <map>
#include <memory>
#include <vector>

#include "Player.h"

typedef int Score;

class Roster {
public:
    Roster() = default;

    // player is not const because it is being added to a vector
    // and the only way to store it is as a pointer; pointers' objects
    // cannot be const
    void add_player(Player &player);

    void add_score(const Player &player, Score score);

    Score get_score(const Player &player) const;

private:
    // Storing pointers because Player is an abstract class
    std::vector<Player *> players;
    // Mapping player to score using string because I could not figure out how
    // to use Player/pointer to player as a key
    std::map<std::string, Score> scores;
};
