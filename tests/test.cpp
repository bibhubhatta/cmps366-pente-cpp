#include <gtest/gtest.h>

#include "Round.h"
#include "Tournament.h"
#include <Board.h>

TEST(Serialization, Load)
{
    auto tournament = Tournament();
    tournament.load("serials/load.input");

    // Check that the current board is the same as the one in the file
    Board current_board = tournament.get_current_board();

    for (int row = 0; row < 19; row++)
    {
        for (int col = 0; col < 19; col++)
        {

            if (row == 10 && col == 10)
            {
                EXPECT_EQ(current_board.get_stone_color(
                              Position(row = row, col = col)),
                          'W');
                continue;
            }

            EXPECT_EQ(
                current_board.get_stone_color(Position(row = row, col = col)),
                'O');
        }
    }

    // Check that the current score is the same as the one in the file
    int human_score = tournament.get_human_score();
    int computer_score = tournament.get_computer_score();

    EXPECT_EQ(human_score, 0);
    EXPECT_EQ(computer_score, 0);

    // Check that the next player is the same as the one in the file
    Player next_player = tournament.get_round().get_next_player();
    EXPECT_EQ(next_player.name, "Human");

    // Check that the next stone color is the same as the one in the file
    char next_stone_color = tournament.get_round().get_next_stone_color();
    EXPECT_EQ(next_stone_color, 'B');
}