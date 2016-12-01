# Othello
Othello(Reversi) Game

Implemented in Mac OS, used GCC compiler, in C

---DIRECTION KEY---

Left: 9'o clock direction

Right: 3'o clock direction

Up: 12'o clock direction

Down: 6'o clock direction

LeftUp: 11'o clock direction

LeftDown: 7'o hour direction

RightUp: 1'o hour direction

RightDown: 5'o hour direction

---FUNCTIONS---

clearBoard: sets all elements of the board to 0

initGame: initial setup of the game. Place black and white token in the middle of the board

printMap: prints the board

isValidInput: checks whether input is out-of-bounds

reverse: reverses the token to its direction. ex)reverseLeftDown: reverses token(s) to 7'o clock direction

check: checks whether tokens are eligible to reverse to certain direction.

isValidLocation: checks whether input location is eligible to put the stone.

getUserInput: recieves the coordinate.

isAble: checks whether player is eligible to place his or her token.

isOver: checks whether the game is over

playAgain: asks people to play again.
