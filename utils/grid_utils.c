#include <stdio.h>
#include <stdlib.h>
#include "../types.h"


int ** createSudokuGrid(int caseValue, int size) {
    int ** grid = (int **) malloc(sizeof(int *) * size);

    for (int row = 0; row < size; row++) {
	    grid[row] = (int *) malloc(sizeof(int) * size);
    }

    // initialized value
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            grid[row][col] = caseValue;
        }
    }

    return grid;
}


int ** createSudokuGridFrom(t_grid startGrid, int size) {
    int **grid = (int **) malloc(sizeof(int *) * size);

    // allocate
    for (int row = 0; row < size; row++) {
	    grid[row] = (int *) malloc(sizeof(int) * size);
    }

    // initialized value
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            grid[row][col] = startGrid[row][col];
        }
    }

    return grid;
}


int *** createSudokuBlockGridFrom(t_grid startGrid, int size) {
    int ***grid = (int ***) malloc(sizeof(int **) * size);
    int blockLine = 0;
    int v = 0;
    int irow;
    int icol;

    // allocate
    for (int blockIndex = 0; blockIndex < size; blockIndex++) {
	    grid[blockIndex] = (int **) malloc(sizeof(int *) * 3);
    }
    for (int blockIndex = 0; blockIndex < size; blockIndex++) {
        for (int row = 0; row < 3; row++) {
            grid[blockIndex][row] = (int *) malloc(sizeof(int) * 3);
        }
    }

    // initialized value
    for (int blockIndex = 0; blockIndex < size; blockIndex++) 
    {
        for (int row = 0; row < 3; row++) 
        {
            for (int col = 0; col < 3; col++) 
            {
                irow = row + blockLine * 3;
                icol = col + v;

                grid[blockIndex][row][col] = startGrid[irow][icol];

            }
        }
        v+=3;
        if (blockIndex % 3 == 2 && blockIndex != 0) {
            blockLine++;
            v = 0;
        }
    }

    return grid;
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
                if (col < SUDOKU_SIZE && row < SUDOKU_SIZE && grid[row][col] != EMPTY_CASE) {
                    printf(" %d   %s", grid[row][col], VERTICAL_BOLD_CHAR);
                } else if (row < SUDOKU_SIZE && grid[row][col] == EMPTY_CASE) {
                    if (showEmptyCase) {
                        printfColor(44, "  ?  ");
                        printf("%s", VERTICAL_BOLD_CHAR);
                    } else {
                        printfColor(36, "  ?  ");
                        printf("%s", VERTICAL_BOLD_CHAR);
                    }
                }
            } else {
                if (col < SUDOKU_SIZE && row < SUDOKU_SIZE && grid[row][col] != EMPTY_CASE) {
                    printf(" %d   %s", grid[row][col], VERTICAL_CHAR);
                } else if (row < SUDOKU_SIZE && grid[row][col] == EMPTY_CASE) {
                    if (showEmptyCase) {
                        printfColor(44, "  ?  ");
                        printf("%s", VERTICAL_CHAR);
                    } else {
                        printfColor(36, "  ?  ");
                        printf("%s", VERTICAL_CHAR);
                    }
                }
            }
        }
        printf("\n");
    }
}


void freeSudokuGrid(int **grid, int size) {
    for (int i = 0; i < size; i++) {
        free(grid[i]);
    }
    free(grid);
}


void freeSudokuBlockGrid(int ***grid, int size) {
    for (int blockIndex = 0; blockIndex < size; blockIndex++) {
        for (int row = 0; row < 3; row++) {
            free(grid[blockIndex][row]);
        }
        free(grid[blockIndex]);
    }
    free(grid);
}


int countValue(int **grid, int value) {
    int count = 0;
    int size;

    for (int row = 0; row < SUDOKU_SIZE; row++) {
        for (int col = 0; col < SUDOKU_SIZE; col++) {
            if (grid[row][col] == value) {
                count++;
            }
        }
    }

    return count;
}


int countRowValue(int **grid, int rowIndex, int value) {
    int count = 0;
    int size;

    for (int col = 0; col < SUDOKU_SIZE; col++) {
        if (grid[rowIndex][col] == value) {
            count++;
        }
    }

    return count;
}


int countColValue(int **grid, int colIndex, int value) {
    int count = 0;
    int size;

    for (int row = 0; row < SUDOKU_SIZE; row++) {
        if (grid[row][colIndex] == value) {
            count++;
        }
    }

    return count;
}


int countBlockValue(int ***grid, int blockIndex, int value) {
    int count = 0;

    for (int row = 0; row < 3; row++) 
    {
        for (int col = 0; col < 3; col++) 
        {
            if (grid[blockIndex][row][col] == value) {
                count++;
            }
        }
    }

    return count;
}


int getBlockIndice(int ***grid, int rowIndex, int colIndex) {
    int irow = 0;
    int icol = 0;

    for (int blockIndex = 0; blockIndex < SUDOKU_SIZE; blockIndex++) 
    {
        
    }
}