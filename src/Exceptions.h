#pragma once

#include <map>
#include <set>
#include <string>
#include <vector>

#include <fmt/format.h>

#include "Board.h"
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

class GameOver : public std::exception
{
  public:
    GameOver(const std::string& reason)
        : reason(reason), message("Game over. " + reason)
    {
    }

    const char* what() const noexcept override { return message.c_str(); }

    const std::string reason;
    const std::string message;
};

class GameWon : public GameOver
{
  public:
    GameWon(Stone winner, const std::string& reason)
        : GameOver(reason), winner(winner),
          message(fmt::format("Game won by {}. {}.", winner, reason))
    {
    }

    const Stone       winner;
    const std::string message;
};

class GameDrawn : public GameOver
{
  public:
    GameDrawn(const std::string& reason)
        : GameOver(reason), message("Game drawn. " + reason)
    {
    }

    const std::string message;
};