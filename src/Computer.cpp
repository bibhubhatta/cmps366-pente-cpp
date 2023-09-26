#include "Computer.h"
#include "Strategy.h"

#include "fmt/core.h"

Position Computer::get_move(const Board& board) const
{
    auto [move, rationale] = Strategy(board).get_move();

    fmt::print("Computer chose {} because {}\n", move.to_string(), rationale);

    return move;
}
