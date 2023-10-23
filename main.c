#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "utils/utils.h"
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
        {1,0,0, 4,0,9, 0,0,5},
        {0,0,0, 0,8,0, 0,7,9},
};


void showMainMenu(int *canShowGame, int *loop);
void showGame(int *canShowGame);


int main() {
    int loop;
    int canShowGame;

    // initialize variable
    loop = 1;
    canShowGame = 1;

    // menus loop
    while (loop) {
        showMainMenu(&canShowGame, &loop);
        showGame(&canShowGame);
    }

    return 0;
}


void showMainMenu(int *canShowGame, int *loop) {
    int choice;

    choice = -1;

    // main menu loop
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

    // variable declaration
    int choice;
    int instruction;
    char previousMoveChoice;
    int returnMoveChoice;
    int cursorPosY;
    int cursorPosX;

    char errorsBuffer[300];

    int caseNum;
    int caseValue;
    int maxIndex;

    int *selectedCase;
    int errorValue;

    int showIndex;

    int **sudokuGrid;
    int **indexGrid;

    int **moves;
    int lastMoveIndex;

    // variable initialization
    sudokuGrid = createSudokuGridFrom(originalSudokuGrid);
    indexGrid = createSudokuGrid(0);
    updateGridEmptyValueIndexFromGrid(indexGrid, sudokuGrid);

    choice = -1;
    instruction = 1;

    selectedCase = getValuePos(indexGrid, caseNum);
    checkAllocation(selectedCase);
    selectedCase[0] = -1;
    errorValue = -1;

    showIndex = 0;
    maxIndex = getMaxFromGrid(indexGrid);
    moves = initMoves();
    lastMoveIndex = -1;
    strcpy(errorsBuffer, "");

    // check some function
    // printf("Check function\n");
    // printf("Value %d\n", countValue(sudokuGrid, 5));
    // printf("Row value %d\n", countRowValue(sudokuGrid, 0, 5));
    // printf("Col value %d\n", countColValue(sudokuGrid, 5, 5));
    // printf("Block value %d\n", countBlockValue(sudokuGrid, 3, 8));
    // printf("Block indice %d\n\n", getBlockIndice(3, 8));

    // sudoku loop
    while (*canShowGame) {

        // print sudoku grid
        // clearTerm();
        printf("Sudoku\n");
        printSudoku(sudokuGrid, indexGrid, showIndex, errorValue, selectedCase);

        // print moves
        if (lastMoveIndex != -1) {
            printf("\nMoves\n");
            printMoves(moves, lastMoveIndex);
        }

        /*
            List of instruction
            1 - Main menu
            2 - Entering the case number
            3 - Entering the case value
            4 - Back to the previous move
            5 - Back to a precise move
        */

        // Main menu
        if (instruction == 1) {
            if (lastMoveIndex == -1) {
                printf("\n[1] Insérer une valeur\n[4] Quitter la partie\n");
            } else {
                printf("\n[1] Insérer une valeur\n[2] Retour au coup précédent\n[3] Retour au coup ...\n[4] Quitter la partie\n");
            }
            printError(errorsBuffer);
            printf(": ");
            scanf("%d", &choice);
            getchar();
        }
        // Entering the case number
        else if (instruction == 2) {
            printf("\n[0] Retour\n\n");
            printf("Taper le numéro de la case que vous souhaiter modifier\n");
            printError(errorsBuffer);
            printf(": ");
            scanf("%d", &caseNum);
            getchar();

            // the case doesn't exist
            if (caseNum < 0 || caseNum > maxIndex) {
                sprintf(errorsBuffer, "Imposible de selectioner la case [%d]. \nVeuillez saisir une case valide.", caseNum);
            }
            // back to instruction 1
            else if (caseNum == 0) {
                instruction = 1;
                showIndex = 0;
                strcpy(errorsBuffer, "");
            }
            // valid case number
            else if (caseNum > 0) {
                selectedCase = getValuePos(indexGrid, caseNum);
                checkAllocation(selectedCase);

                // check if case is empty
                if (sudokuGrid[selectedCase[0]][selectedCase[1]] == EMPTY_CASE)  {
                    instruction = 3;
                    showIndex = 0;
                    strcpy(errorsBuffer, "");
                } else {
                    sprintf(errorsBuffer, "La case %d n'est pas vide (%d,%d)", caseNum, selectedCase[0], selectedCase[1]);
                }
            }
        }
        // Entering the case value
        else if (instruction == 3) {
            printf("\n[0] Retour\n\n");
            printf("Saisir la valeur de la case [%d]\n", caseNum);
            printError(errorsBuffer);
            printf(": ");
            scanf("%d", &caseValue);
            getchar();

            // back to instruction 2
            if (caseValue == 0) {
                instruction = 2;
                selectedCase[0] = -1;
                errorValue = -1;
                showIndex = 1;
                strcpy(errorsBuffer, "");
            }
            // valid value
            else if (1 <= caseValue && caseValue <= SUDOKU_SIZE) {
                sudokuGrid[selectedCase[0]][selectedCase[1]] = caseValue;

                // check if the value is unique in the row, column and block
                if (countRowValue(sudokuGrid, selectedCase[0], caseValue) > 1 ||
                    countColValue(sudokuGrid, selectedCase[1], caseValue) > 1 ||
                    countBlockValue(sudokuGrid, getBlockIndice(selectedCase[0], selectedCase[1]), caseValue) > 1)
                {
                    sprintf(errorsBuffer, "Impossible de mettre la valeur %d dans la case %d car elle existe déjà,\nsoit dans la ligne, dans la colonne ou dans le block.\nVeuillez saisir une autre valeur.", caseValue, caseNum);
                    errorValue = sudokuGrid[selectedCase[0]][selectedCase[1]];
                    sudokuGrid[selectedCase[0]][selectedCase[1]] = 0;
                } else {
                    // add move
                    lastMoveIndex++;
                    updateMove(moves, lastMoveIndex, selectedCase[0], selectedCase[1], caseValue);

                    updateGridEmptyValueIndexFromGrid(indexGrid, sudokuGrid);
                    maxIndex = getMaxFromGrid(indexGrid);

                    selectedCase[0] = -1;
                    errorValue = -1;
                    instruction = 1;
                    showIndex = 0;
                    strcpy(errorsBuffer, "");
                }
            }
            // error the value isn't between 1 and 9
            else {
                sprintf(errorsBuffer, "Impossible de mettre %d comme valeur.\nVeullez saisir une valeur entre 1 et 9.", caseValue);
            }
        }
        // Back to the previous move
        else if (instruction == 4) {
            printf("\nÊtes-vous sur de revenir au coup #%d\nSaisir o pour Oui ou n pour non.\n", lastMoveIndex + 1);
            printError(errorsBuffer);
            printf(": ");
            scanf("%c", &previousMoveChoice);
            getchar();

            // remove the last move
            if (previousMoveChoice == 'o') {
                sudokuGrid[moves[lastMoveIndex][1]][moves[lastMoveIndex][2]] = 0;
                updateGridEmptyValueIndexFromGrid(indexGrid, sudokuGrid);
                moves[lastMoveIndex][0] = -1;
                lastMoveIndex--;
                selectedCase[0] = -1;
                instruction = 1;
            }
            // return to instruction 1
            else if (previousMoveChoice == 'n') {
                instruction = 1;
                selectedCase[0] = -1;
            }
            // input error
            else {
                strcpy(errorsBuffer, "Saisie incorrecte.");
            }
        }
        // Back to a precise move
        else if (instruction == 5) {
            printf("\n[0] Retour\n\n");
            printf("Saisir l'indice du coup (%d à %d).\n", moves[0][0] + 1, lastMoveIndex + 1);
            printError(errorsBuffer);
            printf(": ");
            scanf("%d", &returnMoveChoice);
            getchar();

            // back to instruction 1
            if (returnMoveChoice == 0) {
                instruction = 1;
            }
            // remove all moves to select move
            else if (moves[0][0] <= returnMoveChoice - 1 && returnMoveChoice - 1 < lastMoveIndex) {
                while (lastMoveIndex != returnMoveChoice - 1) {
                    sudokuGrid[moves[lastMoveIndex][1]][moves[lastMoveIndex][2]] = 0;
                    moves[lastMoveIndex][0] = -1;
                    lastMoveIndex--;
                }

                updateGridEmptyValueIndexFromGrid(indexGrid, sudokuGrid);
                selectedCase[0] = -1;
                instruction = 1;
            }
            // input error
            else {
                strcpy(errorsBuffer, "Saisie incorrecte.");
            }
        }

        // with choice set variables for custom sudoku print 
        // and redirect to instruction
        if (choice == 1) {
            instruction = 2;
            showIndex = 1;
            selectedCase[0] = -1;
            choice = 100;
            strcpy(errorsBuffer, "");
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
        } else if (lastMoveIndex != -1) {
            if (choice == 2) {
                instruction = 4;
                // highlight last move
                selectedCase[0] = moves[lastMoveIndex][1];
                selectedCase[1] = moves[lastMoveIndex][2];
                choice = 100;
                strcpy(errorsBuffer, "");
            } else if (choice == 3) {
                instruction = 5;
                choice = 100;
                strcpy(errorsBuffer, "");
            }
        } else if (choice == 100) {
            // redirection
        } else if (choice < 1 || choice != 100 || choice > 4) {
            strcpy(errorsBuffer, "Saisie incorrecte.\nVeuillez saisir un nombre correspondant à une action.");
        }
    }
}


