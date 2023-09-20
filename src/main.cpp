#include "Computer.h"
#include "Human.h"
#include "Tournament.h"
#include "TournamentAnnouncement.h"

int main()
{
    Tournament tournament;

    Human    human("Human");
    Computer computer("Computer");

    tournament.add_player(&human);
    tournament.add_player(&computer);

    while (true)
    {
        tournament.play_a_round();

        if (human.wants_to_play_again())
        {
            continue;
        }
        else
        {
            break;
        }
    }

    TournamentAnnouncement(tournament).announce_results();
}