#include "ui.h"
#include "card.h"
#include <stdio.h>
#include <string.h>

// PRINT 1, 11, 12, 13 TO A, J, Q, K
const char *getRankStr(int rank)
{
    static const char *ranks[] = {"", "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};

    if (rank >= 1 && rank <= 13)
    {
        return ranks[rank];
    }
    return "?"; // <- For invalid ranks
}

// PRINT WASTE

void printWaste(DeckStack *waste)
{

    printf("Waste (0): ");

    int total = 0;

    Card *count =
        waste->top;

    while (count != NULL)
    {

        total++;
        count = count->next;
    }

    int skip = total - 3;

    if (skip < 0)
        skip = 0;

    Card *temp =
        waste->top;

    int index = 0;

    while (temp != NULL)
    {

        if (index >= skip)
        {

            printf("%s%s ",
                   getRankStr(temp->rank),
                   temp->suit);
        }

        temp = temp->next;
        index++;
    }

    printf("\n");
}

// PRINT FOUNDATION

void printFoundation(DeckStack foundation[4])
{

    printf("\n=-= FOUNDATION =-=\n");

    for (int i = 0;
         i < 4;
         i++)
    {

        int col = i + 8;

        printf("%d: ",
               col);

        Card *top =
            getBottomCard(
                &foundation[i]);

        if (top == NULL)
        {

            printf("[EMPTY]");
        }
        else
        {

            printf("%s%s",
                   getRankStr(top->rank),
                   top->suit);
        }

        printf("\n");
    }

    printf("--------------------\n");
}

// PRINT TABLEAU

void printTableau(DeckStack tableau[7])
{

    printf("\n=-= TABLEAU =-=\n");

    for (int col = 0;
         col < 7;
         col++)
    {

        printf("Col %d: ",
               col + 1);

        Card *temp =
            tableau[col].top;

        while (temp != NULL)
        {

            if (temp->Faceup)
                printf("%s%s ",
                       getRankStr(temp->rank),
                       temp->suit);
            else
                printf("XX ");

            temp = temp->next;
        }

        printf("\n");
    }

    printf("\n--------------------\n");
}

// PRINT GAME

void printGame(DeckStack tableau[7],
               DeckStack foundation[4],
               DeckStack *stock,
               DeckStack *waste)
{

    printTableau(tableau);

    printFoundation(foundation);

    printf("\nStock remaining: %d cards hidden\n",
           stock->totalcount);

    printWaste(waste);
}
