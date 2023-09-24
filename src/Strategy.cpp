#include "fmt/format.h"
#include <algorithm>
#include <queue>

#include "MoveAnalysis.h"
#include "Strategy.h"
#include "helpers.h"

StrategicMove Strategy::get_move()
{
    std::string rationale;

    std::set<Position> available_moves = board.get_available_positions();

    if (available_moves.size() == 1)
    {
        rationale = "Only move.";
        return {*available_moves.begin(), rationale};
    }

    std::priority_queue<std::pair<int, std::string>> winning_move_deltas;
    std::priority_queue<std::pair<int, std::string>> capturing_move_deltas;

    std::set<Position> losing_moves;

    for (const auto& move : available_moves)
    {
        MoveAnalysis move_analysis(board, move);

        if (move_analysis.is_winning_move())
        {
            winning_move_deltas.emplace(move_analysis.win_delta(),
                                        move.to_string());
            continue;
        }

        if (move_analysis.is_capturing_move())
        {
            capturing_move_deltas.emplace(move_analysis.capture_delta(),
                                          move.to_string());
            continue;
        }

        if (move_analysis.is_losing_move())
        {
            losing_moves.insert(move);
            continue;
        }
    }

    if (winning_move_deltas.size() == 1)
    {
        rationale = "Winning move.";
        auto winning_move = winning_move_deltas.top().second;
        return {Position(winning_move), rationale};
    }

    if (winning_move_deltas.size() > 1)
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
            rationale =
                fmt::format("{}There are {} winning moves. "
                            "So, choosing the one that gets the most points. "
                            "It wins {} points.",
                            rationale, no_winning_moves, highest_win_delta);

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

    if (!capturing_move_deltas.empty())
    {
        auto [highest_capture_delta, highest_capture_delta_move] =
            capturing_move_deltas.top();

        rationale = fmt::format(
            "{}There are {} capturing moves. "
            "So, choosing the one that gets the most points. "
            "It captures {} points.",
            rationale, capturing_move_deltas.size(), highest_capture_delta);

        return {Position(highest_capture_delta_move), rationale};
    }

    rationale = fmt::format("{}There are no winning or capturing moves. "
                            "So, choosing a random move.",
                            rationale);

    auto random_move = get_random_element(available_moves);
    return {random_move, rationale};
}
