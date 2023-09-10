#pragma once

#include "Position.h"
#include <map>
#include <string>
#include <vector>

class Board
{
  public:
    Board();

    /// \brief Creates a board from a string; the string must be a single line
    /// of 19x19 characters, where each character is either 'O', 'W', or 'B'.
    /// \param board_string
    /// \param no_captured_white_pairs
    /// The number of white captured pairs, ie, the number of pairs captured by
    /// the black player
    /// \param no_captured_black_pairs
    /// The number of black captured pairs, ie, the number of pairs captured by
    /// the white player
    /// \return Board
    static Board from_string(const std::string& board_string,
                             int                no_captured_white_pairs,
                             int                no_captured_black_pairs);

    template <typename T> char get_stone(const T& position) const;

    int get_no_captured_pairs(char stone) const;

  private:
    std::vector<std::vector<char>> board;
    std::map<char, int>            captured_pairs;

    template <typename T> void set_stone(const T& position, char stone);
};
