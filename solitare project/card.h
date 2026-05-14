#ifndef CARD_H
#define CARD_H

#include <stdbool.h>
#include <stdlib.h>

// Card
typedef struct Card {
    int rank;
    char *suit;
    bool Faceup;
    struct Card *next;
    struct Card *prev;
} Card;

// Stack
typedef struct {
    Card *top;
    int totalcount;
} DeckStack;

// Function
Card *createcard(int rank, char *suit);
void push(DeckStack *s, Card *c);
void pushBottom(DeckStack *s, Card *c);
Card *pop(DeckStack *s);
Card *getBottomCard(DeckStack *s);

#endif