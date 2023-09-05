#pragma once

#include <vector>

#include "Board.h"
#include "Player.h"
#include "Round.h"

class Tournament
{
  public:
    Tournament();
    void  load(const std::string& filename);
    Board get_current_board();
    int   get_human_score();
    int   get_computer_score();
    Round get_round();

  private:
    std::vector<Round> rounds;
    Human              human;
    Computer           computer;
};