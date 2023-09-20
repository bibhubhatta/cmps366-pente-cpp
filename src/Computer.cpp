#include "Computer.h"

#include "helpers.cpp"
// I can't figure out how to just use the .h file without getting a linker error
// It is possible with declaring each template instantiation, but that beats the
// purpose of using templates for containers

Position Computer::get_move(const Board& board) const
{
    std::set<Position> available_moves = board.get_available_positions();
    auto               random_move = get_random_element(available_moves);

    return random_move;
}
