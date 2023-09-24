#include <fmt/format.h>
#include <iostream>
#include <tabulate/table.hpp>

#include "TournamentAnnouncement.h"
#include "UnicodeDisplayHelpers.h"

using namespace tabulate;

TournamentAnnouncement::TournamentAnnouncement(const Tournament& tournament)
    : tournament(tournament)
{
}

void TournamentAnnouncement::announce_results() const
{
    Table scores_table = get_scores_table();
    use_unicode_borders(scores_table);

    fmt::print("Tournament Results:\n");
    fmt::print("{}\n", scores_table.str());

    if (tournament.get_winner() == nullptr)
    {
        fmt::print("Tournament ended in a draw.\n");
        return;
    }

    Table winner_table;
    winner_table.add_row({"Winner", tournament.get_winner()->name});
    use_unicode_borders(winner_table);
    
    fmt::print("Tournament Winner:\n");
    fmt::print("{}\n", winner_table.str());
}

tabulate::Table TournamentAnnouncement::get_scores_table() const
{
    Roster tournament_roster = tournament.get_roster();
    Table  scores_table;
    scores_table.add_row({"Player", "Score"});
    for (auto player : tournament_roster.get_players())
    {
        scores_table.add_row(
            {player->name,
             std::to_string(tournament_roster.get_score(player))});
    }
    return scores_table;
}

void TournamentAnnouncement::announce_scores() const
{
    fmt::print("Tournament Scores:\n");
    tabulate::Table scores_table = get_scores_table();
    use_unicode_borders(scores_table);
    fmt::print("{}\n", scores_table.str());
}
