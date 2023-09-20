#include "TournamentAnnouncement.h"

#include <iostream>

TournamentAnnouncement::TournamentAnnouncement(const Tournament& tournament)
    : tournament(tournament)
{
}

void TournamentAnnouncement::announce_results() const
{
    std::cout << "Implement TournamentAnnouncement::announce_results()"
              << std::endl;
}