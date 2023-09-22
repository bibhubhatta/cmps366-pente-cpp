#include <iostream>
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
            board.push_back(EMPTY);
        }
    }

    // Initialize captured pairs
    // The number of captured pairs is the numbers of pairs lost, ie, captured
    // by the opponent
    captured_pairs[WHITE_STONE] = 0;
    captured_pairs[BLACK_STONE] = 0;
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
            char        row_char = 'A' + col;
            std::string position = fmt::format("{}{}", row_char, row + 1);
            Stone       stone = board_string[row * no_cols + col];
            board_.set_stone(position, stone);
        }
    }

    board_.captured_pairs[WHITE_STONE] = no_captured_white_pairs;
    board_.captured_pairs[BLACK_STONE] = no_captured_black_pairs;

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

BoardSequence Board::get_row(int row) const
{
    BoardSequence row_;
    for (int col = 0; col < 19; col++)
    {
        Stone stone = get_stone(Position(row, col));
        row_.push_back(stone);
    }
    return row_;
}

template <typename T> BoardSequence Board::get_row(T& position) const
{
    Position position_ {position};
    int      row = position_.row;

    return get_row(row);
}

template BoardSequence Board::get_row<Position>(Position& position) const;

template BoardSequence Board::get_row<std::string>(std::string& position) const;

BoardSequence Board::get_col(int col) const
{
    BoardSequence col_;
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
    int no_white_stones = get_total_no_stone_played(WHITE_STONE);
    int no_black_stones = get_total_no_stone_played(BLACK_STONE);

    if (no_white_stones == no_black_stones)
    {
        return WHITE_STONE;
    }
    else if (no_white_stones == no_black_stones + 1)
    {
        return BLACK_STONE;
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
    return get_total_no_stone_played(WHITE_STONE) +
           get_total_no_stone_played(BLACK_STONE);
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
            if (get_stone(row, col) == EMPTY)
            {
                empty_positions.insert({row, col});
            }
        }
    }

    return empty_positions;
}

void Board::check_win_by_sequence() const
{
    check_win_by_row();
    check_win_by_column();
    check_win_by_main_diagonal();
    check_win_by_anti_diagonal();
}

void Board::check_win_by_row() const
{
    for (int row_num = 0; row_num < no_rows; row_num++)
    {
        BoardSequence row = get_row(row_num);

        std::vector<BoardSequence> sequences = get_stone_sequences(row);

        for (auto const& sequence : sequences)
        {
            if (sequence.size() == no_consecutive_stones_to_win)
            {
                throw GameWon(
                    sequence.at(0),
                    fmt::format("{} in a row", no_consecutive_stones_to_win));
            }
        }
    }
}

void Board::check_win_by_column() const
{
    for (int col_num = 0; col_num < no_cols; col_num++)
    {
        BoardSequence col = get_col(col_num);

        std::vector<BoardSequence> sequences = get_stone_sequences(col);

        for (auto const& sequence : sequences)
        {
            if (sequence.size() == no_consecutive_stones_to_win)
            {
                throw GameWon(sequence.at(0),
                              fmt::format("{} in a column",
                                          no_consecutive_stones_to_win));
            }
        }
    }
}

void Board::check_win_by_main_diagonal() const
{
    for (int row = 0, col = no_cols - 1; row < no_rows && col >= 0;
         row++, col--) // Positions of anti diagonal to get all main diagonal
    {
        auto          diagonal_center = Position(row, col);
        BoardSequence main_diagonal = get_main_diagonal(diagonal_center);

        std::vector<BoardSequence> sequences =
            get_stone_sequences(main_diagonal);

        for (auto const& sequence : sequences)
        {
            if (sequence.size() == no_consecutive_stones_to_win)
            {
                throw GameWon(sequence.at(0),
                              fmt::format("{} in a diagonal",
                                          no_consecutive_stones_to_win));
            }
        }
    }
}

void Board::check_win_by_anti_diagonal() const
{
    for (int row = 0, col = 0; row < no_rows && col < no_cols;
         row++, col++) // Positions of main diagonal to get all anti diagonal
    {
        auto          diagonal_center = Position(row, col);
        BoardSequence anti_diagonal = get_anti_diagonal(diagonal_center);

        std::vector<BoardSequence> sequences =
            get_stone_sequences(anti_diagonal);

        for (auto const& sequence : sequences)
        {
            if (sequence.size() == no_consecutive_stones_to_win)
            {
                throw GameWon(sequence.at(0),
                              fmt::format("{} in a diagonal",
                                          no_consecutive_stones_to_win));
            }
        }
    }
}

