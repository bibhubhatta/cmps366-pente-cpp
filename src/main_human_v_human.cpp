#include "Human.h"
#include "Tournament.h"
#include "TournamentAnnouncement.h"

int main()
{
    Tournament tournament;

    Human human("Human 1");
    Human human2("Human 2");

    tournament.add_player(&human);
    tournament.add_player(&human2);

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