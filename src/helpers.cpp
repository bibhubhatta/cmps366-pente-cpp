#include <fstream>
#include <string>
#include <vector>

std::vector<std::string> get_lines(const std::string& filename)
{
    std::vector<std::string> lines;
    std::ifstream            file(filename);
    std::string              line;

    while (std::getline(file, line))
    {
        lines.push_back(line);
    }

    return lines;
}