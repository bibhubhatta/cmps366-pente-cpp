#pragma once


#include <vector>
#include <string>

class SerialFile {
public:

    SerialFile(const std::string &path);

    int get_human_score() const;

    int get_computer_score() const;

    int get_human_captured_pairs() const;

    int get_computer_captured_pairs() const;

private:
    std::vector<std::string> lines;

};
