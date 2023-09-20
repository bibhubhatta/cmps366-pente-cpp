#include <iostream>
#include <random>

#include "Human.h"

Position Human::get_move(const Board& board) const
{
    // TODO: Implement this
    // Stub for testing and compilation
    return Position {0, 0};
}

bool Human::won_toss()
{
    char choice = '\0';
    while (true) // Loop to validate input
    {
        std::cout << "Tossing coin..." << std::endl;
        std::cout << "Heads or tails? (h/t): ";

        std::cin >> choice;
        choice = tolower(choice);

        if (choice == 'h' || choice == 't')
        {
            break;
        }
        else
        {
            std::cout << "Invalid choice. Please try again." << std::endl;
            continue;
        }
    }

    char result = (std::rand() % 2 == 0) ? 'h' : 't';
    std::cout << "The coin landed on " << result << "." << std::endl;

    if (choice == result)
    {
        std::cout << "You won the toss!" << std::endl;
        return true;
    }
    else
    {
        std::cout << "You lost the toss." << std::endl;
        return false;
    }
}

bool Human::wants_to_play_again()
{
    char choice = '\0';

    while (true) // Loop to validate input
    {
        std::cout << "Would you like to play again? (y/n): ";
        std::cin >> choice;
        choice = tolower(choice);
        if (choice == 'y' || choice == 'n')
        {
            break;
        }
        else
        {
            std::cout << "Invalid choice. Please try again." << std::endl;
            continue;
        }
    }

    if (choice == 'y')
    {
        return true;
    }
    else
    {
        return false;
    }
}
