#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "utils/term_utils.h"
#include "utils/grid_utils.h"
#include "moves.h"


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
void checkAllocation(int *pointer);


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
        clearTerm();

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
    int instruction;
    char previousMoveChoice;
    char returnMoveChoice;
    int cursorPosY;
    int cursorPosX;

    char errorsBuffer[300];

    int caseNum;
    int caseValue;
    int maxIndex;

    int *selectedCase;

    int showIndex;

    int **sudokuGrid;
    int **indexGrid;

    int **moves;
    int lastMoveIndex;

    // initialize values
    sudokuGrid = createSudokuGridFrom(originalSudokuGrid, SUDOKU_SIZE);
    indexGrid = createSudokuGrid(0, SUDOKU_SIZE);
    updateGridEmptyValueIndexFromGrid(indexGrid, sudokuGrid, SUDOKU_SIZE);

    printf("Check function\n");
    printf("Value %d\n", countValue(sudokuGrid, 5));
    printf("Row value %d\n", countRowValue(sudokuGrid, 0, 5));
    printf("Col value %d\n", countColValue(sudokuGrid, 5, 5));
    printf("Block value %d\n", countBlockValue(sudokuGrid, 3, 8));
    printf("Block indice %d\n\n", getBlockIndice(3, 8));

    choice = -1;
    instruction = 1;

    selectedCase = getValuePos(indexGrid, caseNum);
    checkAllocation(selectedCase);
    selectedCase[0] = -1;

    showIndex = 0;
    maxIndex = getMaxFromGrid(indexGrid);
    moves = initMoves();
    lastMoveIndex = -1;
    strcpy(errorsBuffer, "");

    // boucle du jeu
    while (*canShowGame) {
        // clearTerm();
        printf("Sudoku\n");
        printSudoku(sudokuGrid, indexGrid, showIndex, selectedCase);

        if (lastMoveIndex != -1) {
            printf("\nMoves\n");
            printMoves(moves, lastMoveIndex);
        }

        if (instruction == 1) {
            if (lastMoveIndex == -1) {
                printf("\n[1] Insérer une valeur\n[4] Quitter la partie\n");
            } else {
                printf("\n[1] Insérer une valeur\n[2] Retour au coup précédent\n[3] Retour au coup ...\n[4] Quitter la partie\n");
            }
            printf("%s\n: ", errorsBuffer);
            scanf("%d", &choice);
            getchar();
        } else if (instruction == 2) {
            printf("\n[0] Retour\n\n");
            printf("Taper le numéro de la case que vous souhaiter modifier\n");
            printf("%s\n: ", errorsBuffer);
            scanf("%d", &caseNum);
            getchar();

            if (caseNum < 0 || caseNum > maxIndex) {
                sprintf(errorsBuffer, "\nImposible de selectioner la case [%d]. \nVeuillez saisir une case valide.\n", caseNum);
            }

            else if (caseNum == 0) {
                instruction = 1;
                showIndex = 0;
                strcpy(errorsBuffer, "");
            }

            else if (caseNum > 0) {
                selectedCase = getValuePos(indexGrid, caseNum);
                checkAllocation(selectedCase);

                if (sudokuGrid[selectedCase[0]][selectedCase[1]] == EMPTY_CASE)  {
                    instruction = 3;
                    // choice = 10;
                    printf("Ok %d,%d\n", selectedCase[0], selectedCase[1]);
                }

                else {
                    sprintf(errorsBuffer, "\nLa case %d n'est pas vide (%d,%d)\n", caseNum, selectedCase[0], selectedCase[1]);
                }
            }
        } else if (instruction == 3) {
            printf("\n[0] Retour\n\n");
            printf("Saisir la valeur de la case [%d]\n", caseNum);
            printf("%s\n: ", errorsBuffer);
            scanf("%d", &caseValue);
            getchar();

            if (caseValue == 0) {
                instruction = 2;
                selectedCase[0] = -1;
            }
            else if (1 <= caseValue && caseValue <= 9) {
                sudokuGrid[selectedCase[0]][selectedCase[1]] = caseValue;

                if (countRowValue(sudokuGrid, selectedCase[0], caseValue) > 1 ||
                    countColValue(sudokuGrid, selectedCase[1], caseValue) > 1 ||
                    countBlockValue(sudokuGrid, getBlockIndice(selectedCase[0], selectedCase[1]), caseValue) > 1)
                {
                    sprintf(errorsBuffer, "\nImpossible de mettre la valeur %d dans la case %d car elle existe déjà,\nsoit dans la ligne, dans la colonne ou dans le block.\nVeuillez saisir une autre valeur.\n", caseValue, caseNum);
                    sudokuGrid[selectedCase[0]][selectedCase[1]] = 0;
                } else {
                    // add move
                    lastMoveIndex++;
                    updateMove(moves, lastMoveIndex, selectedCase[0], selectedCase[1], caseValue);

                    updateGridEmptyValueIndexFromGrid(indexGrid, sudokuGrid, SUDOKU_SIZE);
                    maxIndex = getMaxFromGrid(indexGrid);
                    selectedCase[0] = -1;
                    instruction = 1;
                    showIndex = 0;
                    strcpy(errorsBuffer, "");
                }
            } else {
                sprintf(errorsBuffer, "\nImpossible de mettre %d comme valeur.\nVeullez saisir une valeur entre 1 et 9.\n", caseValue);
            }
        } else if (instruction == 4) {
            printf("\n[0] Retour\n\n");
            printf("Êtes-vous sur de revenir au coup #%d\nSaisir o pour Oui ou n pour non.\n", lastMoveIndex + 1);
            printf("%s\n: ", errorsBuffer);
            scanf("%c", &previousMoveChoice);
            getchar();

            if (previousMoveChoice == '0') {
                instruction = 1;
            } else if (previousMoveChoice == 'o') {
                sudokuGrid[moves[lastMoveIndex][1]][moves[lastMoveIndex][2]] = 0;
                updateGridEmptyValueIndexFromGrid(indexGrid, sudokuGrid, SUDOKU_SIZE);
                moves[lastMoveIndex][0] = -1;
                lastMoveIndex--;
                selectedCase[0] = -1;
                instruction = 1;
            } else if (previousMoveChoice == 'n') {
                instruction = 1;
                selectedCase[0] = -1;
            } else {
                strcpy(errorsBuffer, "Saisie incorrecte.");
            }
        } else if (instruction == 5) {
            printf("[0] Retour\n\n");
            printf("Saisir l'indice du coup (%d à %d).\n", moves[0][0] + 1, lastMoveIndex + 1);
            printf("%s\n: ", errorsBuffer);
            scanf("%d", &returnMoveChoice);
            getchar();

            if (returnMoveChoice == 0) {
                instruction = 1;
            } else if (moves[0][0] <= returnMoveChoice - 1 && returnMoveChoice - 1 < lastMoveIndex) {
                while (lastMoveIndex != returnMoveChoice - 1) {
                    sudokuGrid[moves[lastMoveIndex][1]][moves[lastMoveIndex][2]] = 0;
                    moves[lastMoveIndex][0] = -1;
                    lastMoveIndex--;
                }

                updateGridEmptyValueIndexFromGrid(indexGrid, sudokuGrid, SUDOKU_SIZE);
                selectedCase[0] = -1;
                instruction = 1;
            } else {
                strcpy(errorsBuffer, "Saisie incorrecte.");
            }
        }

        if (choice == 1) {
            instruction = 2;
            showIndex = 1;
            selectedCase[0] = -1;
            choice = 10;
            strcpy(errorsBuffer, "");
        } else if (lastMoveIndex != -1) {
            if (choice == 2) {
                instruction = 4;
                // highlight last move
                selectedCase[0] = moves[lastMoveIndex][1];
                selectedCase[1] = moves[lastMoveIndex][2];
                choice = 10;
            } else if (choice == 3) {
                instruction = 5;
                choice = 10;
            }
        } else if (choice == 4) {
            *canShowGame = 0;

            // release the memory space
            if (sudokuGrid != NULL)
                freeMatrix(sudokuGrid, SUDOKU_SIZE);
            if (indexGrid != NULL)
                freeMatrix(indexGrid, SUDOKU_SIZE);
            if (moves != NULL)
                freeMatrix(moves, MAX_MOVE);
            if (selectedCase != NULL)
                free(selectedCase);
        } else if (choice == 10) {
            // redirection
        } else if (choice < 1 || choice != 10 || choice > 4) {
            strcpy(errorsBuffer, "Saisie incorrecte");
        }
    }
}


void checkAllocation(int *pointer) {
    if (pointer == NULL) {
        fprintf(stderr, "Allocation impossible\n");
        exit(EXIT_FAILURE);
    }
}
