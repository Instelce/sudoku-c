#include <stdio.h>
#include <stdlib.h>
// #include "types.h"


/* 
Le maximun de move est réglé sur MAX_MOVE
chaque movement à 3 valeurs : 
    0: l'index du mouvement
    1: la position de la ligne
    2: la position de la colonne
    3: la valeur de la case
*/
int ** initMoves() {
    int **moves;
    moves = (int **) malloc(sizeof(int *) * MAX_MOVE);

    for (int i = 0; i < MAX_MOVE; i++) {
        moves[i] = (int *) malloc(sizeof(int) * 4);
    }

    // init first value of all moves to -1
    for (int i = 0; i < MAX_MOVE; i++) {
        moves[i][0] = -1;
    }

    return moves;
}


void printMoves(int **moves, int lastMoveIndex) {
    for (int i = 0; i < MAX_MOVE; i++) {
        if (moves[i][0] != -1) {
            if (lastMoveIndex == i) {
                printfColor(YELLOW_FG, -1, "#%d - (%d,%d) %d\n", moves[i][0] + 1, moves[i][1] + 1, moves[i][2] + 1, moves[i][3]);
            } else {
                printf("#%d - (%d,%d) %d\n", moves[i][0] + 1, moves[i][1] + 1, moves[i][2] + 1, moves[i][3]);
            }
        }
    }
}


void updateMove(int **moves, int moveIndex, int rowPos, int colPos, int caseValue) {
    moves[moveIndex][0] = moveIndex;
    moves[moveIndex][1] = rowPos;
    moves[moveIndex][2] = colPos;
    moves[moveIndex][3] = caseValue;
}