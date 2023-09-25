#pragma once

#include "Board.h"
#include "Computer.h"
#include "Human.h"
#include "Roster.h"
#include <string>

using MoveHistory = std::vector<std::pair<Player*, Position>>;

class Round
{
  public:
    Round(const Roster& roster);
    Round(const Roster& roster, const Board& board);
    void play();

    Score get_score(Player* player) const;
    Board get_board() const;

    std::vector<Player*> get_players() const;
    Player*              get_winner() const;
    Stone                get_stone(Player* Player) const;
    int                  get_no_captures(Player* Player) const;
    int                  get_no_four_in_sequence(Player* Player) const;

    MoveHistory get_move_history() const;

    std::string get_winning_reason() const;

  private:
    Roster                   roster;
    Board                    board {19, 19};
    std::map<Player*, Stone> player_to_stone;
    MoveHistory              move_history;

    Player*     winner = nullptr;
    bool        is_draw = false;
    bool        is_over = false;
    std::string win_by;

    Player*              first_player() const;
    std::vector<Player*> sorted_players() const;
    Human*               get_human_player() const;
    Player*              get_computer_player() const;
    Player*              next_player(Player* player) const;
};