#include "gamelogic.h"
#include <string.h>
#include <time.h>
#include <stdio.h>

bool isRed(Card *c)
{

    return

        strcmp(c->suit, "♥") == 0 ||

        strcmp(c->suit, "♦") == 0;
}


bool canMove(Card *moving,
             Card *dest)
{
    // SAFETY CHECK
    if (moving == NULL)
    {
        return false;
    }

    // Empty Only King
    if (dest == NULL)
    {

        return moving->rank == 13;
    }

    // Alternate Color
    if (isRed(moving) ==
        isRed(dest))
    {

        return false;
    }

    // Descending
    if (moving->rank !=
        dest->rank - 1)
    {

        return false;
    }

    return true;
}


bool canMoveToFoundation(Card *moving,
                         DeckStack *foundation)
{

    // SAFETY CHECK
    if (moving == NULL)
    {
        return false;
    }

    // Empty -> Ace
    if (foundation->top == NULL)
    {

        return moving->rank == 1;
    }

    Card *top =
        getBottomCard(foundation);

    // Same Suit
    if (strcmp(moving->suit,
               top->suit) != 0)
    {

        return false;
    }

    // Ascending
    if (moving->rank !=
        top->rank + 1)
    {

        return false;
    }

    return true;
}

Card *detachStack(DeckStack *s,
                  int amount)
{

    if (s->top == NULL)
        return NULL;

    Card *temp =
        getBottomCard(s);

    for (int i = 1;
         i < amount;
         i++)
    {

        if (temp->prev == NULL)
        {

            return NULL;
        }

        temp = temp->prev;
    }

    // Cannot Move Facedown
    if (temp->Faceup == false)
    {

        return NULL;
    }

    // Validate Internal Stack
    Card *check = temp;

    while (check->next != NULL)
    {

        Card *next =
            check->next;

        bool sameColor =

            (strcmp(check->suit, "♥") == 0 ||
             strcmp(check->suit, "♦") == 0)

            ==

            (strcmp(next->suit, "♥") == 0 ||
             strcmp(next->suit, "♦") == 0);

        if (sameColor)
        {

            return NULL;
        }

        if (check->rank !=
            next->rank + 1)
        {

            return NULL;
        }

        check = next;
    }

    // Detach
    if (temp->prev != NULL)
    {

        temp->prev->next = NULL;
        temp->prev = NULL;
    }
    else
    {

        s->top = NULL;
    }

    s->totalcount -= amount;

    return temp;
}

Card *detachWithoutValidation(DeckStack *s,
                              int amount)
{

    if (s->top == NULL)
        return NULL;

    Card *temp =
        getBottomCard(s);

    for (int i = 1;
         i < amount;
         i++)
    {

        if (temp->prev == NULL)
        {

            return NULL;
        }

        temp = temp->prev;
    }

    // Detach ONLY
    if (temp->prev != NULL)
    {

        temp->prev->next = NULL;
        temp->prev = NULL;
    }
    else
    {

        s->top = NULL;
    }

    s->totalcount -= amount;

    return temp;
}


void attachStack(DeckStack *s,
                 Card *stack)
{

    if (stack == NULL)
        return;

    // Empty
    if (s->top == NULL)
    {

        s->top = stack;

        Card *count = stack;

        while (count != NULL)
        {

            s->totalcount++;
            count = count->next;
        }

        return;
    }

    Card *bottom =
        getBottomCard(s);

    bottom->next = stack;
    stack->prev = bottom;

    Card *count = stack;

    while (count != NULL)
    {

        s->totalcount++;
        count = count->next;
    }
}

// CREATE SHUFFLED DECK

DeckStack createShuffledDeck()
{

    char *suits[4] = {

        "♠",
        "♥",
        "♦",
        "♣"};

    Card *temp[52];

    int cardNum = 0;

    // Ordered Deck
    for (int i = 0;
         i < 4;
         i++)
    {

        for (int j = 1;
             j <= 13;
             j++)
        {

            temp[cardNum++] =
                createcard(j,
                           suits[i]);
        }
    }

    // Shuffle
    for (int i = 51;
         i > 0;
         i--)
    {

        int r =
            rand() % (i + 1);

        Card *t = temp[i];

        temp[i] = temp[r];
        temp[r] = t;
    }

    DeckStack deck;

    deck.top = NULL;
    deck.totalcount = 0;

    for (int i = 0;
         i < 52;
         i++)
    {

        push(&deck,
             temp[i]);
    }

    return deck;
}

void recycleStock(DeckStack *stock,
                  DeckStack *waste)
{

    if (waste->top == NULL)
    {

        printf("No cards to recycle.\n");
        return;
    }

    printf("Recycling waste back into stock\n");

    Card *c;

    while ((c = detachWithoutValidation(waste, 1)) != NULL)
    {

        c->Faceup = false;

        push(stock, c);
    }
}

void drawFromStock(DeckStack *stock,
                   DeckStack *waste)
{

    for (int i = 0;
         i < 3;
         i++)
    {

        if (stock->top == NULL)
        {

            recycleStock(stock,
                         waste);
        }

        Card *c = pop(stock);

        if (c == NULL)
            return;

        c->Faceup = true;

        pushBottom(waste, c);
    }
}

// CHECK WIN

bool checkWin(DeckStack foundation[4])
{

    int total = 0;

    for (int i = 0;
         i < 4;
         i++)
    {

        total +=
            foundation[i].totalcount;
    }

    return total == 52;
}