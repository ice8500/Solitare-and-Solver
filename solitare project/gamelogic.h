#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "card.h"

// Rules & Validation
bool isRed(Card *c);
bool canMove(Card *moving, Card *dest);
bool canMoveToFoundation(Card *moving, DeckStack *foundation);
bool checkWin(DeckStack foundation[4]);

// Stack Manipulation
Card *detachStack(DeckStack *s, int amount);
Card *detachWithoutValidation(DeckStack *s, int amount);
void attachStack(DeckStack *s, Card *stack);

// Deck Operations
DeckStack createShuffledDeck();
void recycleStock(DeckStack *stock, DeckStack *waste);
void drawFromStock(DeckStack *stock, DeckStack *waste);

#endif