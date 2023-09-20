#pragma once

#include "Roster.h"

class Round
{
  public:
    Round(const Roster& roster);
    void  play();
    Score get_score(Player* player) const;

  private:
    Roster roster;
};