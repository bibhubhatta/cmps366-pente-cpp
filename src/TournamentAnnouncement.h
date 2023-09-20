#pragma once

#include "Tournament.h"

class TournamentAnnouncement
{
  public:
    TournamentAnnouncement(const Tournament& tournament);

    void announce_results() const;

  private:
    const Tournament& tournament;
};
