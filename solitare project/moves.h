#ifndef MOVES_H
#define MOVES_H

#include "gamelogic.h"

// Hint Move
typedef struct
{

    int from;
    int amount;
    int to;
    int score;

} Hint;

extern Hint lastHint;

// UNDO MOVE

typedef struct UndoMove
{

    int from;
    int to;
    int amount;

    bool flippedCard;

    bool wasStockDraw;

    struct UndoMove *next;

} UndoMove;

void saveUndo(UndoMove **undoTop, int from, int to, int amount, bool flippedCard, bool wasStockDraw);
void moveCards(DeckStack tableau[7], DeckStack foundation[4], DeckStack *waste, UndoMove **undoTop, int from, int amount, int to);
void undoLastMove(DeckStack tableau[7], DeckStack foundation[4], DeckStack *stock, DeckStack *waste, UndoMove **undoTop);
int evaluateMove(DeckStack tableau[7],int from,int amount,int to);
bool isReverseMove(Hint last,int from,int amount,int to);
Hint findBestHint(DeckStack tableau[7], DeckStack foundation[4], DeckStack *waste);

#endif