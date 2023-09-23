#include <fmt/format.h>

#include "BoardDisplay.h"
#include "RoundDisplay.h"
#include "UnicodeDisplayHelpers.h"

using namespace tabulate;

tabulate::Table RoundDisplay::get_table() const
{

    Table board_table = BoardDisplay(round.get_board()).board_grid();
    Table score_table = RoundDisplay(round).score_table();

    Table round_table;
    round_table.add_row({board_table, score_table});

    round_table.format().width(50).hide_border();

    return round_table;
}

tabulate::Table RoundDisplay::score_table() const
{
    Table score_table;
    score_table.add_row({"Player", "Score"});
    for (auto player : round.get_players())
    {
        score_table.add_row(
            {player->name, std::to_string(round.get_score(player))});
    }

    use_unicode_borders(score_table);

    return score_table;
}

void RoundDisplay::show() const
{
    //    std::cout << get_table() << std::endl;
    fmt::print("{}\n", get_table().str());
}
