#include "fmt/format.h"
#include <algorithm>
#include <queue>

#include "MoveAnalysis.h"
#include "Strategy.h"
#include "helpers.h"

Strategy::Strategy(Board board) : board(board) {}

StrategicMove Strategy::get_move()
{
    using analysis = std::tuple<int, int, int, int, int, int, Score, Score, int,
                                std::string>;
    std::vector<analysis> move_analyses;

    std::set<Position> available_moves = board.get_available_positions();
    for (const auto& move : available_moves)
    {
        MoveAnalysis move_analysis(board, move);

        move_analyses.emplace_back(
            move_analysis.is_winning_move(),
            move_analysis.is_opponent_winning_move(),
            move_analysis.score_delta(), move_analysis.opponent_score_delta(),
            move_analysis.capture_delta(),
            move_analysis.opponent_capture_delta(),
            move_analysis.is_capture_safe(),
            move_analysis.pseudo_score_after_move(),
            -move_analysis.distance_from_center(), move.to_string());
    }

    std::sort(move_analyses.begin(), move_analyses.end());

    auto const& [winning_move, opponent_winning_move, score_delta,
                 opponent_score_delta, capturing_move, opponent_capturing_move,
                 is_capture_safe, pseudo_score_after_move,
                 neg_distance_from_center, position_str] = move_analyses.back();

    Position    position {position_str};
    std::string rationale;

    if (move_analyses.size() == 1)
    {
        rationale = "it is the only available move.";
        return {position, rationale};
    }

    if (winning_move)
    {

        auto second_best_move = move_analyses.back();
        move_analyses.pop_back();

        if (std::get<0>(second_best_move))
        {
            Score second_best_score_delta = std::get<2>(second_best_move);
            if (score_delta > second_best_score_delta)
            {
                rationale = fmt::format(
                    "it is the best winning move; it scores {} more points "
                    "than the second best winning move.",
                    score_delta - second_best_score_delta);

                return {position, rationale};
            }
            else
            {

                for (auto x : move_analyses)
                {
                    if (std::get<2>(x))
                    {
                        rationale = fmt::format(
                            "even though there are more than one winning moves "
                            "that lead to same score, opponent can win on "
                            "their next move. So playing the winning move.");
                        return {position, rationale};
                    }
                }
                
                rationale =
                    fmt::format("There are more than one winning moves that "
                                "lead to the same score, so holding off.");
                while (std::get<0>(move_analyses.back()))
                {
                    move_analyses.pop_back();
                }
            }
        }
    }

    auto const& [winning_move_, opponent_winning_move_, score_delta_,
                 opponent_score_delta_, capturing_move_,
                 opponent_capturing_move_, is_capture_safe_,
                 pseudo_score_after_move_, neg_distance_from_center_,
                 position_str_] = move_analyses.back();

    if (opponent_winning_move_)
    {
        rationale = fmt::format(
            "it prevents the opponent from making a winning move. {}",
            rationale);
    }
    else if (capturing_move_)
    {
        rationale = fmt::format("it is a capturing move. {}", rationale);
    }
    else if (opponent_capturing_move_)
    {
        rationale = fmt::format("it is a capture blocking move. {}", rationale);
    }
    else if (pseudo_score_after_move_ > 0)
    {
        rationale = fmt::format("it is the most optimal move. {}", rationale);
    }
    else
    {
        rationale = fmt::format(
            "it is an arbitrary move. All moves are equally optimal. {}",
            rationale);
    }

    return {position, rationale};
}
