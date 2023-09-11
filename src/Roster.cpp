#include "Roster.h"

void Roster::add_player(Player& player)
{
    players.push_back(&player);
    scores[player.name] = 0;
}

void Roster::add_score(const Player& player, Score score)
{
    scores[player.name] += score;
}

Score Roster::get_score(const Player& player) const
{
    return scores.at(player.name);
}
