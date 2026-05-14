#include "card.h"
#include <stdio.h>

// CREATE CARD

Card *createcard(int rank,
                 char *suit)
{

    Card *c = malloc(sizeof(Card));

    c->rank = rank;
    c->suit = suit;

    c->Faceup = false;

    c->next = NULL;
    c->prev = NULL;

    return c;
}

// PUSH TOP

void push(DeckStack *s,
          Card *c)
{

    if (c == NULL)
        return;

    c->next = s->top;

    if (s->top != NULL)
        s->top->prev = c;

    s->top = c;

    s->totalcount++;
}

// PUSH BOTTOM

void pushBottom(DeckStack *s,
                Card *c)
{

    if (c == NULL)
        return;

    c->next = NULL;
    c->prev = NULL;

    // Empty
    if (s->top == NULL)
    {

        s->top = c;
        s->totalcount++;

        return;
    }

    Card *temp = s->top;

    while (temp->next != NULL)
    {

        temp = temp->next;
    }

    temp->next = c;
    c->prev = temp;

    s->totalcount++;
}

// POP TOP

Card *pop(DeckStack *s)
{

    if (s->top == NULL)
        return NULL;

    Card *c = s->top;

    s->top = c->next;

    if (s->top != NULL)
        s->top->prev = NULL;

    c->next = NULL;
    c->prev = NULL;

    s->totalcount--;

    return c;
}

// GET BOTTOM CARD

Card *getBottomCard(DeckStack *s)
{

    if (s->top == NULL)
        return NULL;

    Card *temp = s->top;

    while (temp->next != NULL)
    {

        temp = temp->next;
    }

    return temp;
}