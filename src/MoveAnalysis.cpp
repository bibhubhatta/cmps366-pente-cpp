#include <algorithm>

#include "Exceptions.h"
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

bool MoveAnalysis::is_capturing_move() const
{
    return capture_differential() > 0;
}

int MoveAnalysis::capture_differential() const
{
    auto current_player = board.get_turn();
    auto opponent = current_player == Board::WHITE_STONE ? Board::BLACK_STONE
                                                         : Board::WHITE_STONE;
    auto captured_pairs_before = board.get_no_captured_pairs(opponent);

    Board board_ = board;

    board_.make_move(move);

    auto captured_pairs_after = board_.get_no_captured_pairs(opponent);

    return captured_pairs_after - captured_pairs_before;
}

Score MoveAnalysis::pseudo_score_after_move() const
{
    Board board_ = board;
    Stone current_player = board_.get_turn();

    board_.make_move(move);
    Score score = 0;

    auto all_stone_sequences = board_.get_all_stone_sequences(current_player);

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

    return score;
}
