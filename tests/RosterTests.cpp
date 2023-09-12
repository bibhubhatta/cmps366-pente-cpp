#include "gtest/gtest.h"

#include "Computer.h"
#include "Human.h"
#include "Roster.h"

TEST(RosterTests, addPlayer)
{
    Roster roster;

    // Using a Human player for testing because Player is an abstract class

    Human player("Player 1");
    roster.add_player(player);
    EXPECT_EQ(roster.get_score(player), 0);

    roster.add_score(player, 10);
    EXPECT_EQ(roster.get_score(player), 10);

    Human player2("Player 2");
    roster.add_player(player2);
    roster.add_score(player2, 20);

    EXPECT_EQ(roster.get_score(player2), 20);
}

TEST(RosterTests, getPlayer)
{
    Roster roster;

    Human    human("Human");
    Computer computer("Computer");

    roster.add_player(human);
    roster.add_player(computer);

    Player* human_ptr = roster.get_player("Human");
    Player* computer_ptr = roster.get_player("Computer");

    EXPECT_EQ(human_ptr->name, human.name);
    EXPECT_EQ(computer_ptr->name, computer.name);
}
