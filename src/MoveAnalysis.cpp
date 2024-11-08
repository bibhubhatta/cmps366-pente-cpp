#include <algorithm>

#include "Exceptions.h"
#include "ExperimentalBoard.h"
#include "MoveAnalysis.h"

template <typename T>
MoveAnalysis::MoveAnalysis(const Board& board, const T& move)
    : board(board), move(move)
{
}

template MoveAnalysis::MoveAnalysis(const Board&       board,
                                    const std::string& move);
template MoveAnalysis::MoveAnalysis(const Board& board, const Position& move);

bool MoveAnalysis::is_only_move() const
{
    return board.get_available_positions().size() == 1;
}

bool MoveAnalysis::is_winning_move() const
{
    Board board_ = board;

    try
    {
        board_.make_move(move);
    }
    catch (const GameWon& e)
    {
        return true;
    }
    catch (const std::exception& e)
    {
        return false;
    }

    return false;
}

bool MoveAnalysis::is_win_blocking_move() const
{
    if (is_winning_move())
    {
        return true;
    }

    Board board_ = board;

    board_.make_move(move);

    auto available_positions = board_.get_available_positions();

    for (const auto& position : available_positions)
    {
        if (MoveAnalysis(board_, position).is_winning_move())
        {
            return false;
        }
    }

    return true;
}

bool MoveAnalysis::is_losing_move() const { return !is_win_blocking_move(); }

bool MoveAnalysis::is_capturing_move() const { return capture_delta() > 0; }

int MoveAnalysis::score_delta() const
{
    Stone current_player = board.get_turn();
    Score current_score = board.get_score(current_player);
    Board board_ = board;

    try
    {
        board_.make_move(move);
    }
    catch (const std::exception& e)
    {
    }

    Score new_score = board_.get_score(current_player);
    return new_score - current_score;
}

int MoveAnalysis::opponent_score_delta() const
{

    auto board_ = static_cast<ExperimentalBoard>(board);

    Stone current_player = board_.get_turn();
    Stone opponent = current_player == Board::WHITE_STONE ? Board::BLACK_STONE
                                                          : Board::WHITE_STONE;

    Score opponent_score = board_.get_score(opponent);

    board_.set_stone(move, opponent);

    try
    {
        board_.check_win();
    }
    catch (const std::exception& e)
    {
    }

    Score new_opponent_score = board_.get_score(opponent);
    return new_opponent_score - opponent_score;
}

int MoveAnalysis::capture_delta() const
{
    auto current_player = board.get_turn();
    auto opponent = current_player == Board::WHITE_STONE ? Board::BLACK_STONE
                                                         : Board::WHITE_STONE;
    auto captured_pairs_before = board.get_no_captured_pairs(opponent);

    Board board_ = board;
    try
    {
        board_.make_move(move);
    }
    catch (const GameOver& e)
    {
    }

    auto captured_pairs_after = board_.get_no_captured_pairs(opponent);

    return captured_pairs_after - captured_pairs_before;
}

Score MoveAnalysis::pseudo_score_after_move() const
{
    Board board_ = board;
    Stone current_player = board_.get_turn();

    try
    {
        board_.make_move(move);
    }
    catch (const GameWon& e)
    {
    }

    Score score = calculate_pseudo_score(board_, current_player);

    return score + opponent_pseudo_score_after_move();
}

Score MoveAnalysis::calculate_pseudo_score(const Board& board_,
                                           const Stone& stone) const
{
    Score score = 0;

    auto all_stone_sequences = board_.get_stone_sequences(stone, move);

    std::map<int, int> sequence_length_count;

    for (auto const& sequence : all_stone_sequences)
    {
        sequence_length_count[sequence.size()]++;
    }

    for (auto [length, count] : sequence_length_count)
    {
        if (length == 1)
        {
            score += 0; // No score for single stones
            continue;
        }

        score += count * length;
    }

    return score * (board_.get_score(stone) + 1);
}

Score MoveAnalysis::opponent_pseudo_score_after_move() const
{
    ExperimentalBoard board_ = static_cast<ExperimentalBoard>(board);
    Stone             current_player = board_.get_turn();
    Stone opponent = current_player == Board::WHITE_STONE ? Board::BLACK_STONE
                                                          : Board::WHITE_STONE;

    board_.set_stone(move, opponent);
    Score score = calculate_pseudo_score(board_, opponent);

    return score;
}

bool MoveAnalysis::is_opponent_winning_move() const
{
    ExperimentalBoard board_ = static_cast<ExperimentalBoard>(board);

    auto opponent = board_.get_turn() == Board::WHITE_STONE
                        ? Board::BLACK_STONE
                        : Board::WHITE_STONE;

    try
    {
        board_.set_stone(move, opponent);
        board_.check_win();
    }
    catch (const GameWon& e)
    {
        return true;
    }
    catch (const std::exception& e)
    {
        return false;
    }

    return false;
}

bool MoveAnalysis::is_opponent_scoring_move() const
{
    return opponent_score_delta() != 0;
}

bool MoveAnalysis::is_opponent_capturing_move() const
{
    return opponent_capture_delta() != 0;
}

int MoveAnalysis::opponent_capture_delta() const
{

    ExperimentalBoard board_ = static_cast<ExperimentalBoard>(board);

    auto current_player = board_.get_turn();
    auto opponent = current_player == Board::WHITE_STONE ? Board::BLACK_STONE
                                                         : Board::WHITE_STONE;

    auto captured_pairs_before = board_.get_no_captured_pairs(current_player);

    board_.set_stone(move, opponent);

    auto captured_pairs_after = board_.get_no_captured_pairs(current_player);

    return captured_pairs_after - captured_pairs_before;
}

bool MoveAnalysis::is_capture_safe() const
{
    Board board_ = board;
    try
    {
        board_.make_move(move);
    }
    catch (const GameOver& e)
    {
        return true;
    }

    auto neighborhood = board_.get_available_sequence_neighbors(move);
    for (const auto& position : neighborhood)
    {
        if (MoveAnalysis(board_, position).is_capturing_move())
        {
            return false;
        }
    }

    return true;
}

int MoveAnalysis::distance_from_center() const
{
    auto center = board.get_center();
    return move.distance(center);
}
