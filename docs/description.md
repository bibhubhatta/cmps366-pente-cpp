# Pente
*Copied from https://pages.ramapo.edu/~amruth/teaching/opl/projects/pente/problem.html for access inside IDE.*

Pente is a two-player board game, designed by Gary Gabriel.

## The Objective

The objective of this game is to win by either:

-   Placing at least five of one's stones in an uninterrupted line (row/column/diagonal) or
-   Capturing five pairs of opponent's stones

while also scoring as many points as possible.

## The Players

Two players play this game - one player will be the human user of your program, and the other player will be your program/computer. The two players will play a "tournament", consisting of one or more rounds. Each round will consist of the two players playing till one of them wins the round.

## The Setup

### Pieces

The game uses white and black stones.

### Setup

The game uses a 19 X 19 board. The columns are numbered A through S from left to right. The rows are numbered 1 through 19 from bottom to top. The intersections are referred to by their column and row numbers, e.g., the bottom left intersection is A1 and the center of the board is K10.

## A Round

### First Player

On the first round, a coin is tossed and the human player is asked to call the toss. If the human player correctly calls the toss, the human player plays first. Otherwise, the computer player plays first.

On subsequent rounds, the player with the most points plays first. If both the players have the same number of points, a coin is tossed to determine the first player.

The first player plays white stones. The other player plays black stones.

### A Turn

On the first turn, the first player must place a white stone at the center (K10). The other player can place a black stone anywhere on the board.

On the second turn, the first player must place another white stone at least 3 intersections away from the first white stone.

Thereafter, the two players alternate turns, placing one stone per turn on the board.

A player can capture a pair of the opponent's stones if the opponent's stones are next to each other in a row, column or diagonal and the player places their stones on both sides of the row, column or diagonal. The following illustrates capturing a pair of white stones (in a row, column and diagonal) when a black stone is placed at the location marked by an asterisk. Note that it also illustrates a case where a player captures  **two**  pairs of white stones by placing a single black stone.

    BWW*

    B     *        BWW*
    W      W          W
    W       W         W
    *        B        B
    

### End of a round

A round ends when a player:

-   Places at least five of one's stones in an uninterrupted line (row/column/diagonal) or
-   Captures five pairs of opponent's stones

### Score

When a round ends, each player is awarded points as follows:

-   5 points to the player who has placed at least five of their stones in an uniterrupted row/column/diagonal
-   1 point for each pair of opponent's stones captured
-   1 point for each set of four of the player's stones placed in an uninterrupted row/column/diagonal

A player would want to maximize their score and may want to delay winning a round when possible.

## A Tournament

After each round, the human player is asked whether she/he wants to play another round.

-   If yes, another round is played as described above and the process is repeated.
-   If no, the winner of the tournament is announced and the game quits. The winner of the tournament is the player who has earned the most number of points over all the rounds. If both the players have the same number of points, the tournament is a draw.

## Computer Player's Strategy

The computer must have a strategy for both creating initiative and countering initiative:

-   Creating initiative: The computer places stones in a row/column/diagonal towards getting five stones in a row. But, it should avoid placing two stones next to each other since the opponent can easily capture them.
-   Countering opponent's initiative: If the opponent places two stones in a row/column/diagonal, it should prioritize capturing the pair. If the opponent places three or four stones in a row/column/diagonal, it should try to block the arrangement.

Your computer player must play to win. It must have a strategy for both creating and countering initiatives.

## Implementation

-   **User Interface:**  You must provide a user-friendly interface for the game. For C++, LISP and Prolog, ASCII graphics and command-line input are sufficient.
    -   You must refer to the intersections on the board with row and column numbers, as in A1, K10 and S19 in all your user interface interactions.  
        The board must be displayed with these labels.
    -   All human inputs must be validated.
    -   The turn played by the computer as well as the strategy it uses must be displayed on the screen, e.g.,
        
        The computer placed a black stone at L10 in order to create a row of three stones.
        
-   **Help Mode:**  When the human player is playing, the computer must provide a help mode:
    -   If the human player asks for a recommendation, the computer must suggest the best intersection where the next stone must be placed and the reason why it should be placed there. The computer must use its own playing strategy to come up with this recommendation.
