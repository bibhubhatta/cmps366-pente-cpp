#include "Computer.h"
#include "Human.h"
#include "Tournament.h"
#include "TournamentAnnouncement.h"

#include <fmt/format.h>

bool user_wants_to_load_from_file()
{
    while (true)
    {
        fmt::print("Do you want to load from file? (y/n): ");
        std::string answer;

        std::cin >> answer;

        if (answer == "y")
        {
            return true;
        }
        else if (answer == "n")
        {
            return false;
        }
        else
        {
            fmt::print("Invalid answer. Please try again.\n");
        }
    }
}

void update_tournament_from_file(Tournament& tournament)
{

    while (true)
    {
        try
        {
            std::string filename;
            fmt::print("Please enter the filename: ");
            std::cin >> filename;

            tournament.update_from_file(filename);
            break;
        }
        catch (const std::exception& e)
        {
            fmt::print("Error: {}\n", e.what());
            fmt::print("Please try again.\n");
        }
    }
}

int main()
{
    Tournament             tournament;
    TournamentAnnouncement announcement {tournament};

    Human    human("Human");
    Computer computer("Computer");

    tournament.add_player(&human);
    tournament.add_player(&computer);

    if (user_wants_to_load_from_file())
    {
        update_tournament_from_file(tournament);
    }

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