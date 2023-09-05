#include <fstream>
#include <iostream>
#include <string>

#include "Tournament.h"
#include "helpers.cpp"

Tournament::Tournament() = default;

void Tournament::load(const std::string& filename)
{
    Round round {};

    std::vector<std::string> lines = get_lines(filename);

    std::string current_board_string {""};
    for (int i = 1; i < 20; i++)
    {
        current_board_string += lines[i];
    }
    Board current_board = Board::from_string(current_board_string);

    int human_captured_pairs = std::stoi(lines[22]);
    int human_score = std::stoi(lines[23]);

    int computer_captured_pairs = std::stoi(lines[26]);
    int computer_score = std::stoi(lines[27]);

    std::string next_player_string = lines[29];

    if (next_player_string == "Next Player: Human - Black")
    {
        Player black_player = human;
        Player white_player = computer;
        char   next_stone_color = 'B';
    }

    if (next_player_string == "Next Player: Human - White")
    {
        Player white_player = human;
        Player black_player = computer;
        char   next_stone_color = 'W';
    }

    if (next_player_string == "Next Player: Computer - Black")
    {
        Player black_player = computer;
        Player white_player = human;
        char   next_stone_color = 'B';
    }

    if (next_player_string == "Next Player: Computer - White")
    {
        Player black_player = computer;
        Player white_player = human;
        char   next_stone_color = 'W';
    }

    Round round =
        Round(white_player, black_player, current_board, next_stone_color,
              human_captured_pairs, computer_captured_pairs);
}
