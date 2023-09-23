#include <iostream>
#include <random>

#include "BoardDisplay.h"
#include "Exceptions.h"
#include "Human.h"
#include "helpers.h"

Position Human::get_move(const Board& board) const
{
    std::string input;
    while (true) // Loop to validate input
    {
        std::cout << "Enter a move (e.g. A10): ";
        std::cin >> input;

        char col = input[0];
        col = toupper(col);
        std::string row_str = input.substr(1);

        input = col + row_str;

        try
        {
            Position position {input};
            Board    board_copy = board;
            board_copy.make_move(position);
        }
        catch (const InvalidMove& e)
        {
            std::cout << e.what() << std::endl;
            std::cout << "Please try again." << std::endl;
            continue;
        }
        catch (const GameOver& e)
        {
            // Pass because this is a valid move
        }
        catch (const std::exception& e)
        {
            std::cout << "Invalid input.";
            std::cout << e.what() << std::endl;
            std::cout << "Please try again." << std::endl;
            continue;
        }

        break;
    }

    return {input};
}

bool Human::won_toss()
{
    std::vector<char> choices {'h', 't'};
    char              choice = '\0';
    while (true) // Loop to validate input
    {
        std::cout << "Tossing coin..." << std::endl;
        std::cout << "Heads or tails? (h/t): ";

        std::cin >> choice;
        choice = tolower(choice);

        if (contains(choices, choice))
        {
            break;
        }
        else
        {
            std::cout << "Invalid choice. Please try again." << std::endl;
            continue;
        }
    }

    char result = get_random_element(choices);
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
