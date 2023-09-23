#pragma once

#include <iostream>

#include <format>
#include <tabulate/table.hpp>

#include "Round.h"

class RoundDisplay
{
  public:
    RoundDisplay(const Round& round) : round(round) {};

    tabulate::Table get_table() const;
    tabulate::Table score_table() const;

    void show() const;

  private:
    const Round& round;
};
