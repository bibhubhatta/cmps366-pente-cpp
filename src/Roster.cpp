#include "Roster.h"

void Roster::add_player(Player* player)
{
    players.push_back(player);
    scores[player] = 0;
}

void Roster::add_score(Player* player, Score score) { scores[player] += score; }

Score Roster::get_score(Player* player) const { return scores.at(player); }

std::vector<Player*> Roster::get_players() const
{
    return std::vector<Player*> {players};
}

Player* Roster::get_player_by_name(const std::string& name) const
{
    for (auto player : players)
    {
        if (player->name == name)
        {
            return player;
        }
    }
    return nullptr;
}
