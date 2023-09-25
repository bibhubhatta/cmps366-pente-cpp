#include "fmt/format.h"
#include <algorithm>
#include <queue>

#include "MoveAnalysis.h"
#include "Strategy.h"
#include "helpers.h"

Strategy::Strategy(Board board) : board(board) {}

StrategicMove Strategy::get_move()
{
    std::string rationale;

    std::set<Position> available_moves = board.get_available_positions();

    if (available_moves.size() == 1)
    {
        rationale = "it is the only available move.";
        return {*available_moves.begin(), rationale};
    }

    std::priority_queue<std::pair<int, std::string>> winning_move_deltas;
    std::priority_queue<std::pair<int, std::string>>
        opponent_winning_move_deltas;
    std::priority_queue<std::pair<int, std::string>> capturing_move_deltas;
    std::priority_queue<std::pair<int, std::string>> opponent_capture_deltas;
    std::priority_queue<std::pair<int, std::string>> pseudo_scores;

    std::set<Position> losing_moves;

    for (const auto& move : available_moves)
    {
        MoveAnalysis move_analysis(board, move);

        if (move_analysis.is_winning_move())
        {
            winning_move_deltas.emplace(move_analysis.score_delta(),
                                        move.to_string());
            continue;
        }

        if (move_analysis.is_opponent_winning_move())
        {
            opponent_winning_move_deltas.emplace(
                move_analysis.opponent_score_delta(), move.to_string());
            continue;
        }

        if (move_analysis.is_capturing_move())
        {
            capturing_move_deltas.emplace(move_analysis.capture_delta(),
                                          move.to_string());
            continue;
        }

        if (move_analysis.is_opponent_capturing_move())
        {
            opponent_capture_deltas.emplace(
                move_analysis.opponent_capture_delta(), move.to_string());
            continue;
        }

        pseudo_scores.emplace(move_analysis.pseudo_score_after_move(),
                              move.to_string());
    }

    if (winning_move_deltas.size() == 1)
    {
        rationale = "it is a winning move.";
        auto winning_move = winning_move_deltas.top().second;
        return {Position(winning_move), rationale};
    }

    else if (winning_move_deltas.size() > 1)
    {
        // If there is only one highest win delta, then we can just choose that
        // move. Otherwise, hold off

        auto no_winning_moves = winning_move_deltas.size();

        auto [highest_win_delta, highest_win_delta_move] =
            winning_move_deltas.top();
        winning_move_deltas.pop();

        auto [second_highest_win_delta, second_highest_win_delta_move] =
            winning_move_deltas.top();
        winning_move_deltas.pop();

        if (highest_win_delta > second_highest_win_delta)
        {
            rationale = fmt::format(
                "it gets the most points. It wins {} more points than the "
                "current score. There are {} winning moves. {}",
                highest_win_delta, no_winning_moves, rationale);

            return {Position(highest_win_delta_move), rationale};
        }

        else
        {
            rationale =
                fmt::format("{}There are {} winning moves, and 2 moves get the "
                            "same score, so holding off.",
                            rationale, no_winning_moves);
        }
    }

    else
    {
        rationale = fmt::format("{}There are no winning moves.", rationale);
    }

    if (opponent_winning_move_deltas.size() == 1)
    {
        auto [highest_opponent_win_delta, highest_opponent_win_delta_move] =
            opponent_winning_move_deltas.top();

        rationale =
            fmt::format("opponent can win by playing here. {}", rationale);

        return {Position(highest_opponent_win_delta_move), rationale};
    }

    else if (opponent_winning_move_deltas.size() > 1)
    {
        auto const& [highest_opponent_win_delta,
                     highest_opponent_win_delta_move] =
            opponent_winning_move_deltas.top();

        auto const& [second_highest_opponent_win_delta,
                     second_highest_opponent_win_delta_move] =
            opponent_winning_move_deltas.top();

        rationale = fmt::format(" it gives the opponent the least points. "
                                "Opponent has {} winning moves. {}",
                                opponent_winning_move_deltas.size(), rationale);

        return {Position(highest_opponent_win_delta_move), rationale};
    }

    else
    {
        rationale =
            fmt::format("{} There are no opponent winning moves.", rationale);
    }

    if (capturing_move_deltas.size() > 1)
    {
        auto [highest_capture_delta, highest_capture_delta_move] =
            capturing_move_deltas.top();

        rationale = fmt::format("it captures the most points. There are {} "
                                "capturing moves, and it captures {} pairs. {}",
                                capturing_move_deltas.size(),
                                highest_capture_delta, rationale);

        return {Position(highest_capture_delta_move), rationale};
    }

    else if (capturing_move_deltas.size() == 1)
    {
        auto [highest_capture_delta, highest_capture_delta_move] =
            capturing_move_deltas.top();

        rationale = fmt::format("it is a capturing move. {}", rationale);

        return {Position(highest_capture_delta_move), rationale};
    }

    else
    {
        rationale = fmt::format("{} There are no capturing moves.", rationale);
    }

    if (opponent_capture_deltas.size() > 1)
    {
        // opponent_captur_delta returns negative as it represents the number of
        // pairs we loose
        auto [highest_opponent_capture_delta,
              highest_opponent_capture_delta_move] =
            opponent_capture_deltas.top();

        rationale = fmt::format(
            "it prevents the opponent from capturing the most pairs. There "
            "are {} opponent capturing moves, and it will lose {} pairs. {}",
            opponent_capture_deltas.size(), highest_opponent_capture_delta,
            rationale);

        return {Position(highest_opponent_capture_delta_move), rationale};
    }

    else if (opponent_capture_deltas.size() == 1)
    {
        auto [highest_opponent_capture_delta,
              highest_opponent_capture_delta_move] =
            opponent_capture_deltas.top();

        rationale =
            fmt::format("it prevents opponent from capturing. {}", rationale);

        return {Position(highest_opponent_capture_delta_move), rationale};
    }

    else
    {
        rationale =
            fmt::format("{} There are no opponent capturing moves.", rationale);
    }

    if (pseudo_scores.top().first != 0)
    {
        auto const& [highest_pseudo_score, highest_pseudo_score_move] =
            pseudo_scores.top();

        rationale = fmt::format("it is the most optimal move. {}", rationale);

        return {Position(highest_pseudo_score_move), rationale};
    }

    rationale = fmt::format(
        "all moves are similar, so choosing a random move. {}", rationale);

    auto random_move = get_random_element(available_moves);
    return {random_move, rationale};
}
