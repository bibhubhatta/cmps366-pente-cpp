#include <iostream>

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
