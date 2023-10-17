#include "grid_utils.c"
#include "../types.h"

int ** createSudokuGrid(int value, int size);
int ** createSudokuGridFrom(t_grid grid, int size);
int *** createSudokuBlockGridFrom(t_grid startGrid, int size);

void printSudoku(int **grid, int showEmptyCase);
void freeSudokuGrid(int **grid, int size);

int countValue(int **grid, int value);
int countRowValue(int **grid, int rowIndex, int value);
int countColValue(int **grid, int colIndex, int value);