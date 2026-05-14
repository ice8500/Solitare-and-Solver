#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "moves.h"
#include "card.h"
#include "gamelogic.h"

// LAST HINT MEMORY
Hint lastHint = {-1, 0, -1, -1};

// SAVE UNDO

void saveUndo(UndoMove **undoTop,
              int from,
              int to,
              int amount,
              bool flippedCard,
              bool wasStockDraw)
{

    UndoMove *u =
        malloc(sizeof(UndoMove));

    u->from = from;
    u->to = to;
    u->amount = amount;

    u->flippedCard = flippedCard;

    u->wasStockDraw = wasStockDraw;

    u->next = *undoTop;

    *undoTop = u;
}

// MOVE CARDS

void moveCards(DeckStack tableau[7],
               DeckStack foundation[4],
               DeckStack *waste,
               UndoMove **undoTop,
               int from,
               int amount,
               int to)
{

    int fromIndex = from - 1;
    int toIndex = to - 1;

    bool toFoundation =
        (to >= 8 && to <= 11);
    bool flipped = false;

    // Waste Move
    if (from == 0)
    {

        if (amount != 1)
        {

            printf("Can only move 1 card from waste\n");
            return;
        }

        Card *moving =
            detachWithoutValidation(waste,
                                    1);

        if (moving == NULL)
        {

            printf("Waste is empty\n");
            return;
        }

        // Waste -> Foundation
        if (toFoundation)
        {

            int f = to - 8;

            if (canMoveToFoundation(
                    moving,
                    &foundation[f]))
            {

                pushBottom(
                    &foundation[f],
                    moving);

                printf("Moved waste card to Foundation %d\n",
                       to);
            }
            else
            {

                pushBottom(waste,
                           moving);

                printf("Illegal foundation move\n");
            }

            return;
        }

        // Waste -> Tableau
        if (to < 1 ||
            to > 7)
        {

            pushBottom(waste,
                       moving);

            printf("Invalid destination\n");
            return;
        }

        Card *dest =
            getBottomCard(
                &tableau[toIndex]);

        if (canMove(moving,
                    dest))
        {

            pushBottom(
                &tableau[toIndex],
                moving);

            printf("Moved waste card to Col %d\n",
                   to);
        }
        else
        {

            pushBottom(waste,
                       moving);

            printf("Illegal move\n");
        }

        return;
    }

    // Tableau Source
    if (from < 1 ||
        from > 7)
    {

        printf("Invalid source column\n");
        return;
    }

    Card *moving =
        detachStack(
            &tableau[fromIndex],
            amount);

    if (moving == NULL)
    {

        printf("Cannot move stack\n");
        return;
    }

    // Tableau -> Foundation
    if (toFoundation)
    {

        if (amount != 1)
        {

            attachStack(
                &tableau[fromIndex],
                moving);

            printf("Can only move 1 card to foundation\n");
            return;
        }

        int f = to - 8;

        if (canMoveToFoundation(
                moving,
                &foundation[f]))
        {

            pushBottom(
                &foundation[f],
                moving);

            Card *flip =
                getBottomCard(
                    &tableau[fromIndex]);

            if (flip != NULL &&
                flip->Faceup == false)
            {

                flip->Faceup = true;

                flipped = true;
            }

            printf("Moved to Foundation %d\n",
                   to);

            saveUndo(
                undoTop,
                from,
                to,
                amount,
                flipped,
                false);
        }
        else
        {

            attachStack(
                &tableau[fromIndex],
                moving);

            printf("Illegal foundation move\n");
        }

        return;
    }

    // Tableau -> Tableau
    if (to < 1 ||
        to > 7)
    {

        attachStack(
            &tableau[fromIndex],
            moving);

        printf("Invalid destination\n");
        return;
    }

    Card *dest =
        getBottomCard(
            &tableau[toIndex]);

    if (canMove(moving,
                dest))
    {

        attachStack(
            &tableau[toIndex],
            moving);

        Card *flip =
            getBottomCard(
                &tableau[fromIndex]);

        if (flip != NULL &&
            flip->Faceup == false)
        {

            flip->Faceup = true;

            flipped = true;
        }

        printf("Moved %d cards from Col %d to Col %d\n",
               amount,
               from,
               to);

        saveUndo(
            undoTop,
            from,
            to,
            amount,
            flipped,
            false);
    }
    else
    {

        attachStack(
            &tableau[fromIndex],
            moving);

        printf("Illegal move\n");
    }
}

