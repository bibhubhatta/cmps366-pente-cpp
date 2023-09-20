#include <iostream>

#include "Round.h"

Round::Round(const Roster& roster) : roster(roster) {}

void Round::play() { std::cout << "Implement Round::play()" << std::endl; }

Score Round::get_score(Player* player) const
{
    std::cout << "Implement Round::get_score()" << std::endl;
    return 0;
}
