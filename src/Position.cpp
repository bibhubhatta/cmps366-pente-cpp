#include "Position.h"

Position::Position(int row, int col) : row(row), col(col) {}

Position Position::from_string(const std::string& position_string)
{
    int row = get_row_number_from_position_string(position_string);
    int col = get_col_number_from_position_string(position_string);

    return {row, col};
}

int Position::get_row_number_from_position_string(const std::string& position)
{
    int row = std::stoi(position.substr(1, position.length() - 1)) - 1;
    return row;
}

int Position::get_col_number_from_position_string(const std::string& position)
{
    int col = position[0] - 'A';
    return col;
}

std::string Position::to_string() const
{
    std::string position = std::string(1, 'A' + col) + std::to_string(row + 1);
    return position;
}

bool Position::operator==(const Position& other) const
{
    return row == other.row && col == other.col;
}

bool Position::operator!=(const Position& other) const
{
    return !(*this == other);
}