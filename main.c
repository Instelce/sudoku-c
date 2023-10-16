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
void printSudoku(t_sudoku_grid g, int showEmptyCase);
void printfColor(int color, const char *format, ...);


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
    t_sudoku_grid sudokuGrid = {
        {0,0,-1, 0,0,0, 0,0,0},
        {1,0,0, 0,0,-1, 0,0,1},
        {0,0,0, 0,0,0, 0,0,0},

        {0,0,0, 0,-1,0, 0,0,0},
        {0,0,0, -1,0,-1, 0,0,0},
        {0,0,0, 0,-1,0, 0,0,0},

        {0,0,0, 0,0,0, 0,0,0},
        {1,-1,0, 0,0,0, 0,0,1},
        {0,0,0, 0,0,0, 0,-1,0},
    };

    choice = -1;

    // boucle du jeu
    while (*canShowGame) {
        // system("clear");

        printf("Sudoku\n");

        // printSudoku(sudokuGrid);
        printSudoku(sudokuGrid, 1);

        printf("[1] Insérer une valeur\n[2] Retour au coup précédent\n[3] Retour au coup ...\n[4] Quitter la partie\n: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4: *canShowGame = 0;
                break;
            default:
                printf("\nSaisie incorrecte\n");
                break;
        }
    }
}


void oldPrintSudoku(t_sudoku_grid g) {
    int x;
    int y;
    int width = SUDOKU_SIZE + 1;
    int height = SUDOKU_SIZE + SUDOKU_SIZE;

    for (y = 0; y <= height; y++) {
        for (x = 0; x <= width; x++) {
            if (x == 0) {
                // left
                if (y == 0) {
                    printf("%s", TOPLEFT_CORNER_CHAR);
                } else if (y == height) {
                    printf("%s", BOTTOMLEFT_CORNER_CHAR);
                } else if (y % 2 == 0) {
                    printf("%s", VERTIVAL_HORIZONTAL_RIGHT_CHAR);
                } else {
                    printf("%s", VERTICAL_CHAR);
                }
            } else if (x == width) {
                // right corners
                if (y == 0) {
                    printf("%s", TOPRIGHT_CORNER_CHAR);
                } else if (y == height) {
                    printf("%s", BOTTOMRIGHT_CORNER_CHAR);
                } else if (y % 2 == 0) {
                    printf("%s", VERTIVAL_HORIZONTAL_LEFT_CHAR);
                } else {
                    printf("%s", VERTICAL_CHAR);
                }
            } else {
                // top and bottom ligne
                if (y == 0 && x < width -1) {
                    printf("%s%s%s%s%s%s", HORIZONTAL_CHAR, HORIZONTAL_CHAR, HORIZONTAL_CHAR, HORIZONTAL_CHAR, HORIZONTAL_CHAR, HORIZONTAL_VERTIVAL_DOWN_CHAR);
                }
                if (y == 0 && x > width - 2 && x < width) {
                    printf("%s%s%s%s%s", HORIZONTAL_CHAR, HORIZONTAL_CHAR, HORIZONTAL_CHAR, HORIZONTAL_CHAR, HORIZONTAL_CHAR);
                }
                if (y == height && x < width -1) {
                    printf("%s%s%s%s%s%s", HORIZONTAL_CHAR, HORIZONTAL_CHAR, HORIZONTAL_CHAR, HORIZONTAL_CHAR, HORIZONTAL_CHAR, HORIZONTAL_VERTIVAL_UP_CHAR);
                }
                if (y == height && x > width - 2 && x < width) {
                    printf("%s%s%s%s%s", HORIZONTAL_CHAR, HORIZONTAL_CHAR, HORIZONTAL_CHAR, HORIZONTAL_CHAR, HORIZONTAL_CHAR);
                }

                // ligne
                if (y % 2 == 0 && y > 0 && y < height && x < width - 1) {
                    printf("%s%s%s%s%s%s", HORIZONTAL_BOLD_CHAR, HORIZONTAL_BOLD_CHAR, HORIZONTAL_BOLD_CHAR, HORIZONTAL_BOLD_CHAR, HORIZONTAL_BOLD_CHAR, CROSS);
                }
                // end of ligne
                if (y % 2 == 0 && y > 0 && y < height && width - 2 < x && x < width) {
                    printf("%s%s%s%s%s", HORIZONTAL_BOLD_CHAR, HORIZONTAL_BOLD_CHAR, HORIZONTAL_BOLD_CHAR, HORIZONTAL_BOLD_CHAR, HORIZONTAL_BOLD_CHAR);
                }

                // ligne value
                if (y % 2 == 1 && y > 0 && y < height && x < width - 1) {
                    printf("  %d  %s", g[y][x], VERTICAL_BOLD_CHAR);
                }
                // end of ligne value
                if (y % 2 == 1 && y > 0 && y < height && x > width - 2 && x < width) {
                    printf("  %d  ", g[SUDOKU_SIZE - (y - SUDOKU_SIZE)][x - 1]);
                }
            }
        }
        printf("\n");
    }
}


void printSudoku(t_sudoku_grid g, int showEmptyCase) {
    int x;
    int y;
    int caseSize;
    caseSize = 6;

    for (y = 0; y < SUDOKU_SIZE + 1; y++) {
        // top and bottom left corner
        if (y == 0) {
            printf("%s", TOPLEFT_CORNER_CHAR);
        } else if (y == SUDOKU_SIZE) {
            printf("%s", BOTTOMLEFT_CORNER_CHAR);
        } else {
            printf("%s", VERTIVAL_HORIZONTAL_RIGHT_CHAR);
        }

        // horizontal lignes
        for (x = 0; x < SUDOKU_SIZE * caseSize - 1; x++) {
            if (x % caseSize == caseSize - 1 && y != 0 && y != SUDOKU_SIZE) {
                printf("%s", CROSS_BOLD);
            } else if (y % 3 == 0 && y != 0 && y != SUDOKU_SIZE) {
                printf("%s", HORIZONTAL_BOLD_CHAR);
            } else {
                printf("%s", HORIZONTAL_CHAR);
            }
        }

        // top and bottom right corner
        if (y == 0) {
            printf("%s", TOPRIGHT_CORNER_CHAR);
        } else if (y == SUDOKU_SIZE) {
            printf("%s", BOTTOMRIGHT_CORNER_CHAR);
        } else {
            printf("%s", VERTIVAL_HORIZONTAL_LEFT_CHAR);
        }

        if (y < SUDOKU_SIZE) {
            printf("\n%s", VERTICAL_CHAR);
        }

        for (x = 0; x < SUDOKU_SIZE; x++) {
            if (x % 3 == 2 && x < SUDOKU_SIZE - 1) {
                if (x < SUDOKU_SIZE && y < SUDOKU_SIZE && g[y][x] != -1) {
                    printf(" %d   %s", g[y][x], VERTICAL_BOLD_CHAR);
                } else if (y < SUDOKU_SIZE && g[y][x] == -1) {
                    if (showEmptyCase) {
                        printfColor(44, "  ?  ");
                        printf("%s", VERTICAL_BOLD_CHAR);
                        // printf("\033[31m  ?  \033[0m%s", VERTICAL_BOLD_CHAR);
                    } else {
                        printf("  !  %s", VERTICAL_BOLD_CHAR);
                    }
                }
            } else {
                if (x < SUDOKU_SIZE && y < SUDOKU_SIZE && g[y][x] != -1) {
                    printf(" %d   %s", g[y][x], VERTICAL_CHAR);
                } else if (y < SUDOKU_SIZE && g[y][x] == -1) {
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
