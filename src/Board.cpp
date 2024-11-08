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

    // Initialize stone offsets for loading erroneous boards
    stone_offsets[WHITE_STONE] = 0;
    stone_offsets[BLACK_STONE] = 0;
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
                         const int          no_captured_black_pairs,
                         const Stone next_stone, const int no_rows,
                         const int no_cols)
{
    auto board_ = Board(no_rows, no_cols);

    int expected_board_string_size = no_rows * no_cols;

    if (board_string.size() != no_rows * no_cols)
    {
        throw std::runtime_error(
            fmt::format("Invalid board string. There must be {} cells/stones "
                        "in a board, but there are {}.",
                        expected_board_string_size, board_string.size()));
    }

    // Loop through board string and set stones
    for (int row = 0; row < no_rows; row++)
    {
        for (int col = 0; col < no_cols; col++)
        {
            char        row_char = 'A' + col;
            std::string position = fmt::format("{}{}", row_char, row + 1);
            Stone       stone = board_string[row * no_cols + col];
            if (!(stone == EMPTY || stone == WHITE_STONE ||
                  stone == BLACK_STONE))
            {
                throw std::runtime_error(
                    fmt::format("Invalid stone at position {}", position));
            }
            board_.set_stone(position, stone);
        }
    }

    board_.captured_pairs[WHITE_STONE] = no_captured_white_pairs;
    board_.captured_pairs[BLACK_STONE] = no_captured_black_pairs;

    // Fix errors in file
    while (true)
    {
        auto other_stone =
            next_stone == WHITE_STONE ? BLACK_STONE : WHITE_STONE;
        try
        {
            auto next_player = board_.get_turn();
            if (next_player != next_stone)
            {
                fmt::print(
                    "According to the board, the next player should be {}, but "
                    "serial says it should be {}. Setting next stone to {}\n",
                    next_player, next_stone, next_stone);
                board_.stone_offsets[other_stone]++;
            }
            break;
        }
        catch (const std::runtime_error& e)
        {
            fmt::print("Error: {}\n", e.what());

            fmt::print("Loading anyway...\n");

            fmt::print("Setting next stone to {}\n", next_stone);

            int black_stones_played =
                board_.get_total_no_stone_played(BLACK_STONE);
            int white_stones_played =
                board_.get_total_no_stone_played(WHITE_STONE);

            int diff = white_stones_played - black_stones_played;

            if (diff > 1)
            {
                board_.stone_offsets[BLACK_STONE] = diff;
            }
            else if (diff < 0)
            {
                board_.stone_offsets[WHITE_STONE] = diff;
            }

            if (board_.get_turn() != next_stone)
            {
                board_.stone_offsets[other_stone]++;
            }
        }
    }
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
    return get_no_stone_on_board(stone) + get_no_captured_pairs(stone) * 2 +
           stone_offsets.at(stone);
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
        throw std::runtime_error(fmt::format(
            "Invalid number of stones on board. There are {} white stones and "
            "{} black stones after accounting for captured pairs. The "
            "difference must be 0 or 1.",
            no_white_stones, no_black_stones));
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

    else if (no_moves_so_far == 2)
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
    for (const auto& row : get_all_rows())
    {
        std::vector<BoardSequence> sequences = get_stone_sequences(row);

        for (auto const& sequence : sequences)
        {
            if (sequence.size() >= no_consecutive_stones_to_win)
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
    for (const auto& col : get_all_cols())
    {
        std::vector<BoardSequence> sequences = get_stone_sequences(col);

        for (auto const& sequence : sequences)
        {
            if (sequence.size() >= no_consecutive_stones_to_win)
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
    auto all_main_diagonals = get_all_main_diagonals();

    for (auto const& main_diagonal : all_main_diagonals)
    {
        std::vector<BoardSequence> sequences =
            get_stone_sequences(main_diagonal);

        for (auto const& sequence : sequences)
        {
            if (sequence.size() >= no_consecutive_stones_to_win)
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
    for (const auto& anti_diagonal : get_all_anti_diagonals())
    {

        std::vector<BoardSequence> sequences =
            get_stone_sequences(anti_diagonal);

        for (auto const& sequence : sequences)
        {
            if (sequence.size() >= no_consecutive_stones_to_win)
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

    // Add score for sequences
    for (const auto& sequence : all_stone_sequences)
    {
        if (sequence.size() >= no_consecutive_stones_to_win)
        {
            score += 5;
        }
        else if (sequence.size() == no_consecutive_stones_to_win - 1)
        {
            score += 1;
        }
    }

    // Add score for captured pairs
    Stone opponent_stone = stone == WHITE_STONE ? BLACK_STONE : WHITE_STONE;
    score += captured_pairs.at(opponent_stone);

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

    std::vector<BoardSequence> all_board_sequences;

    std::vector<std::vector<BoardSequence>> all_rows_cols_diagonals = {
        get_all_rows(), get_all_cols(), get_all_main_diagonals(),
        get_all_anti_diagonals()};

    for (auto const& row_col_diagonal : all_rows_cols_diagonals)
    {
        for (auto const& sequence : row_col_diagonal)
        {
            all_board_sequences.push_back(sequence);
        }
    }

    for (auto const& sequence : all_board_sequences)
    {
        auto stone_sequences = get_stone_sequences(sequence, stone);
        for (auto const& stone_sequence : stone_sequences)
        {
            all_sequences.push_back(stone_sequence);
        }
    }

    return all_sequences;
}

std::vector<BoardSequence> Board::get_all_rows() const
{
    std::vector<BoardSequence> all_rows;

    for (int row = 0; row < no_rows; row++)
    {
        BoardSequence row_ = get_row(row);
        all_rows.push_back(row_);
    }

    return all_rows;
}

std::vector<BoardSequence> Board::get_all_cols() const
{
    std::vector<BoardSequence> all_cols;

    for (int col = 0; col < no_cols; col++)
    {
        BoardSequence col_ = get_col(col);
        all_cols.push_back(col_);
    }

    return all_cols;
}

std::vector<BoardSequence> Board::get_all_anti_diagonals() const
{
    std::vector<BoardSequence> all_anti_diagonals;

    for (int row = 0; row < no_rows; row++)
    {
        auto          diagonal_start = Position(row, no_cols - 1);
        BoardSequence anti_diagonal = get_anti_diagonal(diagonal_start);

        all_anti_diagonals.push_back(anti_diagonal);
    }

    for (int col = no_cols - 1; col > 0; col--)
    {
        auto          diagonal_start = Position(0, col);
        BoardSequence anti_diagonal = get_anti_diagonal(diagonal_start);

        all_anti_diagonals.push_back(anti_diagonal);
    }

    return all_anti_diagonals;
}

std::vector<BoardSequence> Board::get_all_main_diagonals() const
{
    std::vector<BoardSequence> all_main_diagonals;

    for (int row = 0; row < no_rows; row++)
    {
        auto          diagonal_start = Position(row, 0);
        BoardSequence main_diagonal = get_main_diagonal(diagonal_start);

        all_main_diagonals.push_back(main_diagonal);
    }

    for (int col = 1; col < no_cols; col++)
    {
        auto          diagonal_start = Position(0, col);
        BoardSequence main_diagonal = get_main_diagonal(diagonal_start);

        all_main_diagonals.push_back(main_diagonal);
    }

    return all_main_diagonals;
}

int Board::get_no_stone_sequences(Stone stone, int sequence_length) const
{
    int no_sequences = 0;

    auto all_stone_sequences = get_all_stone_sequences(stone);

    for (auto const& sequence : all_stone_sequences)
    {
        if (sequence.size() == sequence_length)
        {
            no_sequences++;
        }
    }

    return no_sequences;
}

std::vector<BoardSequence> Board::get_stone_sequences(Stone    stone,
                                                      Position position) const
{
    std::vector<BoardSequence> all_sequences_from_position;

    auto rows_cols_diagonals = {get_row(position), get_col(position),
                                get_main_diagonal(position),
                                get_anti_diagonal(position)};

    for (auto const& sequence : rows_cols_diagonals)
    {
        auto stone_sequences = get_stone_sequences(sequence, stone);
        for (auto const& stone_sequence : stone_sequences)
        {
            all_sequences_from_position.push_back(stone_sequence);
        }
    }

    return all_sequences_from_position;
}

void Board::check_win() const
{
    check_win_by_sequence();
    check_win_by_no_capture();
}

std::string Board::to_string() const
{
    std::string board_string;
    for (int row = no_rows - 1; row >= 0; row--)
    {
        for (int col = 0; col < no_cols; col++)
        {
            board_string += get_stone(row, col);
        }
        board_string += "\n";
    }
    return board_string;
}

std::set<Position> Board::get_neighbors(const Position& position) const
{
    std::set<Position> neighbors;

    int row = position.row;
    int col = position.col;

    if (row > 0)
    {
        neighbors.insert(Position(row - 1, col));
    }

    if (row < no_rows - 1)
    {
        neighbors.insert(Position(row + 1, col));
    }

    if (col > 0)
    {
        neighbors.insert(Position(row, col - 1));
    }

    if (col < no_cols - 1)
    {
        neighbors.insert(Position(row, col + 1));
    }

    // Diagonals

    if (row > 0 && col > 0)
    {
        neighbors.insert(Position(row - 1, col - 1));
    }

    if (row > 0 && col < no_cols - 1)
    {
        neighbors.insert(Position(row - 1, col + 1));
    }

    if (row < no_rows - 1 && col > 0)
    {
        neighbors.insert(Position(row + 1, col - 1));
    }

    if (row < no_rows - 1 && col < no_cols - 1)
    {
        neighbors.insert(Position(row + 1, col + 1));
    }

    return neighbors;
}
std::set<Position>

Board::get_available_sequence_neighbors(const Position& position) const
{
    std::set<Position> available_sequence_neighbors;

    auto               neighbors = get_neighbors(position);
    auto               moves = get_available_positions();
    std::set<Position> visited;

    while (!neighbors.empty())
    {
        Position neighbor = *neighbors.begin();
        neighbors.erase(neighbors.begin());

        if (visited.contains(neighbor))
        {
            continue;
        }

        visited.insert(neighbor);

        if (moves.contains(neighbor))
        {
            available_sequence_neighbors.insert(neighbor);
        }
        else if (get_stone(neighbor) == get_stone(position))
        {
            auto neighbor_neighbors = get_neighbors(neighbor);
            for (auto const& neighbor_neighbor : neighbor_neighbors)
            {
                neighbors.insert(neighbor_neighbor);
            }
        }
    }

    return available_sequence_neighbors;
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
    if (row >= 3 && col <= no_cols - 4)
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
    if (row <= no_rows - 4 && col <= no_cols - 4)
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
    if (row >= 3 && col >= 3)
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
    if (row <= no_rows - 4 && col >= 3)
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
        else if (no_moves_so_far == 2)
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
