#include "Board.h"

Board::Board()
{

    // Initialize board with empty stones
    for (int i = 0; i < 19; i++)
    {
        StoneSequence row;
        for (int j = 0; j < 19; j++)
        {
            row.push_back('O');
        }
        board.push_back(row);
    }

    // Initialize captured pairs
    // The number of captured pairs is the numbers of pairs lost, ie, captured
    // by the opponent
    captured_pairs['W'] = 0;
    captured_pairs['B'] = 0;
}

template <typename T> Stone Board::get_stone(const T& position) const
{
    Position position_ {position};
    int      row = position_.row;
    int      col = position_.col;

    return board[row][col];
}

template Stone Board::get_stone<Position>(const Position& position) const;
template Stone Board::get_stone<std::string>(const std::string& position) const;

template <typename T> void Board::set_stone(const T& position, Stone stone)
{
    Position position_ {position};
    int      row = position_.row;
    int      col = position_.col;

    // TODO: Raise exception if stone is already set

    board[row][col] = stone;
}

template void Board::set_stone<Position>(const Position& position, Stone stone);
template void Board::set_stone<std::string>(const std::string& position,
                                            Stone              stone);

Board Board::from_string(const std::string& board_string,
                         const int          no_captured_white_pairs,
                         const int          no_captured_black_pairs)
{
    auto board_ = Board();

    // Loop through board string and set stones
    for (int row = 0; row < 19; row++)
    {
        for (int col = 0; col < 19; col++)
        {
            std::string position =
                std::string(1, 'A' + col) + std::to_string(row + 1);
            Stone stone = board_string[row * 19 + col];
            board_.set_stone(position, stone);
        }
    }

    board_.captured_pairs['W'] = no_captured_white_pairs;
    board_.captured_pairs['B'] = no_captured_black_pairs;

    return board_;
}

int Board::get_no_captured_pairs(Stone stone) const
{
    // The number of captured pairs is the numbers of pairs lost for a stone,
    // ie, captured by the opponent
    return captured_pairs.at(stone);
}

StoneSequence Board::get_row(int row) const { return board[row]; }

template <typename T> StoneSequence Board::get_row(T& position) const
{
    Position position_ {position};
    int      row = position_.row;

    return board[row];
}

template StoneSequence Board::get_row<Position>(Position& position) const;
template StoneSequence Board::get_row<std::string>(std::string& position) const;

StoneSequence Board::get_col(int col) const
{
    StoneSequence col_;
    for (int row = 0; row < 19; row++)
    {
        col_.push_back(board[row][col]);
    }
    return col_;
}

template <typename T> StoneSequence Board::get_col(T& position) const
{
    Position position_ {position};
    int      col = position_.col;

    return get_col(col);
}

template StoneSequence Board::get_col<Position>(Position& position) const;
template StoneSequence Board::get_col<std::string>(std::string& position) const;

template <typename T> StoneSequence Board::get_main_diagonal(T& position) const
{
    Position position_ {position};
    int      row = position_.row;
    int      col = position_.col;

    StoneSequence diagonal;

    // Find the start of the diagonal
    int start_row = row;
    int start_col = col;
    while (start_row > 0 && start_col > 0)
    {
        start_row--;
        start_col--;
    }

    // Find the end of the diagonal
    int end_row = row;
    int end_col = col;
    while (end_row < 18 && end_col < 18)
    {
        end_row++;
        end_col++;
    }

    // Add the diagonal to the vector
    for (int i = start_row, j = start_col; i <= end_row && j <= end_col;
         i++, j++)
    {
        diagonal.push_back(board[i][j]);
    }

    return diagonal;
}

template StoneSequence
Board::get_main_diagonal<Position>(Position& position) const;
template StoneSequence
Board::get_main_diagonal<std::string>(std::string& position) const;

template <typename T> StoneSequence Board::get_anti_diagonal(T& position) const
{
    Position position_ {position};
    int      row = position_.row;
    int      col = position_.col;

    StoneSequence diagonal;

    // Find the start of the diagonal
    int start_row = row;
    int start_col = col;
    while (start_row > 0 && start_col < 18)
    {
        start_row--;
        start_col++;
    }

    // Find the end of the diagonal
    int end_row = row;
    int end_col = col;
    while (end_row < 18 && end_col > 0)
    {
        end_row++;
        end_col--;
    }

    // Add the diagonal to the vector
    for (int i = start_row, j = start_col; i <= end_row && j >= end_col;
         i++, j--)
    {
        diagonal.push_back(board[i][j]);
    }

    return diagonal;
}

template StoneSequence
Board::get_anti_diagonal<Position>(Position& position) const;
template StoneSequence
Board::get_anti_diagonal<std::string>(std::string& position) const;