#pragma once

#include <map>
#include <string>
#include <vector>

class Board
{
  public:
    Board();
    static Board from_string(const std::string& board_string,
                             int                no_captured_white_pairs,
                             int                no_captured_black_pairs);

    char get_stone(const std::string& position) const;

    int get_no_captured_pairs(char stone) const;

  private:
    std::vector<std::vector<char>> board;
    std::map<char, int>            captured_pairs;

    void set_stone(const std::string& position, char stone);

    static int get_row(const std::string& position);
    static int get_col(const std::string& position);
};
