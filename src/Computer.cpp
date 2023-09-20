#include "Computer.h"

#include "helpers.h"

Position Computer::get_move(const Board& board) const
{
    std::set<Position> available_moves = board.get_available_positions();
    auto               random_move = get_random_element(available_moves);

    return random_move;
}
