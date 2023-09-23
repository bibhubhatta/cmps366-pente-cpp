#include "Tournament.h"
#include "Computer.h"
#include "Human.h"

Tournament::Tournament() = default;

void Tournament::add_player(Player* player) { roster.add_player(player); }

void Tournament::play_a_round()
{
    Round round(roster);
    round.play();
    update_scores(round);
}

void Tournament::update_scores(const Round& round)
{
    for (auto player : roster.get_players())
    {
        roster.add_score(player, round.get_score(player));
    }
}

Roster Tournament::get_roster() const { return roster; }

Player* Tournament::get_winner() const { return roster.get_winner(); }
