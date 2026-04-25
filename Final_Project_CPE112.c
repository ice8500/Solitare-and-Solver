#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define TOTAL 13 //From A to K

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
    for(int i = 1; i <= 13; i++) { //1 = A, 11 = Jack, 12 = Queen, 13 = King
        
    }
}

int main() {

}




