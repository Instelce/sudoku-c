#include <stdio.h>
#include <stdlib.h>
#include "../types.h"
#include "math.h"

/**
 * @brief Create a Sudoku Grid object
 * 
 * @param caseValue 
 * @return int** 
 */
int ** createSudokuGrid(int caseValue) {
    int ** grid = (int **) malloc(sizeof(int *) * SUDOKU_SIZE);
    checkAllocation(grid);

    // allocate
    for (int row = 0; row < SUDOKU_SIZE; row++) {
	    grid[row] = (int *) malloc(sizeof(int) * SUDOKU_SIZE);
        checkAllocation(grid[row]);
    }

    // initialized value
    for (int row = 0; row < SUDOKU_SIZE; row++) {
        for (int col = 0; col < SUDOKU_SIZE; col++) {
            grid[row][col] = caseValue;
        }
    }

    return grid;
}

/**
 * @brief Create a Sudoku Grid From object
 * 
 * @param startGrid 
 * @return int** 
 */
int ** createSudokuGridFrom(t_grille startGrid) {
    int **grid = (int **) malloc(sizeof(int *) * SUDOKU_SIZE);
    checkAllocation(grid);

    // allocate
    for (int row = 0; row < SUDOKU_SIZE; row++) {
	    grid[row] = (int *) malloc(sizeof(int) * SUDOKU_SIZE);
        checkAllocation(grid[row]);
    }

    // initialized value
    for (int row = 0; row < SUDOKU_SIZE; row++) {
        for (int col = 0; col < SUDOKU_SIZE; col++) {
            grid[row][col] = startGrid[row][col];
        }
    }

    return grid;
}


/**
 * @fn void updateGridEmptyValueIndexFromGrid(int **indexGrid, int **grid)
 * @brief Updating a grid containing the indexes of empty cells in another grid
 * 
 * @param indexGrid 
 * @param grid 
 */
void updateGridEmptyValueIndexFromGrid(int **indexGrid, int **grid) {
    int index = 0;

    for (int row = 0; row < SUDOKU_SIZE; row++) {
        for (int col = 0; col < SUDOKU_SIZE; col++) {
            if (grid[row][col] == EMPTY_CASE) {
                index++;
                indexGrid[row][col] = index;
            } else {
                indexGrid[row][col] = 0;
            }
        }
    }
}


/**
 * @brief 
 * 
 * @param value 
 * @param foregroundColor 
 * @param backgroundColor 
 */
void printCase(int value, int foregroundColor, int backgroundColor) {
    if (foregroundColor == -1 && backgroundColor == -1) {
        if (value == -1) {
            printf("  ?  %s", VERTICAL_CHAR);
        } else {
            if (value > 9) {
                printf(" %d  %s", value, VERTICAL_CHAR);
            } else {
                printf("  %d  %s", value, VERTICAL_CHAR);
            }
        }
    } else {
        if (value == -1) {
            printfColor(foregroundColor, backgroundColor, "  ?  ");
            printf("%s", VERTICAL_CHAR);
        } else {
            if (value > 9) {
                printfColor(foregroundColor, backgroundColor, " %d  ", value);
                printf("%s", VERTICAL_CHAR);
            } else {
                printfColor(foregroundColor, backgroundColor, "  %d  ", value);
                printf("%s", VERTICAL_CHAR);
            }
        }
    }
}


/**
 * @brief 
 * 
 * @param grid 
 * @param indexGrid 
 * @param showIndex 
 * @param errorValue 
 * @param selectedCase 
 */
void printSudoku(int **grid, int **indexGrid, int showIndex, int errorValue, int *selectedCase) {
    int row;
    int col;
    int caseSize;
    int caseValue;

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
            if (col % caseSize == caseSize - 1 && row == 0) {
                printf("%s", HORIZONTAL_VERTIVAL_DOWN_CHAR);
            } else if (col % caseSize == caseSize - 1 && row == SUDOKU_SIZE) {
                printf("%s", HORIZONTAL_VERTIVAL_UP_CHAR);
            } else if (row != 0 && row != SUDOKU_SIZE && col % caseSize == caseSize - 1) {
                if (row % 3 == 0)
                    printf("%s", CROSS_BOLD);
                else
                    printf("%s", CROSS);
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

        // new line with value
        if (row < SUDOKU_SIZE) {
            printf("\n%s", VERTICAL_CHAR);
        }

        for (col = 0; col < SUDOKU_SIZE; col++) {
            if (col < SUDOKU_SIZE && row < SUDOKU_SIZE) {
                caseValue = grid[row][col];

                // fill cases
                if (caseValue != EMPTY_CASE) {
                    // show selected case if it exists
                    if (selectedCase[0] != -1 &&
                        grid[selectedCase[0]][selectedCase[1]] != EMPTY_CASE &&
                        row == selectedCase[0] &&
                        col == selectedCase[1]) {
                        printCase(caseValue, -1, YELLOW_BG);
                    } 
                    // shows the cases that generated the error
                    else if (
                        errorValue == caseValue &&
                        (row == selectedCase[0] ||
                        col == selectedCase[1] ||
                        getBlockIndice(row, col) == getBlockIndice(selectedCase[0], selectedCase[1]))) {
                        printCase(caseValue, RED_FG, -1);
                    } 
                    // show fill case
                    else {
                        printCase(caseValue, -1, -1);
                    }
                }

                // empty cases
                else if (caseValue == EMPTY_CASE) {
                    // show selected case if it exists
                    if (selectedCase[0] != -1 &&
                        grid[selectedCase[0]][selectedCase[1]] == EMPTY_CASE &&
                        row == selectedCase[0] &&
                        col == selectedCase[1]) {
                        printCase(-1, -1, YELLOW_BG);
                    } 
                    // show index cases
                    else if (showIndex) {
                        printCase(indexGrid[row][col], -1, BLUE_BG);
                    // show empty case
                    } else {
                        printCase(-1, GREEN_FG, -1);
                    }
                }
            }
        }

        printf("\n");
    }
}


