
# Colitare - A C Solitare program

A Solitare program in the terminal made using the C language in order to prove our competence in data structures by utilizing stacks and linked list to manage card movement, card information, game logic, and move history. 


## Tech Stack

Core Language

- C (C99/C11 Standard): The project uses standard C libraries for memory management and I/O. (A C compiler like gcc or clang is required to run the program)

Standard Libraries Used

- <stdio.h> : For standard input/output of the project.

- <stdlib.h> : For dynamic memory allocation of data structures.

- <stdbool.h> : For handling boolean logic within game states and move validations.

- <time.h> : Used for the seed of the random number generator each game.

- <string.h> : Utilized for suit comparisons and handling user command strings.

- <windows.h> : Used in order to force the terminal to use UTF-8 Encoding for the suits

## Features

- Standard Klondike Rules: Play with a full 52-card deck.

- Dynamic Card Management: Uses linked lists to handle card stacks (Tableau, Foundation, Stock, and Waste).

- Move Validation: Automatically checks for valid moves based on alternating colors and descending ranks.

- Hint System: An automated engine that evaluates the board and suggests the "best" move based on a scoring algorithm.

- Undo Functionality: Supports backtracking through move history using an undo stack.

- Automated Recycling: Automatically recycles the waste pile back into the stock when the stock is empty



## How to Play

Game Commands

- The board uses a numbering system for locations: 0 for Waste, 1-7 for Tableau columns, and 8-11 for Foundations.

- /stock : Draw 3 cards from the stock pile into the waste.

- /move [from] [amount] [to] : Move a specified number of revealed cards from one stack to another

- /hint : Display the move with the highest calculated score.

- /undo : Reverse the last action.

- /quit : Exit the program.

## Win/Loss Conditions

- Win : All 52 cards are successfully moved to the four Foundation piles.

- Game Over: No legal moves remain, the stock is empty, and the hint engine finds no possible actions.
