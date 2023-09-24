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
    score_table.add_row({"Player", "Stone", "Captures", "4Seq", "Score"});
    for (auto player : round.get_players())
    {
        std::string player_name = player->name;
        char        stone = round.get_stone(player);
        int         no_captures = round.get_no_captures(player);
        int         no_four_in_sequence = round.get_no_four_in_sequence(player);
        Score       score = round.get_score(player);

        std::string stone_str {stone};

        score_table.add_row(
            {player_name, stone_str, std::to_string(no_captures),
             std::to_string(no_four_in_sequence), std::to_string(score)});
    }

    use_unicode_borders(score_table);

    return score_table;
}

void RoundDisplay::show() const
{
    //    std::cout << get_table() << std::endl;
    fmt::print("{}\n", get_table().str());
}