// Count functions

/**
 * @fn int countValue(int **grid, int value)
 * @brief 
 * 
 * @param grid 
 * @param value 
 * @return int 
 */
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


/**
 * @fn int countRowValue(int **grid, int rowIndex, int value)
 * @brief 
 * 
 * @param grid 
 * @param rowIndex 
 * @param value 
 * @return int 
 */
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


/**
 * @fn int countColValue(int **grid, int colIndex, int value)
 * @brief 
 * 
 * @param grid 
 * @param colIndex 
 * @param value 
 * @return int 
 */
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


/**
 * @fn int countBlockValue(int **grid, int blockIndex, int value)
 * @brief 
 * 
 * @param grid 
 * @param blockIndex 
 * @param value 
 * @return int 
 */
int countBlockValue(int **grid, int blockIndex, int value) {
    int count = 0;
    int blockLine = 0;
    int blockInlineStart = 0;
    int irow;
    int icol;

    for (int bIndex = 0; bIndex < SUDOKU_SIZE; bIndex++) 
    {
        for (int row = 0; row < 3; row++) 
        {
            for (int col = 0; col < 3; col++) 
            {
                irow = row + blockLine * 3;
                icol = col + blockInlineStart;
                if (grid[irow][icol] == value && bIndex == blockIndex) {
                    count++;
                }
            }
        }
        blockInlineStart+=3;

        // new "line"
        if (bIndex % 3 == 2 && bIndex != 0) {
            blockLine++;
            blockInlineStart = 0;
        }
    }

    return count;
}


/**
 * @fn int getBlockIndice(int rowIndex, int colIndex)
 * @brief Get the Block Indice from row and col index
 * 
 * @param rowIndex 
 * @param colIndex 
 * @return int 
 */
int getBlockIndice(int rowIndex, int colIndex) {
    int irow = 0;
    int icol = 0;
    int blockLine = 0;
    int blockInlineStart = 0;

    for (int blockIndex = 0; blockIndex < SUDOKU_SIZE; blockIndex++) {
        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 3; col++) {
                irow = row + blockLine * 3;
                icol = col + blockInlineStart;

                if (irow == rowIndex && icol == colIndex) {
                    return blockIndex;
                }
            }
        }

        blockInlineStart+=3;

        // new "line"
        if (blockIndex % 3 == 2 && blockIndex != 0) {
            blockLine++;
            blockInlineStart = 0;
        }
    }

    return 0;
}


/**
 * @fn int * getValuePos(int **grid, int value)
 * @brief Get the Value Pos of value in grid
 * 
 * @param grid 
 * @param value
 * @return int* 
 */
int * getValuePos(int **grid, int value) {
    int *pos = (int *) malloc(sizeof(int) * 2);

    for (int row = 0; row < SUDOKU_SIZE; row++) {
        for (int col = 0; col < SUDOKU_SIZE; col++) {
            if (grid[row][col] == value) {
                pos[0] = row;
                pos[1] = col;
                return pos;
            }
        }
    }

    pos[0] = -1;
    return pos;
}


/**
 * @fn int getMaxOfGrid(int ** grid)
 * @brief Get the max value of a grid
 * 
 * @param grid 
 * @return int 
 */
int getMaxOfGrid(int ** grid) {
    int max;

    max = (int) -INFINITY;
     for (int row = 0; row < SUDOKU_SIZE; row++) {
        for (int col = 0; col < SUDOKU_SIZE; col++) {
            if (grid[row][col] > max) {
                max = grid[row][col];
            }
        }
    }

    return max;
}
