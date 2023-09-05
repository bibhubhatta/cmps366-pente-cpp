#include <sstream>

#include "SerialFile.h"

SerialFile::SerialFile(const std::string &path) {

    // Read all lines from the file into lines
    std::istringstream iss{path};
    std::string line;

    while (std::getline(iss, line)) {
        lines.push_back(line);
    }
}

int SerialFile::get_human_score() const {
    return 0;
}

int SerialFile::get_computer_score() const {
    return 0;
}

int SerialFile::get_human_captured_pairs() const {
    return 0;
}

int SerialFile::get_computer_captured_pairs() const {
    return 0;
}
