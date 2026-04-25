#include <stdio.h>
#include <stdlib.h>
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

typedef struct card {
    int num;
    char suit;
    struct card * next;
} card;

int deck() {
    char suit[4] = {"♠", "♥", "♦", "♣"};
    for(int i = 1; i <= 13; i++) { //1 = ACE, 11 = JACK, 12 = QUEEN, 13 = KING
        
    }
}

int main() {

}




