#pragma once

#include <string>
#include <vector>

class Serial
{
  public:
    Serial(const std::string& serial_string) ;

    int get_human_score() const;

    int get_computer_score() const;

    int get_human_captured_pairs() const;

    int get_computer_captured_pairs() const;

  private:
    std::vector<std::string> lines;

    int get_number(int line_number) const;
};