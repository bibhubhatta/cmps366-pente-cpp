#pragma once

#include <map>
#include <set>
#include <string>
#include <vector>

#include "Position.h"

class InvalidMove : public std::exception
{
  public:
    InvalidMove(const Position move, const std::string& reason)
        : move(move), reason(reason)
    {
        message = "Invalid move. " + reason;
    }

    const char* what() const noexcept override { return message.c_str(); }

    const Position    move;
    const std::string reason;
    std::string       message;
};
