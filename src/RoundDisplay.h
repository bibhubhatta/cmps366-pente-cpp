#pragma once

#include <iostream>

#include <fmt/format.h>
#include <tabulate/table.hpp>

#include "Round.h"

class RoundDisplay
{
  public:
    RoundDisplay(const Round& round) : round(round) {};

    tabulate::Table get_table() const;
    tabulate::Table score_table() const;

    void show() const;

    void announce_scores_and_winner() const;

  private:
    const Round&    round;
    tabulate::Table history_table(int no_history_entries) const;
};
