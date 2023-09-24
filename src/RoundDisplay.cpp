#include <fmt/format.h>

#include "BoardDisplay.h"
#include "RoundDisplay.h"
#include "UnicodeDisplayHelpers.h"

using namespace tabulate;

tabulate::Table RoundDisplay::get_table() const
{

    Table board_table = BoardDisplay(round.get_board()).board_grid();
    Table score_table = RoundDisplay(round).score_table();
    Table history_table = RoundDisplay(round).history_table(10);

    Table history_and_score_table;
    history_and_score_table.format().width(50).hide_border();
    history_and_score_table.add_row({"Round Details & Scores"});
    history_and_score_table.add_row({score_table});
    history_and_score_table.add_row({"Move History (Last 15 Moves)"});
    history_and_score_table.add_row({history_table});
    history_and_score_table[0]
        .format()
        .font_style({FontStyle::bold})
        .font_align(FontAlign::center);
    history_and_score_table[2]
        .format()
        .font_style({FontStyle::bold})
        .font_align(FontAlign::center);
    history_and_score_table.format().hide_border();

    Table round_table;
    round_table.add_row({board_table, history_and_score_table});

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

tabulate::Table RoundDisplay::history_table(int no_history_entries) const
{
    Table history_table;
    history_table.add_row({"N", "Player", "Move"});

    MoveHistory history = round.get_move_history();

    int move_index = 1;
    if (history.size() > no_history_entries)
    {
        move_index = history.size() - no_history_entries + 1;
        history =
            MoveHistory(history.end() - no_history_entries, history.end());
    }

    for (auto [player, move] : history)
    {
        std::string move_index_str = std::to_string(move_index++);
        std::string player_name = player->name;
        std::string move_str = move.to_string();

        history_table.add_row({move_index_str, player_name, move_str});
    }

    use_unicode_borders(history_table);

    return history_table;
}

void RoundDisplay::show() const
{
    //    std::cout << get_table() << std::endl;
    fmt::print("{}\n", get_table().str());
}

void RoundDisplay::announce_scores_and_winner() const
{
    Table score_table = RoundDisplay(round).score_table();

    Table winner_table;
    winner_table.add_row({"Winner", "Score", "Win By"});
    winner_table.add_row({round.get_winner()->name,
                          std::to_string(round.get_score(round.get_winner())),
                          round.get_winning_reason()});
    use_unicode_borders(winner_table);

    fmt::print("\n{}\n", "Final Round Scores");
    fmt::print("{}\n", score_table.str());
    fmt::print("{}\n", winner_table.str());
}
