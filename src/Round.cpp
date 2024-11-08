#include <algorithm>

#include "Computer.h"
#include "Exceptions.h"
#include "Human.h"
#include "Round.h"
#include "RoundDisplay.h"

Round::Round(const Roster& roster) : roster(roster) {}

Round::Round(const Roster& roster, const Board& board, Player* white_player,
             Player* black_player)
    : roster(roster), board(board)
{
    player_to_stone[white_player] = Board::WHITE_STONE;
    player_to_stone[black_player] = Board::BLACK_STONE;
}

void Round::play()
{
    RoundDisplay display(*this);

    Player* current_player = get_current_player();

    if (current_player == nullptr)
    {
        current_player = first_player();
        Player* other_player = next_player(current_player);
        player_to_stone[current_player] = Board::WHITE_STONE;
        player_to_stone[other_player] = Board::BLACK_STONE;
    }

    while (true)
    {
        display.show();

        Position current_move = current_player->get_move(board);

        try
        {

            board.make_move(current_move);
        }
        catch (const GameWon& e)
        {
            winner = current_player;
            is_over = true;
            win_by = e.reason;
        }
        catch (const GameDrawn& e)
        {
            is_draw = true;
            is_over = true;
        }

        move_history.emplace_back(current_player, current_move);

        if (is_over)
        {
            break;
        }

        current_player = next_player(current_player);
    }

    display.announce_scores_and_winner();
}

Player* Round::get_current_player() const
{
    Stone current_stone = board.get_turn();

    Player* current_player = nullptr;
    for (auto& [player, stone] : player_to_stone)
    {
        if (stone == current_stone)
        {
            current_player = player;
        }
    }

    return current_player;
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
            return next_player(human);
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

Board Round::get_board() const { return board; }

std::vector<Player*> Round::get_players() const
{
    std::vector<Player*> players = roster.get_players();
    return players;
}

Player* Round::get_winner() const { return winner; }

Stone Round::get_stone(Player* Player) const
{
    return player_to_stone.at(Player);
}

int Round::get_no_captures(Player* Player) const
{
    return board.get_no_captured_pairs(get_stone(next_player(Player)));
}

int Round::get_no_four_in_sequence(Player* Player) const
{
    Stone stone = get_stone(Player);
    return board.get_no_stone_sequences(stone, 4);
}
MoveHistory Round::get_move_history() const { return move_history; }

std::string Round::get_winning_reason() const { return win_by; }

bool Round::is_round_over() const { return is_over; }

std::string Round::get_serial_string() const
{

    std::string board_str = board.to_string();

    Player* human = get_human_player();
    Player* computer = get_computer_player();

    int human_captured_pairs = get_no_captures(human);
    int human_score = roster.get_score(human);

    int computer_captured_pairs = get_no_captures(computer);
    int computer_score = roster.get_score(computer);

    Player*     next_player = get_current_player();
    std::string next_player_str = (next_player == human) ? "Human" : "Computer";
    Stone       next_stone = board.get_turn();
    std::string next_stone_str =
        (next_stone == Board::WHITE_STONE) ? "White" : "Black";

    std::string serial = fmt::format(
        "Board:\n"
        "{}" // Board
        "\n"
        "Human:\n"
        "Captured pairs: {}\n"
        "Score: {}\n"
        "\n"
        "Computer:\n"
        "Captured pairs: {}\n"
        "Score: {}\n"
        "\n"
        "Next Player: {} - {}",

        board_str, human_captured_pairs, human_score, computer_captured_pairs,
        computer_score, next_player_str, next_stone_str);
    return serial;
}
