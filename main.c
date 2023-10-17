#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "utils/grid_utils.h"
#include "utils/term_utils.h"


t_grid originalSudokuGrid = {
        {5,3,0, 0,7,0, 0,0,0},
        {6,0,0, 1,9,5, 0,0,0},
        {0,9,8, 0,0,0, 0,6,0},

        {8,0,0, 0,6,0, 0,0,3},
        {4,0,0, 8,0,3, 0,0,1},
        {7,0,0, 0,2,0, 0,0,6},

        {0,6,0, 0,0,0, 2,8,0},
        {1,0,0, 4,1,9, 0,0,5},
        {0,0,0, 0,8,0, 0,7,9},
};

int test[2][2] = {{2,3}, {4, 80}};


void showMainMenu(int *canShowGame, int *loop);
void showGame(int *canShowGame);


int main() {
    int loop;
    int canShowGame;

    // initialisation des variables
    loop = 1;
    canShowGame = 1;

    // boucle qui permet de changer de menu à l'infini
    while (loop) {
        showMainMenu(&canShowGame, &loop);
        showGame(&canShowGame);
    }

    return 0;
}


void showMainMenu(int *canShowGame, int *loop) {
    int choice;

    choice = -1;

    // boucle du menu principal
    while (choice != 2 && *canShowGame == 0) {
        system("clear");

        printf("Sudoku\n[1] Nouvelle partie\n[2] Quitter\n: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1: *canShowGame = 1;
                break;
            case 2: *loop = 0;
                break;
            default:
                printf("\nSaisie incorrecte\n\n");
                break;
        }
    }
}


void showGame(int *canShowGame) {
    int choice;
    char errorsBuffer[100];
    int caseNum;
    int caseValue;

    int **sudokuGrid;
    int ***sudokuBlockGrid;

    sudokuGrid = createSudokuGridFrom(originalSudokuGrid, SUDOKU_SIZE);
    sudokuBlockGrid = createSudokuBlockGridFrom(originalSudokuGrid, SUDOKU_SIZE);

    printf("%d\n", countValue(sudokuGrid, 5));
    printf("%d\n", countRowValue(sudokuGrid, 0, 5));
    printf("%d\n", countColValue(sudokuGrid, 5, 5));
    printf("%d\n", countBlockValue(sudokuBlockGrid, 4, 8));
    printf("%d\n", getBlockIndice(sudokuBlockGrid, 2, 4));

    for (int arr = 0; arr < SUDOKU_SIZE; arr++) {
        printf("BLock %d\n", arr);
        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 3; col++) {
                printf("%d ", sudokuBlockGrid[arr][row][col]);
            }
            printf("\n");
        }
        printf("\n");
    }

    choice = -1;
    strcpy(errorsBuffer, "");

    // boucle du jeu
    while (*canShowGame) {
        // system("clear");

        printf("Sudoku\n");
        printSudoku(sudokuGrid, 0);

        printf("\n[1] Insérer une valeur\n[2] Retour au coup précédent\n[3] Retour au coup ...\n[4] Quitter la partie\n");
        printf("%s\n: ", errorsBuffer);
        scanf("%d", &choice);
        getchar();

        if (choice == 1) {
            clearTerm();
            printf("Sudoku\n");
            printSudoku(sudokuGrid, 1);

            printf("[-1] Retour\n\n");
            printf("Taper le numéro de la case que vous souhaiter modifier\n: ");
            scanf("%d", &caseNum);

            while (caseNum != -1) {
                while (caseNum < -1 || caseNum > 0)
                {
                    
                }
            }

            // checker si la valeur existe dans la matrix des cases vide

        } else if (choice == 4) {
            *canShowGame = 0;
        } else {
            strcpy(errorsBuffer, "Saisie incorrecte");
        }
    }

    freeSudokuGrid(sudokuGrid, SUDOKU_SIZE);
    freeSudokuBlockGrid(sudokuBlockGrid, SUDOKU_SIZE);
}
