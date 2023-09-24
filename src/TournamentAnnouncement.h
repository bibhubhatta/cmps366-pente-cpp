#pragma once

#include "Tournament.h"
#include "tabulate/table.hpp"

class TournamentAnnouncement
{
  public:
    TournamentAnnouncement(const Tournament& tournament);

    void announce_results() const;

    void announce_scores() const;

  private:
    const Tournament& tournament;

    tabulate::Table get_scores_table() const;
};