-   **Serialization:**  The user should be able to suspend the game after either player has placed a stone, and resume at a later time from where the game was left off. In order to do this:
    -   Provide the option to serialize after each player has placed a stone.
    -   When the serialization option is exercised, your program should save the current state of the game into a file and quit. We will use text format for the file instead of XML, SOAP or binary format traditionally used.  
        
        ----------
        
        The text format for C++/Java will be as follows:
        
        Board:
        OOOOOOOOOOOOOOOOOOO
        OOOOOOOOOOOOOOOOOOO
        OOOOOOOOOOOOOOOOOOO
        OOOOOOOOOOOOOOOOOOO
        OOOOOOOOOOOOOOOOOOO
        OOOOOOOOOOOOOOOOOOO
        OOOOOOOOOOOOOOOOOOO
        OOOOOOOOOOOOOOOOOOO
        OOOOOOOOOOOOOOOOOOO
        OOOOOOOOOOWOOOOOOOO
        OOOOOOOOOOOOOOOOOOO
        OOOOOOOOOOOOOOOOOOO
        OOOOOOOOOOOOOOOOOOO
        OOOOOOOOOOOOOOOOOOO
        OOOOOOOOOOOOOOOOOOO
        OOOOOOOOOOOOOOOOOOO
        OOOOOOOOOOOOOOOOOOO
        OOOOOOOOOOOOOOOOOOO
        OOOOOOOOOOOOOOOOOOO
        
        Human:
        Captured pairs: 0
        Score: 0
        
        Computer:
        Captured pairs: 0
        Score: 0
        
        Next Player: Human - Black
        
        In the above board, the computer played first and placed a white tile in the center (K10). The next player to play will be the human player playing black. In this round, neither player has captured any pairs of opponent's stones yet. Neither player has earned any points from previous rounds.
        
        The text format for LISP will be as follows:
        
        (
           ; Board:
           (
              ( O O O O O O O O O O O O O O O O O O O )
              ( O O O O O O O O O O O O O O O O O O O )
              ( O O O O O O O O O O O O O O O O O O O )
              ( O O O O O O O O O O O O O O O O O O O )
              ( O O O O O O O O O O O O O O O O O O O )
              ( O O O O O O O O O O O O O O O O O O O )
              ( O O O O O O O O O O O O O O O O O O O )
              ( O O O O O O O O O O O O O O O O O O O )
              ( O O O O O O O O O O O O O O O O O O O )
              ( O O O O O O O O O O W O O O O O O O O )
              ( O O O O O O O O O O O O O O O O O O O )
              ( O O O O O O O O O O O O O O O O O O O )
              ( O O O O O O O O O O O O O O O O O O O )
              ( O O O O O O O O O O O O O O O O O O O )
              ( O O O O O O O O O O O O O O O O O O O )
              ( O O O O O O O O O O O O O O O O O O O )
              ( O O O O O O O O O O O O O O O O O O O )
              ( O O O O O O O O O O O O O O O O O O O )
              ( O O O O O O O O O O O O O O O O O O O )
            )
        
            ; Human
            0 0
        
            ; Computer
            0 0
        
            ; Next player
            Human Black
        }
        
        Note that the comments above are for your convenience. You do not need to parse those - they will not appear in actual serialization files.
        
        The text format for Prolog will be as follows:
        
        [
           ; Board:
           [
              [ o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o ],
              [ o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o ],
              [ o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o ],
              [ o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o ],
              [ o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o ],
              [ o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o ],
              [ o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o ],
              [ o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o ],
              [ o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o ],
              [ o, o, o, o, o, o, o, o, o, o, w, o, o, o, o, o, o, o, o ],
              [ o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o ],
              [ o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o ],
              [ o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o ],
              [ o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o ],
              [ o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o ],
              [ o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o ],
              [ o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o ],
              [ o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o ],
              [ o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o ]
            ],
        
            ; human
            0, 0,
        
            ; computer
            0, 0,
        
            ; next player
            human, black
        }
        
        Note that the comments above are for your convenience. You do not need to parse those - they will not appear in actual serialization files.
        
        ----------
        
    -   When your program is started, it should provide the option to resume a game from a previously saved state. If yes, it should ask for the name of the text file from which to read the current state of the game, and resume playing from that state.
-   Using any part of code available in textbooks, through generative AI or on the web is unacceptable.

## Grading

Please see the rubric for some of the features on which your program will be graded.

### Milestones

The following are recommended milestones for each project:

-   Week 1: Implementation of the board, turns, round, winning and scoring; verification of the correctness of the placement of each stone; all the user interface to obtain human player's moves, and random movements by the computer.
-   Week 2: All the strategies for the computer player, help for human player and serialization.
-   Week 3: Full project demonstration

## Acknowledgments

This game was adapted from the descriptions at [Wikipedia](https://en.wikipedia.org/wiki/Pente) and [Ultraboardgames.com](https://www.ultraboardgames.com/pente/game-rules.php#google_vignette).