// UNDO LAST MOVE

void undoLastMove(DeckStack tableau[7],
                  DeckStack foundation[4],
                  DeckStack *stock,
                  DeckStack *waste,
                  UndoMove **undoTop)
{

    if (*undoTop == NULL)
    {

        printf("Nothing to undo\n");
        return;
    }

    UndoMove *u = *undoTop;

    *undoTop = u->next;

    // Undo Stock Draw
    if (u->wasStockDraw)
    {

        for (int i = 0;
             i < u->amount;
             i++)
        {

            Card *c =
                getBottomCard(waste);

            if (c == NULL)
                break;

            if (c->prev != NULL)
            {

                c->prev->next = NULL;
            }
            else
            {

                waste->top = NULL;
            }

            waste->totalcount--;

            c->next = NULL;
            c->prev = NULL;

            c->Faceup = false;

            push(stock,
                 c);
        }

        printf("Undid stock draw\n");
    }

    // Undo Normal Move
    else
    {

        DeckStack *fromStack = NULL;
        DeckStack *toStack = NULL;

        if (u->to >= 1 &&
            u->to <= 7)
        {

            toStack =
                &tableau[u->to - 1];
        }
        else
        {

            toStack =
                &foundation[u->to - 8];
        }

        if (u->from >= 1 &&
            u->from <= 7)
        {

            fromStack =
                &tableau[u->from - 1];
        }
        else
        {

            fromStack =
                &foundation[u->from - 8];
        }

        // Re-hide previously flipped card FIRST
        if (u->flippedCard)
        {
            Card *bottom =
                getBottomCard(fromStack);

            if (bottom != NULL)
            {
                bottom->Faceup = false;
            }
        }

        Card *stack =
            detachWithoutValidation(
                toStack,
                u->amount);

        attachStack(
            fromStack,
            stack);

        printf("Move undone\n");
    }

    free(u);
}

int evaluateMove(DeckStack tableau[7],
                 int from,
                 int amount,
                 int to)
{

    int score = 0;

    // Foundation Good
    if (to >= 8 &&
        to <= 11)
    {

        score += 100;
    }

    // Empty Column Good
    if (to >= 1 &&
        to <= 7)
    {

        if (tableau[to - 1].top == NULL)
        {

            score += 60;
        }
    }

    // Reveal Hidden Card
    if (from >= 1 &&
        from <= 7)
    {

        DeckStack *src =
            &tableau[from - 1];

        Card *bottom =
            getBottomCard(src);

        if (bottom != NULL &&
            bottom->prev != NULL &&
            bottom->prev->Faceup == false)
        {

            score += 80;
        }
    }

    // Bigger Stack Better
    score += amount * 5;

    return score;
}

bool isReverseMove(Hint last,
                   int from,
                   int amount,
                   int to)
{
    return

        last.from == to &&

        last.to == from &&

        last.amount == amount;
} 


// FIND BEST HINT

