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

- <windows.h> : Used in order to force the terminal to use UTF-8 Encoding for the suits.

Header Files

- "card.h" : Contains the structs of the cards and the deck, and the basic commands for the card and deck stacking.

- "gamelogic.h" : Contains the rules check required for moves, stack manipulation logic, and the deck opertaions (the stock and creating a shuffled deck).

- "moves.h" : Contains the hint logic and implementation, and undo logic and implementation.

- "ui.h" : Contains rank converter, and the print game function

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

## Run Locally

Run this command in a folder on a terminal containing all the .h files and .c files: 
gcc Final_Project_CPE112.c card.c gamelogic.c ui.c moves.c -o solitaire.exe

Or use the existing compiled application (the program isn't recognized, so anti malware protection may comeup)

## Authors

- Thanadol Nakinpong 68070503424 [https://github.com/1i14sd]

- Phuwanat Kraisit 608070503448 [https://github.com/ice8500]

- Pontakorn Tantisirimongkol 68070503476 [https://github.com/PlatPT07]

- Achira Tinnakorn 68070503496 [https://github.com/Charader]