void Board::check_win_by_no_capture() const
{
    if (captured_pairs.at(WHITE_STONE) >= no_captured_pairs_to_win)
    {
        throw GameWon(BLACK_STONE, fmt::format("{} or more pairs captures",
                                               no_captured_pairs_to_win));
    }
    else if (captured_pairs.at(BLACK_STONE) >= no_captured_pairs_to_win)
    {
        throw GameWon(WHITE_STONE, fmt::format("{} or more pairs captures",
                                               no_captured_pairs_to_win));
    }
}

Score Board::get_score(Stone stone) const
{
    int score = 0;

    auto all_stone_sequences = get_all_stone_sequences(stone);

    for (auto sequence : all_stone_sequences)
    {
        if (sequence.size() == no_consecutive_stones_to_win)
        {
            score += 5;
        }
        else if (sequence.size() == no_consecutive_stones_to_win - 1)
        {
            score += 1;
        }
    }

    return score;
}

std::vector<BoardSequence>
Board::get_stone_sequences(const BoardSequence& sequence)
{
    std::vector<BoardSequence> sequences;
    BoardSequence              current_sequence;

    int index = 0;

    while (index < sequence.size())
    {
        if (sequence[index] == EMPTY)
        {
            index++;
            continue;
        }

        current_sequence.push_back(sequence[index]);
        while (index < sequence.size() - 1 &&
               sequence[index] == sequence[index + 1])
        {
            current_sequence.push_back(sequence[index]);
            index++;
        }
        sequences.push_back(current_sequence);
        current_sequence.clear();
        index++;
    }

    return sequences;
}

std::vector<BoardSequence>
Board::get_stone_sequences(const BoardSequence& sequence, const Stone& stone)
{
    auto                       all_sequences = get_stone_sequences(sequence);
    std::vector<BoardSequence> filtered_sequence;

    for (auto seq : all_sequences)
    {
        if (seq.at(0) == stone)
        {
            filtered_sequence.push_back(seq);
        }
    }

    return filtered_sequence;
}

std::vector<BoardSequence> Board::get_all_stone_sequences(Stone stone) const
{
    std::vector<BoardSequence> all_sequences;

    // Get all rows
    for (int row = 0; row < no_rows; row++)
    {
        BoardSequence row_ = get_row(row);
        auto          sequences = get_stone_sequences(row_, stone);
        all_sequences.insert(all_sequences.end(), sequences.begin(),
                             sequences.end());
    }

    // Get all columns
    for (int col = 0; col < no_cols; col++)
    {
        BoardSequence col_ = get_col(col);
        auto          sequences = get_stone_sequences(col_, stone);
        all_sequences.insert(all_sequences.end(), sequences.begin(),
                             sequences.end());
    }

    // Get all main diagonals
    for (int row = 0, col = no_cols - 1; row < no_rows && col >= 0;
         row++, col--) // Positions of anti diagonal to get all main diagonal
    {
        auto          diagonal_center = Position(row, col);
        BoardSequence main_diagonal = get_main_diagonal(diagonal_center);
        auto          sequences = get_stone_sequences(main_diagonal, stone);
        all_sequences.insert(all_sequences.end(), sequences.begin(),
                             sequences.end());
    }

    // Get all anti diagonals
    for (int row = 0, col = 0; row < no_rows && col < no_cols;
         row++, col++) // Positions of main diagonal to get all anti diagonal
    {
        auto          diagonal_center = Position(row, col);
        BoardSequence anti_diagonal = get_anti_diagonal(diagonal_center);
        auto          sequences = get_stone_sequences(anti_diagonal, stone);
        all_sequences.insert(all_sequences.end(), sequences.begin(),
                             sequences.end());
    }

    return all_sequences;
}

