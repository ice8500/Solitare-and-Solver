// SOLITAIRE IN C

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#include "card.h"
#include "gamelogic.h"
#include "ui.h"
#include "moves.h"

#ifdef _WIN32 // Check if run on Windows
#include <windows.h>
#endif

#define MAXSIZE 52 // MAXIMUM DECK SIZE

// ♠ ♥ ♦ ♣

// MAIN

int main()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    srand(time(NULL));

    // Stock
    DeckStack stock =
        createShuffledDeck();

    // Waste
    DeckStack waste;

    waste.top = NULL;
    waste.totalcount = 0;

    // Tableau
    DeckStack tableau[7];

    for (int i = 0;
         i < 7;
         i++)
    {

        tableau[i].top = NULL;
        tableau[i].totalcount = 0;
    }

    // Foundation
    DeckStack foundation[4];

    for (int i = 0;
         i < 4;
         i++)
    {

        foundation[i].top = NULL;
        foundation[i].totalcount = 0;
    }

    // Undo Stack
    UndoMove *undoTop = NULL;

    // Deal Tableau
    for (int col = 0;
         col < 7;
         col++)
    {

        for (int row = 0;
             row <= col;
             row++)
        {

            Card *c =
                pop(&stock);

            if (row == col)
            {

                c->Faceup = true;
            }

            pushBottom(
                &tableau[col],
                c);
        }
    }

    // First Print
    printGame(tableau,
              foundation,
              &stock,
              &waste);

    // Commands
    char cmd[100];

    while (1)
    {

        printf("\n0 = Waste | 1-7 = Columns | 8-11 = Foundation\n");

        printf("Command (/stock, /move from amount to, /hint, /undo, /help, /quit): ");

        fgets(cmd,
              sizeof(cmd),
              stdin);

        cmd[strcspn(cmd,
                    "\n")] = 0;

        // Stock
        if (strcmp(cmd,
                   "/stock") == 0)
        {

            int before =
                waste.totalcount;

            drawFromStock(
                &stock,
                &waste);

            int drawn =
                waste.totalcount - before;

            saveUndo(
                &undoTop,
                -1,
                -1,
                drawn,
                false,
                true);
        }

        // Move
        else if (strncmp(cmd,
                         "/move",
                         5) == 0)
        {

            int from;
            int amount;
            int to;

            if (sscanf(cmd,
                       "/move %d %d %d",
                       &from,
                       &amount,
                       &to) == 3)
            {

                moveCards(
                    tableau,
                    foundation,
                    &waste,
                    &undoTop,
                    from,
                    amount,
                    to);
            }
            else
            {

                printf("Usage: /move from amount to\n");
            }
        }

        // Hint
        else if (strcmp(cmd,
                        "/hint") == 0)
        {

            Hint h =
                findBestHint(
                    tableau,
                    foundation,
                    &waste);

            if (h.score == -1)
            {

                if (stock.totalcount > 0)
                {

                    printf("No possible moves found\n");
                    printf("Try using /stock\n");
                }
                else
                {

                    printf("No possible moves left\n");
                    printf("Game may be unwinnable\n");
                }
            }
            else
            {

                printf("\n=== BEST MOVE ===\n");

                printf("/move %d %d %d\n",
                       h.from,
                       h.amount,
                       h.to);
                lastHint = h;
            }
        }

        // Undo
        else if (strcmp(cmd,
                        "/undo") == 0)
        {

            undoLastMove(
                tableau,
                foundation,
                &stock,
                &waste,
                &undoTop);
        }

        // Help
        else if (strcmp(cmd,
                        "/help") == 0)
        {
            printf("\n  +----------------------------------- GAME COMMANDS ------------------------------------+\n");
            printf("  |                                                                                      |\n");
            printf("  |  Locations: 0 = Waste | 1-7 = Columns | 8-11 = Foundations.                          |\n");
            printf("  |                                                                                      |\n");
            printf("  |  /stock : Draw 3 cards from stock to waste.                                          |\n");
            printf("  |  /move  : Move revealed cards between stacks.                                        |\n");
            printf("  |           (e.g., '/move 1 2 8' is to move 2 cards from Column 1 to Foundation 8)     |\n");
            printf("  |  /hint  : Display the best possible move.                                            |\n");
            printf("  |  /undo  : Reverse the last action.                                                   |\n");
            printf("  |  /help  : Display this help message.                                                 |\n");
            printf("  |  /quit  : Exit the program.                                                          |\n");
            printf("  |                                                                                      |\n");
            printf("  +--------------------------------------------------------------------------------------+\n");
        }

        // Quit
        else if (strcmp(cmd,
                        "/quit") == 0)
        {

            break;
        }

        // Unknown
        else
        {

            printf("Unknown command\n");
        }

        // WIN CHECK

        if (checkWin(foundation))
        {

            printf("\n=-=-=-=-=-=-=-=-=-=-=\n");
            printf("CONGRATULATIONS!\n");
            printf("YOU WON SOLITAIRE!\n");
            printf("=-=-=-=-=-=-=-=-=-=-=\n");

            break;
        }

        // Refresh
        printGame(tableau,
                  foundation,
                  &stock,
                  &waste);
    }

    return 0;
}
