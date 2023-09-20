#include <algorithm>

#include "Computer.h"
#include "Exceptions.h"
#include "Human.h"
#include "Round.h"

Round::Round(const Roster& roster) : roster(roster) {}

void Round::play()
{
    Player* current_player = first_player();
    Player* other_player = next_player(current_player);

    player_to_stone[current_player] = Board::WHITE_STONE;
    player_to_stone[other_player] = Board::BLACK_STONE;

    while (true)
    {
        Position current_move = current_player->get_move(board);

        try
        {
            board.make_move(current_move);
        }
        catch (const GameWon& e)
        {
            winner = current_player;
            is_over = true;
            break;
        }
        catch (const GameDrawn& e)
        {
            is_draw = true;
            is_over = true;
            break;
        }

        current_player = next_player(current_player);
    }
}

Score Round::get_score(Player* player) const
{
    Stone stone = player_to_stone.at(player);
    return board.get_score(stone);
}

Player* Round::first_player() const
{

    // If all players have the same score, do a coin toss
    std::set<Score> scores;
    for (auto& player : roster.get_players())
    {
        scores.insert(roster.get_score(player));
    }

    if (scores.size() == 1) // All players have the same score
    {
        Human* human = get_human_player();
        if (human->won_toss())
        {
            return human;
        }
        else
        {
            return get_computer_player();
        }
    }

    // Sort players by score and return the highest scoring player
    auto players = sorted_players();
    return players[0];
}

std::vector<Player*> Round::sorted_players() const
{
    std::vector<Player*> players_ = roster.get_players();
    std::sort(players_.begin(), players_.end(),
              [this](Player* a, Player* b)
              { return roster.get_score(a) > roster.get_score(b); });
    return players_;
}

Human* Round::get_human_player() const
{
    for (auto& player : roster.get_players())
    {
        if (dynamic_cast<Human*>(player))
        {
            return dynamic_cast<Human*>(player);
        }
    }

    throw std::runtime_error("No human player found");
}

Player* Round::get_computer_player() const
{
    for (auto& player : roster.get_players())
    {
        if (dynamic_cast<Computer*>(player))
        {
            return player;
        }
    }

    throw std::runtime_error("No computer player found");
}

Player* Round::next_player(Player* player) const
{
    for (auto& p : roster.get_players())
    {
        if (p != player)
        {
            return p;
        }
    }

    throw std::runtime_error("No other player found");
}