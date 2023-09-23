#include <fmt/format.h>
#include <iostream>
#include <tabulate/table.hpp>

#include "TournamentAnnouncement.h"

TournamentAnnouncement::TournamentAnnouncement(const Tournament& tournament)
    : tournament(tournament)
{
}

void TournamentAnnouncement::announce_results() const
{
    Roster tournament_roster = tournament.get_roster();

    using namespace tabulate;
    Table result_table;

    // Header
    result_table.add_row({"Tournament Results"});
    result_table[0]
        .format()
        .font_style({FontStyle::bold})
        .font_align(FontAlign::center);

    Table scores_table;
    scores_table.add_row({"Player", "Score"});
    for (auto player : tournament_roster.get_players())
    {
        scores_table.add_row(
            {player->name,
             std::to_string(tournament_roster.get_score(player))});
    }
    result_table.add_row({scores_table});

    Table winner_table;
    winner_table.add_row({"Winner", tournament.get_winner()->name});
    result_table.add_row({winner_table});

    std::cout << result_table << std::endl;

    fmt::print("Congratulations to {} for winning the tournament!\n",
               tournament.get_winner()->name);
}