template <typename T> void Board::handle_capture(const T& position)
{
    Position position_ {position};
    int      row = position_.row;
    int      col = position_.col;

    Stone stone = get_stone(row, col);
    Stone opponent_stone = stone == WHITE_STONE ? BLACK_STONE : WHITE_STONE;

    BoardSequence capture_sequence = {stone, opponent_stone, opponent_stone,
                                      stone};

    BoardSequence row_ = get_row(row);

    // Handle captures to the left
    if (col >= 3)
    {
        auto left =
            std::vector<Stone>(row_.begin() + col - 3, row_.begin() + col + 1);

        if (left == capture_sequence)
        {
            captured_pairs[opponent_stone]++;
            set_stone(Position(row, col - 2), EMPTY);
            set_stone(Position(row, col - 1), EMPTY);
        }
    }

    // Handle captures to the right
    if (col <= no_cols - 4)
    {
        auto right =
            std::vector<Stone>(row_.begin() + col, row_.begin() + col + 4);

        if (right == capture_sequence)
        {
            captured_pairs[opponent_stone]++;
            set_stone(Position(row, col + 1), EMPTY);
            set_stone(Position(row, col + 2), EMPTY);
        }
    }

    // Handle captures below
    if (row >= 3)
    {
        BoardSequence below;
        for (int i = row; i >= row - 3; i--)
        {
            below.push_back(get_stone(i, col));
        }

        if (below == capture_sequence)
        {
            captured_pairs[opponent_stone]++;
            set_stone(Position(row - 2, col), EMPTY);
            set_stone(Position(row - 1, col), EMPTY);
        }
    }

    // Handle captures above
    if (row <= no_rows - 4)
    {
        BoardSequence above;
        for (int i = row; i <= row + 3; i++)
        {
            above.push_back(get_stone(i, col));
        }

        if (above == capture_sequence)
        {
            captured_pairs[opponent_stone]++;
            set_stone(Position(row + 1, col), EMPTY);
            set_stone(Position(row + 2, col), EMPTY);
        }
    }

    // Handle captures in the diagonal - down right
    if (row <= no_rows - 4 && col <= no_cols - 4)
    {
        BoardSequence diagonal;
        for (int i = row, j = col; i >= row - 3 && j <= col + 3; i--, j++)
        {
            diagonal.push_back(get_stone(i, j));
        }

        if (diagonal == capture_sequence)
        {
            captured_pairs[opponent_stone]++;
            set_stone(Position(row - 1, col + 1), EMPTY);
            set_stone(Position(row - 2, col + 2), EMPTY);
        }
    }

    // Handle captures in the diagonal - up right
    if (row >= 3 && col <= no_cols - 4)
    {
        BoardSequence diagonal;
        for (int i = row, j = col; i <= row + 3 && j <= col + 3; i++, j++)
        {
            diagonal.push_back(get_stone(i, j));
        }

        if (diagonal == capture_sequence)
        {
            captured_pairs[opponent_stone]++;
            set_stone(Position(row + 1, col + 1), EMPTY);
            set_stone(Position(row + 2, col + 2), EMPTY);
        }
    }

    // Handle captures in the diagonal - down left
    if (row <= no_rows - 4 && col >= 3)
    {
        BoardSequence diagonal;
        for (int i = row, j = col; i >= row - 3 && j >= col - 3; i--, j--)
        {
            diagonal.push_back(get_stone(i, j));
        }

        if (diagonal == capture_sequence)
        {
            captured_pairs[opponent_stone]++;
            set_stone(Position(row - 1, col - 1), EMPTY);
            set_stone(Position(row - 2, col - 2), EMPTY);
        }
    }

    // Handle captures in the diagonal - up left
    if (row >= 3 && col >= 3)
    {
        BoardSequence diagonal;
        for (int i = row, j = col; i <= row + 3 && j >= col - 3; i++, j--)
        {
            diagonal.push_back(get_stone(i, j));
        }

        if (diagonal == capture_sequence)
        {
            captured_pairs[opponent_stone]++;
            set_stone(Position(row + 1, col - 1), EMPTY);
            set_stone(Position(row + 2, col - 2), EMPTY);
        }
    }
}

template <typename T> void Board::make_move(const T& position)
{
    Position position_ {position};

    if (std::set<Position> available_positions = get_available_positions();
        !available_positions.contains(position_)) // position not available
    {
        std::string reason = position_.to_string() + " is not available.";

        if (int no_moves_so_far = get_no_moves_so_far(); no_moves_so_far == 0)
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

    handle_capture(position);
    check_win_by_sequence();
    check_win_by_no_capture();
}

template void Board::make_move<Position>(const Position& position);
template void Board::make_move<std::string>(const std::string& position);

template <typename T> BoardSequence Board::get_col(T& position) const
{
    Position position_ {position};
    int      col = position_.col;

    return get_col(col);
}

template BoardSequence Board::get_col<Position>(Position& position) const;

template BoardSequence Board::get_col<std::string>(std::string& position) const;

template <typename T> BoardSequence Board::get_main_diagonal(T& position) const
{
    Position position_ {position};
    int      row = position_.row;
    int      col = position_.col;

    BoardSequence diagonal;

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
    while (end_row < (no_rows - 1) && end_col < (no_cols - 1))
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

template BoardSequence
Board::get_main_diagonal<Position>(Position& position) const;

template BoardSequence
Board::get_main_diagonal<std::string>(std::string& position) const;

template <typename T> BoardSequence Board::get_anti_diagonal(T& position) const
{
    Position position_ {position};
    int      row = position_.row;
    int      col = position_.col;

    BoardSequence diagonal;

    // Find the start of the diagonal
    int start_row = row;
    int start_col = col;
    while (start_row > 0 && start_col < (no_cols - 1))
    {
        start_row--;
        start_col++;
    }

    // Find the end of the diagonal
    int end_row = row;
    int end_col = col;
    while (end_row < (no_rows - 1) && end_col > 0)
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

template BoardSequence
Board::get_anti_diagonal<Position>(Position& position) const;

template BoardSequence
Board::get_anti_diagonal<std::string>(std::string& position) const;