#include <set>
#include <stdexcept>

#include "Board.h"
#include "Exceptions.h"

Board::Board(int no_rows, int no_cols) : no_rows(no_rows), no_cols(no_cols)
{

    // Initialize board with empty stones
    for (int i = 0; i < no_rows; i++)
    {
        for (int j = 0; j < no_cols; j++)
        {
            board.push_back('O');
        }
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

    return board[row * no_cols + col];
}

template Stone Board::get_stone<Position>(const Position& position) const;

template Stone Board::get_stone<std::string>(const std::string& position) const;

template <typename T> void Board::set_stone(const T& position, Stone stone)
{
    Position position_ {position};
    int      row = position_.row;
    int      col = position_.col;

    // TODO: Raise exception if stone is already set

    board[row * no_cols + col] = stone;
}

template void Board::set_stone<Position>(const Position& position, Stone stone);

template void Board::set_stone<std::string>(const std::string& position,
                                            Stone              stone);

Board Board::from_string(const std::string& board_string,
                         const int          no_captured_white_pairs,
                         const int no_captured_black_pairs, const int no_rows,
                         const int no_cols)
{
    auto board_ = Board(no_rows, no_cols);

    // Loop through board string and set stones
    for (int row = 0; row < no_rows; row++)
    {
        for (int col = 0; col < no_cols; col++)
        {
            std::string position =
                std::string(1, 'A' + col) + std::to_string(row + 1);
            Stone stone = board_string[row * no_cols + col];
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

    int no_captured_pairs = 0;

    try
    {
        no_captured_pairs = captured_pairs.at(stone);
    }
    catch (const std::out_of_range& oor)
    {
        // It could be that the stone is not valid,
        // but we are returning 0 in case the stone has not been captured yet
    }

    return no_captured_pairs;
}

StoneSequence Board::get_row(int row) const
{
    StoneSequence row_;
    for (int col = 0; col < 19; col++)
    {
        Stone stone = get_stone(Position(row, col));
        row_.push_back(stone);
    }
    return row_;
}

template <typename T> StoneSequence Board::get_row(T& position) const
{
    Position position_ {position};
    int      row = position_.row;

    return get_row(row);
}

template StoneSequence Board::get_row<Position>(Position& position) const;

template StoneSequence Board::get_row<std::string>(std::string& position) const;

StoneSequence Board::get_col(int col) const
{
    StoneSequence col_;
    for (int row = 0; row < no_rows; row++)
    {
        Stone stone = get_stone(Position(row, col));
        col_.push_back(stone);
    }
    return col_;
}

int Board::get_no_stone_on_board(Stone stone) const
{
    int no_stone = 0;
    for (int row = 0; row < no_rows; row++)
    {
        for (int col = 0; col < no_cols; col++)
        {
            if (get_stone(row, col) == stone)
            {
                no_stone++;
            }
        }
    }
    return no_stone;
}

Stone Board::get_stone(int row, int col) const
{
    Position position {row, col};
    return get_stone(position);
}

int Board::get_total_no_stone_played(Stone stone) const
{
    return get_no_stone_on_board(stone) + get_no_captured_pairs(stone) * 2;
}

Stone Board::get_turn() const
{
    int no_white_stones = get_total_no_stone_played('W');
    int no_black_stones = get_total_no_stone_played('B');

    if (no_white_stones == no_black_stones)
    {
        return 'W';
    }
    else if (no_white_stones == no_black_stones + 1)
    {
        return 'B';
    }
    else
    {
        throw std::runtime_error("Invalid number of stones on board");
    }
}

std::set<Position> Board::get_available_positions() const
{
    std::set<Position> available_positions;
    int                no_moves_so_far = get_no_moves_so_far();

    Position center = get_center();

    // First move
    if (no_moves_so_far == 0)
    {
        available_positions.insert(center);
    }

    else if (no_moves_so_far == 1)
    {
        // Second move
        for (auto& position : get_empty_positions())
        {
            if (position.distance(center) >= 3)
            {
                available_positions.insert(position);
            }
        }
    }

    else
    {
        available_positions = get_empty_positions();
    }

    return available_positions;
}

int Board::get_no_moves_so_far() const
{
    return get_total_no_stone_played('W') + get_total_no_stone_played('B');
}

Position Board::get_center() const
{
    int center_row = no_rows / 2;
    int center_col = no_cols / 2;
    return {center_row, center_col};
}

std::set<Position> Board::get_empty_positions() const
{
    std::set<Position> empty_positions;
    for (int row = 0; row < no_rows; row++)
    {
        for (int col = 0; col < no_cols; col++)
        {
            if (get_stone(row, col) == 'O')
            {
                empty_positions.insert({row, col});
            }
        }
    }

    return empty_positions;
}

template <typename T> void Board::make_move(const T& position)
{
    Position position_ {position};

    std::set<Position> available_positions = get_available_positions();

    if (available_positions.find(position_) ==
        available_positions.end()) // position not available
    {
        std::string reason = position_.to_string() + " is not available.";

        int no_moves_so_far = get_no_moves_so_far();

        if (no_moves_so_far == 0)
        {
            reason += " The first move must be at the center of the board.";
        }
        else if (no_moves_so_far == 1)
        {
            reason += " The second move must be at least 3 intersections away "
                      "from the center.";
        }
        else if (position_.row >= no_rows || position_.row < 0 ||
                 position_.col >= no_cols || position_.col < 0)
        {
            reason += " The position is out of the board.";
        }
        else
        {
            reason += " It is already occupied.";
        }

        throw InvalidMove(position_, reason);
    }

    Stone stone = get_turn();
    set_stone(position, stone);
}

template void Board::make_move<Position>(const Position& position);
template void Board::make_move<std::string>(const std::string& position);

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
        diagonal.push_back(get_stone(i, j));
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
        diagonal.push_back(get_stone(i, j));
    }

    return diagonal;
}

template StoneSequence
Board::get_anti_diagonal<Position>(Position& position) const;

template StoneSequence
Board::get_anti_diagonal<std::string>(std::string& position) const;