#include "Tournament.h"
#include "Computer.h"
#include "Human.h"
#include "Serial.h"

Tournament::Tournament() = default;

void Tournament::add_player(Player* player) { roster.add_player(player); }

void Tournament::play_a_round()
{
    if (rounds.empty())
    {
        add_new_round();
    }
    else
    {
        if (rounds.back().is_round_over())
        {
            add_new_round();
        }
    }

    Round& round = rounds.back();
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

void Tournament::update_from_file(const std::string& filename)
{
    Serial serial = Serial::from_file(filename);

    Player* human = roster.get_player_by_name("Human");
    Player* computer = roster.get_player_by_name("Computer");

    roster.add_score(human, serial.get_human_score());
    roster.add_score(computer, serial.get_computer_score());

    Board board = serial.get_board();
    board.get_turn();

    Player* white_player = nullptr;
    Player* black_player = nullptr;

    if (serial.get_human_stone() == Board::WHITE_STONE)
    {
        white_player = human;
        black_player = computer;
    }
    else
    {
        white_player = computer;
        black_player = human;
    }

    Round round(roster, board, white_player, black_player);

    rounds.push_back(round);
}

void Tournament::add_new_round() { rounds.push_back(Round(roster)); }
