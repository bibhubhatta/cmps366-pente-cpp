#pragma once

#include <string>
#include <vector>
class Board
{
  public:
    Board();
    static Board from_string(const std::string& board_string);

    char get_stone(const std::string& position) const;

  private:
    std::vector<std::vector<char>> board;
    void set_stone(const std::string& position, char stone);

    static int get_row(const std::string& position);
    static int get_col(const std::string& position);
};
