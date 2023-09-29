#pragma once

#include <string>
#include <vector>

#include "Board.h"

class Serial
{
  public:
    Serial(const std::string& serial_string);

    static Serial from_file(const std::string& filename);

    int get_human_score() const;

    int get_computer_score() const;

    int get_human_captured_pairs() const;

    int get_computer_captured_pairs() const;

    char get_human_stone() const;

    char get_computer_stone() const;

    char get_next_turn() const;

    Board get_board() const;

  private:
    std::vector<std::string> lines;

    int  get_number_in_line(int line_number) const;
    char other_stone(char stone) const;
};
