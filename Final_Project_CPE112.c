#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#define ALL 13             //ACE - KING

int deck();
int move();
int next();
int undo();
int solver();
int next_column();          //circular_linked-list
int initail_column();       //linked-list
int complete_stack();       //stack

// ♠ ♥ ♦ ♣
Card* createcard(int rank, char suit)
{
    Card *card = (Card *)malloc(sizeof(Card));
    card->rank = rank;
    card->suit = suit;
    card->Faceup = 0;
    card->next = NULL;
    return card;
}//Implemented by 3448; To create a card in the doubly linked list

typedef struct Card {
    int num;
    bool Faceup;
    char suit;
    struct Card * next;
    struct Card * prev;
} Card;

int deck() {
    Card *head = NULL;
    Card *tail = NULL;
    char suit[4] = {"♠", "♥", "♦", "♣"};
    for(int i = 0; i < 4; i++)
    {
        for(int j = 1; j <= 13; j++) 
            {
                Card *newCard = createcard(j, suit[i]);

                if (head == NULL)
                {
                    head = newCard;
                    tail = newCard;
                    newCard->prev = NULL;
                }
                else
                {
                    newCard->prev = tail;
                    tail->next = newCard;
                    tail = newCard;
                }
            }
    }
} //Implemented by 3448; initalizing the deck by using doubly linked list starting from each suits, and from ace to king 

int main() {

}




