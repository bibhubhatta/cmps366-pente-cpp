#pragma once

#include <map>
#include <set>
#include <string>
#include <vector>

#include "Position.h"

typedef char               Stone;
typedef std::vector<Stone> StoneSequence;

class Board
{
  public:
    Board(int now_rows = 19, int no_cols = 19);

    const int no_rows;
    const int no_cols;

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
                             int no_captured_black_pairs, int no_rows = 19,
                             int no_cols = 19);

    template <typename T> Stone get_stone(const T& position) const;

    int get_no_captured_pairs(Stone stone) const;

    template <typename T> StoneSequence get_row(T& position) const;

    template <typename T> StoneSequence get_col(T& position) const;

    template <typename T> StoneSequence get_main_diagonal(T& position) const;

    template <typename T> StoneSequence get_anti_diagonal(T& position) const;

    /// \brief Returns the number of stones of a given color on the board
    /// This only counts the stones on the board, not the captured stones
    /// \param stone
    /// \return
    int get_no_stone_on_board(Stone stone) const;

    /// \brief Returns the total number of stones on the board
    /// This also counts the captured stones
    /// \param stone
    /// \return
    int get_total_no_stone_played(Stone stone) const;

    /// \brief Returns the stone of the player whose turn it is
    /// \return
    Stone get_turn() const;

    std::set<Position> get_available_positions() const;

    template <typename T> void make_move(const T& position);

  private:
    StoneSequence        board;
    std::map<Stone, int> captured_pairs;

    Stone get_stone(int row, int col) const;

    template <typename T> void set_stone(const T& position, Stone stone);

    // These are private because the row and col indices are 0-based in the
    // internal representation, but 1-based in the external representation
    StoneSequence get_row(int row) const;

    StoneSequence get_col(int col) const;

    Position           get_center() const;
    std::set<Position> get_empty_positions() const;
    int                get_no_moves_so_far() const;

    template <typename T> void handle_capture(const T& position);
};
