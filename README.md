# COMP10050 Assignment 2: Igel Argern Game
Iva Mechkarova – 18345221 
Morgan Collins-McCarthy – 18761429
## Iva:
* Fixed issues with inputs – players could end input with carriage return
* Wrote conditions to not allow invalid inputs – made player select a different colour if
they selected a colour that was chosen by another player already or if the colour was
out of range i.e. not 1-6.
* Function to place tokens – Created a function which allowed players to place all of
their tokens on the first column at the beginning of the game – the function allows
players to place a token on a square with the minimum number of tokens and that
does not contain their colour on top already.
* Sidestepping functionality in the function play_game – allowed player to select if they
wanted to move one of their tokens up or down. The player is asked to select the row
and column of the token they wish to move. If the token lies on row 0 it will be
moved down, if it is on row 5 it will move up but if it is in rows 1-4 then the player is
given the option to move up or down. If invalid row or column was entered the player
is asked to select a different row/column.
* Wrote conditions to only allow player to move their own token up/down.
* Made board print every time any tokens were placed/moved.
* Created function to move tokens forward i.e. pop token from current square and push
it onto stack of next square.
* Function to check if there are tokens in the row that corresponds to the number rolled
on the dice – if there is not the player is not asked to select a token to move.
* Fixing warning such as adding in function prototypes.
* Created a function to ask player to select a row (called when placing tokens and when
sidestepping).
* Function to keep track of how many tokens each player has in the last column. Made
sure the game ends when a winner is found (a player with 3 tokens in the last
column).
* When placing tokens at the start, if only square with the min number of tokens was
the same as the players color then the player was allowed place on this square.
* Made sure a min of 2 players was provided as input.
* Comments
* Report

## Morgan:
* Function to ask users to input player names.
* Function to ask each player to select their color.
* Edited print tokens function to print tokens in in color rather than black and white.
This allows players to quickly identify their tokens on the board.
* Added pointer to type struct token in struct token which is used for push and pop
functions (adding and removing tokens from stacks).
* Push function to allow tokens to be added to a stack – initialized top and curr
variables for each square to NULL. This function is crucial to allowing tokens to be
stacked on top of each other and only allowing the token on top to be moved.
* Pop function to allow tokens to be removed from a stack. This function was also
crucial to moving tokens around the board as it only allowed the token on top to be
moved.
* Roll dice function which generates a random number between 0 and 5 (couldn’t have
it as 1 to 6 like a normal dice as rows are labelled 0 to 5).
* Function which combines moving up/down and moving forward into one – this
function is called to move a token up, down or forward.
* Function which checks if there are tokens to be moved in a row and if there are it
checks if it is in an obstacle square or a normal square – if the token is in an obstacle
square it checks if there are tokens behind it and if there are it becomes a normal
square.
* Function to ask user to select a column – is called when moving a token forward or
when moving one up/down.
* Ensured game loops through each player and back to player 1 once the last player has
made their move.
* Made play_game function as efficient as possible
