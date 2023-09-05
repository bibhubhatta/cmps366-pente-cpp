#include <sstream>

#include "Serial.h"

Serial::Serial(const std::string& serial_string)
{
    // Parse the string into lines
    std::string        line;
    std::istringstream iss(serial_string);
    while (std::getline(iss, line))
    {
        lines.push_back(line);
    }
}

int Serial::get_number(int line_number) const
{
    std::string line = lines[line_number];
    std::string number_str = line.substr(line.find(":") + 1, line.length() - 1);

    int number = stoi(number_str);
    return number;
}

int Serial::get_human_score() const { return get_number(23); }

int Serial::get_computer_score() const { return get_number(27); }

int Serial::get_human_captured_pairs() const { return get_number(22); }

int Serial::get_computer_captured_pairs() const { return get_number(26); }

Board Serial::get_board() const
{
    std::string board_string;
    for (int i = 1; i < 20; i++)
    {
        board_string += lines[i];
    }

    char human_stone = get_human_stone();
    char computer_stone = get_computer_stone();

    int no_captured_black_pairs = 0;
    int no_captured_white_pairs = 0;

    if (human_stone == 'W')
    {
        // human captures black pairs
        no_captured_black_pairs = get_human_captured_pairs();

        no_captured_white_pairs = get_computer_captured_pairs();
    }

    else if (human_stone == 'B')
    {
        // human captures white pairs
        no_captured_black_pairs = get_computer_captured_pairs();
        no_captured_white_pairs = get_human_captured_pairs();
    }

    Board board = Board::from_string(board_string, no_captured_white_pairs,
                                     no_captured_black_pairs);

    return board;
}

char Serial::get_human_stone() const
{
    // Line 30: Next Player: Human - Black

    // Get the string after the colon
    std::string line = lines[29];
    std::string player_stone =
        line.substr(line.find(":") + 2, line.length() - 1);

    // Split the string by the dash
    std::string delimiter = " - ";
    std::string player = player_stone.substr(0, player_stone.find(delimiter));
    std::string stone =
        player_stone.substr(player_stone.find(delimiter) + delimiter.length(),
                            player_stone.length() - 1);

    if (player == "Human")
    {
        return stone[0];
    }
    else if (player == "Computer")
    {
        return stone[0] == 'W' ? 'B' : 'W';
    }
}

char Serial::get_computer_stone() const
{
    char human_stone = get_human_stone();
    return human_stone == 'W' ? 'B' : 'W';
}
