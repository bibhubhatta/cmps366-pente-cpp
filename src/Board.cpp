#include "Board.h"

Board::Board()
{
    for (int i = 0; i < 19; i++)
    {
        std::vector<char> row;
        for (int j = 0; j < 19; j++)
        {
            row.push_back('O');
        }
        board.push_back(row);
    }
}

char Board::get_stone(const std::string& position) const
{
    int row = get_row(position);
    int col = get_col(position);
    return board[row][col];
}

void Board::set_stone(const std::string& position, char stone)
{
    int row = get_row(position);
    int col = get_col(position);

    // TODO: Raise exception if stone is already set

    board[row][col] = stone;
}

int Board::get_row(const std::string& position)
{
    int row = std::stoi(position.substr(1, position.length() - 1)) - 1;
    // TODO: Raise exception if position is invalid / out of bounds
    return row;
}

int Board::get_col(const std::string& position)
{
    int col = position[0] - 'A';
    // TODO: Raise exception if position is invalid / out of bounds
    return col;
}

Board Board::from_string(const std::string& board_string)
{
    auto board_ = Board();

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

    return board_;
}
