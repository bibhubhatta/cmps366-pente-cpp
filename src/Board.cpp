#include "Board.h"

Board::Board()
{

    // Initialize board with empty stones
    for (int i = 0; i < 19; i++)
    {
        std::vector<char> row;
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

char Board::get_stone(const std::string& position) const
{
    int row = get_row_number_from_position_string(position);
    int col = get_col_number_from_position_string(position);
    return board[row][col];
}

void Board::set_stone(const std::string& position, char stone)
{
    int row = get_row_number_from_position_string(position);
    int col = get_col_number_from_position_string(position);

    // TODO: Raise exception if stone is already set

    board[row][col] = stone;
}

int Board::get_row_number_from_position_string(const std::string& position)
{
    int row = std::stoi(position.substr(1, position.length() - 1)) - 1;
    // TODO: Raise exception if position is invalid / out of bounds
    return row;
}

int Board::get_col_number_from_position_string(const std::string& position)
{
    int col = position[0] - 'A';
    // TODO: Raise exception if position is invalid / out of bounds
    return col;
}

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
            char stone = board_string[row * 19 + col];
            board_.set_stone(position, stone);
        }
    }

    board_.captured_pairs['W'] = no_captured_white_pairs;
    board_.captured_pairs['B'] = no_captured_black_pairs;

    return board_;
}

int Board::get_no_captured_pairs(char stone) const
{
    // The number of captured pairs is the numbers of pairs lost for a stone,
    // ie, captured by the opponent
    return captured_pairs.at(stone);
}
