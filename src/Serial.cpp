#include <fstream>
#include <sstream>

#include "Serial.h"

Serial::Serial(const std::string& serial_string)
{
    // Parse the string into a vector of lines for easier access
    std::string        line;
    std::istringstream iss(serial_string);
    while (std::getline(iss, line))
    {
        lines.push_back(line);
    }
}

int Serial::get_number_in_line(int line_number) const
{
    // Get number from a line with key:value format
    // Can be used to get score, captured pairs, etc
    std::string line = lines[line_number];
    std::string number_str = line.substr(line.find(":") + 1, line.length() - 1);

    int number = stoi(number_str);
    return number;
}

int Serial::get_human_score() const { return get_number_in_line(23); }

int Serial::get_computer_score() const { return get_number_in_line(27); }

int Serial::get_human_captured_pairs() const { return get_number_in_line(22); }

int Serial::get_computer_captured_pairs() const
{
    return get_number_in_line(26);
}

Board Serial::get_board() const
{
    // Prepare the parameters for the Board::from_string function
    std::string board_string;
    for (int i = 1; i < 20; i++)
    {
        board_string += lines[i];
    }

    char human_stone = get_human_stone();

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
    // Line 30: "Next Player: Human - Black"

    // Get the string after the colon
    std::string line = lines[29];
    std::string player_stone =
        line.substr(line.find(':') + 2, line.length() - 1);

    // Split the string by the dash
    std::string delimiter = " - ";
    std::string player = player_stone.substr(0, player_stone.find(delimiter));
    std::string stone =
        player_stone.substr(player_stone.find(delimiter) + delimiter.length(),
                            player_stone.length() - 1);

    char stone_char;
    if (player == "Human")
    {
        stone_char = stone[0];
    }
    else if (player == "Computer")
    {
        stone_char = other_stone(stone[0]);
    }
    // TODO: Raise exception if player is neither Human nor Computer

    return stone_char;
}

char Serial::get_computer_stone() const
{
    // Reverse of the human stone
    char human_stone = get_human_stone();
    return other_stone(human_stone);
}

char Serial::other_stone(char stone) const { return stone == 'W' ? 'B' : 'W'; }

Serial Serial::from_file(const std::string& filename)
{

    std::ifstream file;

    file.open(filename);

    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open file");
    }

    std::string serial_string;
    std::string line;
    while (std::getline(file, line))
    {
        serial_string += line + "\n";
    }

    file.close();

    return {serial_string};
}
