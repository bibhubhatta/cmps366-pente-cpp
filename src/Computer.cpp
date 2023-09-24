#include "Computer.h"
#include <iostream>

#include "Strategy.h"
#include "helpers.h"

Position Computer::get_move(const Board& board) const
{
    auto [move, rationale] = Strategy(board).get_move();

    std::cout << "Computer's move: " << move.to_string() << std::endl;
    std::cout << "Rationale: " << rationale << std::endl;

    return move;
}
