#include <iostream>

#include <fmt/format.h>
#include <tabulate/table.hpp>

#include "BoardDisplay.h"

BoardDisplay::BoardDisplay(const Board& board) : board(board) {}

void BoardDisplay::render() const
{
    tabulate::Table grid;

    for (int i = board.no_rows - 1; i >= 0; i--)
    {
        std::vector<variant<std::basic_string<char>, const char*,
                            std::basic_string_view<char>, tabulate::Table>>
            row;

        row.emplace_back(fmt::format("{}", i + 1)); // row label

        for (int j = 0; j < board.no_cols; j++)
        {
            char        stone = board.get_stone(Position(i, j));
            std::string stone_str = fmt::format("{}", stone);
            row.emplace_back(stone_str);
        }

        grid.add_row(row);
    }

    //   Add column labels
    std::vector<variant<std::basic_string<char>, const char*,
                        std::basic_string_view<char>, tabulate::Table>>
        col_labels;

    col_labels.emplace_back(" "); // for the row labels column

    for (int i = 0; i < board.no_cols; i++)
    {
        std::string col_label = std::string(1, 'A' + i);
        col_labels.emplace_back(col_label);
    }

    grid.add_row(col_labels);

    std::cout << grid << std::endl;
}
