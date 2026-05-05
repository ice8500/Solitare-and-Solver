#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#define MAXSIZE 52 //MAXIMUM DECK SIZE

// ♠ ♥ ♦ ♣

// Cards
typedef struct Card {
    int rank;
    char *suit; //Need to be pointer because we use emoji not normal alphabet
    bool Faceup;
    struct Card *next;
    struct Card *prev;
} Card;

// Stack
typedef struct {
    Card *top;
    int totalcount;
} DeckStack;

// Create Cards
Card *createcard(int rank, char *suit){
    Card *c = malloc(sizeof(Card));
    c->rank = rank;
    c->suit = suit;
    c->Faceup = false; //Not used yet, will become 1 once it has been open
    c->next = NULL;
    c->prev = NULL;
    return c;
} //Implemented by 3448; To create a card in the doubly linked list

// Stack
void push(DeckStack *s, Card *c){
    if(c == NULL) return;

    c->next = s->top;
    if(s->top != NULL)
        s->top->prev = c;

    s->top = c;
    s->totalcount++;
}

Card *pop(DeckStack *s){
    if(s->top == NULL) return NULL;

    Card *c = s->top;
    s->top = c->next;

    if(s->top != NULL)
        s->top->prev = NULL;

    s->totalcount--;
    return c;
}

// Shuffle Deck
DeckStack createShuffledDeck(){
    char *suits[4] = {"♠", "♥", "♦", "♣"};
    Card *temp[52];
    int cardNum = 0;

    // create ordered deck
    for(int i = 0; i < 4; i++){
        for(int j = 1; j <= 13; j++){
            temp[cardNum++] = createcard(j, suits[i]); //Should Store All 52 Card in order to the temp deck now
        }
    }//Implemented by 3448;

    // Shuffling
    for(int i = 51; i > 0; i--){
        int r = rand() % (i + 1);
        Card *t = temp[i];
        temp[i] = temp[r];
        temp[r] = t;
    }

    // Build Stock Stack
    DeckStack deck;
    deck.top = NULL;
    deck.totalcount = 0;

    for(int i = 0; i < 52; i++){
        push(&deck, temp[i]);
    }

    return deck;
}

// Recycle Stock
void recycleStock(DeckStack *stock, DeckStack *waste){
    if(waste->top == NULL){
        printf("No cards to recycle.\n");
        return;
    }

    printf("Recycling waste back into stock\n");

    Card *c;
    while((c = pop(waste)) != NULL){
        c->Faceup = false;
        push(stock, c);
    }
}

// Draw 3 Cards
void drawFromStock(DeckStack *stock, DeckStack *waste){
    for(int i = 0; i < 3; i++){
        if(stock->top == NULL){
            recycleStock(stock, waste);
        }

        Card *c = pop(stock);
        if(c == NULL) return;

        c->Faceup = true;
        push(waste, c);
    }
}

// Print Waste
void printWaste(DeckStack *waste){
    printf("Waste (top 3): ");

    Card *temp = waste->top;
    int count = 0;

    while(temp != NULL && count < 3){
        printf("%d%s ", temp->rank, temp->suit);
        temp = temp->next;
        count++;
    }

    printf("\n");
}

// Print TABLEAU
void printTableau(Card *tableau[7][7]){
    printf("\n=-= TABLEAU =-=\n");

    for(int col = 0; col < 7; col++){
        printf("Col %d: ", col);

        for(int row = 0; row <= col; row++){
            Card *c = tableau[col][row];

            if(c == NULL) continue;

            if(c->Faceup)
                printf("%d%s ", c->rank, c->suit);
            else
                printf("XX ");
        }
        printf("\n");
    }
    printf("\n=-=-=-=-=-=-=-=-=\n");
}

// Print Game State
void printGame(Card *tableau[7][7], DeckStack *stock, DeckStack *waste){
    printTableau(tableau);

    printf("\nStock remaining: %d cards hidden\n", stock->totalcount);

    printWaste(waste);
}

int main(){
    srand(time(NULL));

    // Stock and Waste
    DeckStack stock = createShuffledDeck();

    DeckStack waste;
    waste.top = NULL;
    waste.totalcount = 0;

    // TABLEAU
    Card *tableau[7][7] = {NULL};

    for(int col = 0; col < 7; col++){
        for(int row = 0; row <= col; row++){
            Card *c = pop(&stock);
            tableau[col][row] = c;

            if(row == col)
                c->Faceup = true;
        }
    }

    // First Time
    printGame(tableau, &stock, &waste);

    // Looping
    char cmd[20];

    while(1){
        printf("\nCommand (/stock, /quit): ");
        scanf("%s", cmd);

        if(strcmp(cmd, "/stock") == 0){
            drawFromStock(&stock, &waste);
        }
        else if(strcmp(cmd, "/quit") == 0){
            break;
        }
        else{
            printf("Unknown command\n");
        }

        // ALWAYS REFRESH AFTER A COMMAND
        printGame(tableau, &stock, &waste);
    }

    return 0;
}
