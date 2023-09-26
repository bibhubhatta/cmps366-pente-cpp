#include "fmt/format.h"
#include <algorithm>
#include <queue>

#include "MoveAnalysis.h"
#include "Strategy.h"
#include "helpers.h"

Strategy::Strategy(Board board) : board(board) {}

StrategicMove Strategy::get_move()
{
    using analysis = std::tuple<int, int, int, int, Score, Score, std::string>;
    std::vector<analysis> move_analyses;

    std::set<Position> available_moves = board.get_available_positions();
    for (const auto& move : available_moves)
    {
        MoveAnalysis move_analysis(board, move);

        move_analyses.emplace_back(
            move_analysis.is_winning_move(),
            move_analysis.is_opponent_winning_move(),
            move_analysis.capture_delta(),
            move_analysis.opponent_capture_delta(), move_analysis.score_delta(),
            move_analysis.pseudo_score_after_move(), move.to_string());
    }

    std::ranges::sort(move_analyses.begin(), move_analyses.end());

    auto const& [winning_move, opponent_winning_move, capturing_move,
                 opponent_capturing_move, score_after_move,
                 pseudo_score_after_move, position_str] = move_analyses.back();

    Position    position {position_str};
    std::string rationale;

    if (move_analyses.size() == 1)
    {
        rationale = "it is the only available move.";
        return {position, rationale};
    }

    if (winning_move)
    {
        rationale = "it is a winning move.";
    }
    else if (opponent_winning_move)
    {
        rationale = "it prevents the opponent from winning.";
    }
    else if (capturing_move)
    {
        rationale = "it is a capturing move.";
    }
    else if (opponent_capturing_move)
    {
        rationale = "it is a capture blocking move.";
    }
    else if (pseudo_score_after_move > 0)
    {
        rationale = "it is the most optimal move.";
    }
    else
    {
        rationale = "it is an arbitrary move. All moves are equally optimal.";
    }

    return {position, rationale};
}
