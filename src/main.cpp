#include "Computer.h"
#include "Human.h"
#include "Tournament.h"
#include "TournamentAnnouncement.h"

int main()
{
    Tournament             tournament;
    TournamentAnnouncement announcement {tournament};

    Human    human("Human");
    Computer computer("Computer");

    tournament.add_player(&human);
    tournament.add_player(&computer);

    while (true)
    {
        tournament.play_a_round();
        announcement.announce_scores();

        if (human.wants_to_play_again())
        {
            continue;
        }
        else
        {
            break;
        }
    }

    announcement.announce_results();
}