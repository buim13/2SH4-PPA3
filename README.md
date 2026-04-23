# Project Preparation Activity 3 – Create a Scavenger Hunt “Guess the Word” Gam

The basic game mechanism:
- The game has a built-in Goal String containing 15-25 ASCII characters, hidden away from the player.
- Upon startup...
o 5 random characters are picked from the Goal String and randomly placed on the game board.
o The Mystery String consisting of unrevealed characters ‘?’ is displayed at the bottom of the game board,
indicating the number of characters to be collected / revealed to match the Goal String.
o The Move Count is also displayed at the bottom of the game board, indicating the distance (number of game board spaces) the player has covered on the game board since the start of the game.
- The player must control the player object to collect the ASCII characters on the board using WASD control.
o For every collected character (i.e., after a collision)...
- Its occurrences will be revealed in the Mystery String; the uncollected characters will remain ‘?’.
- The remaining items on the board are removed, and another 5 randomly selected characters from the Goal String will be generated and randomly placed on the board.

The goal of the game is to consume minimal move count to win the game by revealing all characters in the Mystery String to match the Goal Strin