Hint findBestHint(DeckStack tableau[7],
                  DeckStack foundation[4],
                  DeckStack *waste)
{

    Hint best;

    best.from = -1;
    best.amount = 0;
    best.to = -1;
    best.score = -1;

    // Tableau Moves
    for (int from = 1;
         from <= 7;
         from++)
    {

        DeckStack *src =
            &tableau[from - 1];

        int max =
            src->totalcount;

        for (int amount = 1;
             amount <= max;
             amount++)
        {

            Card *moving =
                detachWithoutValidation(src,
                                        amount);

            if (moving == NULL)
            {
                continue;
            }

            if (moving->Faceup == false)
            {
                attachStack(src, moving);
                continue;
            }

            Card *check = moving;

            bool valid = true;

            while (check->next != NULL)
            {
                Card *next = check->next;

                bool sameColor =

                    (strcmp(check->suit, "♥") == 0 ||
                     strcmp(check->suit, "♦") == 0)

                    ==

                    (strcmp(next->suit, "♥") == 0 ||
                     strcmp(next->suit, "♦") == 0);

                if (sameColor)
                {
                    valid = false;
                    break;
                }

                if (check->rank != next->rank + 1)
                {
                    valid = false;
                    break;
                }

                check = next;
            }

            if (!valid)
            {
                attachStack(src, moving);
                continue;
            }

            // Tableau Destination
            for (int to = 1;
                 to <= 7;
                 to++)
            {

                if (to == from)
                    continue;

                Card *dest =
                    getBottomCard(
                        &tableau[to - 1]);

                if (canMove(moving,
                            dest))
                {

                    int score =
                        evaluateMove(
                            tableau,
                            from,
                            amount,
                            to);

                    // Prevent Reverse Loop
                    if (isReverseMove(lastHint,
                                      from,
                                      amount,
                                      to))
                    {
                        score -= 200;
                    }

                    if (score > best.score)
                    {

                        best.from = from;
                        best.amount = amount;
                        best.to = to;
                        best.score = score;
                    }
                }
            }

            // Foundation Destination
            for (int to = 8;
                 to <= 11;
                 to++)
            {

                if (amount != 1)
                    continue;

                int f = to - 8;

                if (canMoveToFoundation(
                        moving,
                        &foundation[f]))
                {

                    int score =
                        evaluateMove(
                            tableau,
                            from,
                            amount,
                            to);

                    // Prevent Reverse Loop
                    if (isReverseMove(lastHint,
                                      from,
                                      amount,
                                      to))
                    {
                        score -= 200;
                    }

                    if (score > best.score)
                    {

                        best.from = from;
                        best.amount = amount;
                        best.to = to;
                        best.score = score;
                    }
                }
            }

            attachStack(src,
                        moving);
            moving = NULL;
        }
    }

    // Waste Moves
    Card *wasteCard =
        getBottomCard(waste);

    if (wasteCard != NULL)
    {

        // Waste -> Tableau
        for (int to = 1;
             to <= 7;
             to++)
        {

            Card *dest =
                getBottomCard(
                    &tableau[to - 1]);

            if (canMove(wasteCard,
                        dest))
            {

                int score =
                    evaluateMove(
                        tableau,
                        0,
                        1,
                        to);

                // Prevent Reverse Loop
                if (isReverseMove(lastHint,
                                  0,
                                  1,
                                  to))
                {
                    score -= 200;
                }

                if (score > best.score)
                {

                    best.from = 0;
                    best.amount = 1;
                    best.to = to;
                    best.score = score;
                }
            }
        }
    }

    // Waste -> Foundation
    if (wasteCard != NULL)
    {
        for (int to = 8;
             to <= 11;
             to++)
        {

            int f = to - 8;

            if (canMoveToFoundation(
                    wasteCard,
                    &foundation[f]))
            {

                int score =
                    evaluateMove(
                        tableau,
                        0,
                        1,
                        to);

                // Prevent Reverse Loop
                if (isReverseMove(lastHint,
                                  0,
                                  1,
                                  to))
                {
                    score -= 200;
                }

                if (score > best.score)
                {

                    best.from = 0;
                    best.amount = 1;
                    best.to = to;
                    best.score = score;
                }
            }
        }
    }

    return best;
}
