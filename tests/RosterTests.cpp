#include "gtest/gtest.h"

#include "Human.h"
#include "Roster.h"

TEST(RosterTests, addPlayer) {
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
