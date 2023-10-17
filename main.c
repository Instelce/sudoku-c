#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#define SUDOKU_SIZE 9

#define HORIZONTAL_BOLD_CHAR "\u2501"
#define HORIZONTAL_CHAR "\u2500"
#define VERTICAL_BOLD_CHAR "\u2503"
#define VERTICAL_CHAR "\u2502"

#define TOPLEFT_CORNER_CHAR "\u256D"
#define TOPRIGHT_CORNER_CHAR "\u256E"
#define BOTTOMLEFT_CORNER_CHAR "\u2570"
#define BOTTOMRIGHT_CORNER_CHAR "\u256F"

#define HORIZONTAL_VERTIVAL_DOWN_CHAR "\u2530"
#define HORIZONTAL_VERTIVAL_UP_CHAR "\u2538"

#define VERTIVAL_HORIZONTAL_RIGHT_CHAR "\u251D"
#define VERTIVAL_HORIZONTAL_LEFT_CHAR "\u2525"

#define CROSS "\u253C"
#define CROSS_BOLD "\u254B"

#define MAX_MSG_SIZE 100

#define BLUE_FG 44
#define BLUE_FG 44

typedef int t_sudoku_grid[SUDOKU_SIZE][SUDOKU_SIZE];


void setCursorPosition(int x, int y);
void getCursorPosition(int *x, int *y);
void showMainMenu(int *canShowGame, int *loop);
void showGame(int *canShowGame);
void printSudoku(int **grid, int showEmptyCase);
void printfColor(int color, const char *format, ...);
void ** createSudokuGrid(int **grid);


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
    char instructionBuffer[100];
    char errorsBuffer[100];
    int caseNum;
    int caseValue;

    // t_sudoku_grid sudokuGrid = {
    //     {0,0,-1, 0,0,0, 0,0,0},
    //     {1,0,0, 0,0,-1, 0,0,1},
    //     {0,0,0, 0,0,0, 0,0,0},

    //     {0,0,0, 0,-1,0, 0,0,0},
    //     {0,0,0, -1,0,-1, 0,0,0},
    //     {0,0,0, 0,-1,0, 0,0,0},

    //     {0,0,0, 0,0,0, 0,0,0},
    //     {1,-1,0, 0,0,0, 0,0,1},
    //     {0,0,0, 0,0,0, 0,-1,0},
    // };

    int **sudokuGrid;
    sudokuGrid = createSudokuGrid(sudokuGrid);
    // initSudokuGrid(sudokuGrid);

    choice = -1;
    strcpy(errorsBuffer, "");

    // boucle du jeu
    while (*canShowGame) {
        // system("clear");

        printf("Sudoku\n");
        printSudoku(sudokuGrid, 1);

        printf("[1] Insérer une valeur\n[2] Retour au coup précédent\n[3] Retour au coup ...\n[4] Quitter la partie\n");
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
}


void printSudoku(int **grid, int showEmptyCase) {
    int row;
    int col;
    int caseSize;
    caseSize = 6;

    for (row = 0; row < SUDOKU_SIZE + 1; row++) {
        // top and bottom left corner
        if (row == 0) {
            printf("%s", TOPLEFT_CORNER_CHAR);
        } else if (row == SUDOKU_SIZE) {
            printf("%s", BOTTOMLEFT_CORNER_CHAR);
        } else {
            printf("%s", VERTIVAL_HORIZONTAL_RIGHT_CHAR);
        }

        // horizontal lignes
        for (col = 0; col < SUDOKU_SIZE * caseSize - 1; col++) {
            if (col % caseSize == caseSize - 1 && row != 0 && row != SUDOKU_SIZE) {
                printf("%s", CROSS_BOLD);
            } else if (row % 3 == 0 && row != 0 && row != SUDOKU_SIZE) {
                printf("%s", HORIZONTAL_BOLD_CHAR);
            } else {
                printf("%s", HORIZONTAL_CHAR);
            }
        }

        // top and bottom right corner
        if (row == 0) {
            printf("%s", TOPRIGHT_CORNER_CHAR);
        } else if (row == SUDOKU_SIZE) {
            printf("%s", BOTTOMRIGHT_CORNER_CHAR);
        } else {
            printf("%s", VERTIVAL_HORIZONTAL_LEFT_CHAR);
        }

        if (row < SUDOKU_SIZE) {
            printf("\n%s", VERTICAL_CHAR);
        }

        for (col = 0; col < SUDOKU_SIZE; col++) {
            if (col % 3 == 2 && col < SUDOKU_SIZE - 1) {
                if (col < SUDOKU_SIZE && row < SUDOKU_SIZE && grid[row][col] != -1) {
                    printf(" %d   %s", grid[row][col], VERTICAL_BOLD_CHAR);
                } else if (row < SUDOKU_SIZE && grid[row][col] == -1) {
                    if (showEmptyCase) {
                        printfColor(44, "  ?  ");
                        printf("%s", VERTICAL_BOLD_CHAR);
                        // printf("\033[31m  ?  \033[0m%s", VERTICAL_BOLD_CHAR);
                    } else {
                        printf("  !  %s", VERTICAL_BOLD_CHAR);
                    }
                }
            } else {
                if (col < SUDOKU_SIZE && row < SUDOKU_SIZE && grid[row][col] != -1) {
                    printf(" %d   %s", grid[row][col], VERTICAL_CHAR);
                } else if (row < SUDOKU_SIZE && grid[row][col] == -1) {
                    if (showEmptyCase) {
                        printfColor(44, "  ?  ");
                        printf("%s", VERTICAL_CHAR);
                        // printf("\033[31m  ?  \033[0m%s", VERTICAL_CHAR);
                    } else {
                        printf("  !  %s", VERTICAL_CHAR);
                    }
                }
            }
        }
        printf("\n");
    }
}


void ** createSudokuGrid(int **grid) {
    grid = (int **) malloc(sizeof(int *) * SUDOKU_SIZE);

    for (int i = 0; i < SUDOKU_SIZE; i++) {
        grid[i] = (int *) malloc(sizeof(int) * 3);
    }

    grid[0][0] = 5;

    return grid;
}

void initSudokuGrid(int **grid) {
    for (int i = 0; i < SUDOKU_SIZE; i++) {
        for (int j = 0; j < SUDOKU_SIZE; j++) {
            grid[i][j] = 0;
        }
    }
}


void freeSudokuGrid(int **grid, int size) {
    for (int i = 0; i < size; i++) {
        free(grid[i]);
    }
    free(grid);
}


void setCursorPosition(int x, int y) {
    printf("\033[%d;%dH", y + 1, x + 1);
}


void getCursorPosition(int *x, int *y) {
    printf("\033[6n");
    scanf("\033[%d;%dR", x, y);
}


void printfColor(int color, const char *format, ...) {
    char buffer[MAX_MSG_SIZE] = "";

    va_list args;

    va_start(args, format);
    vsnprintf(buffer, MAX_MSG_SIZE, format, args);
    va_end(args);

    printf("\033[%dm%s\033[0m", color, buffer);
}


void clearTerm(void) {
    #ifdef _WIN32
    system("cls");
    #elif defined(__unix__) || defined(__APPLE__)
    system("clear");
    #endif
}


void countEmpyCase(t_sudoku_grid g) {
    
}