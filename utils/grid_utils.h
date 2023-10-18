#include "grid_utils.c"
#include "../types.h"

int ** createSudokuGrid(int value, int size);
int ** createSudokuGridFrom(t_grid grid, int size);
void freeSudokuGrid(int **grid, int size);

void printSudoku(int **grid, int **indexGrid, int showIndex, int *selectedCase);
void printCase(int value, int color);

int countValue(int **grid, int value);
int countRowValue(int **grid, int rowIndex, int value);
int countColValue(int **grid, int colIndex, int value);
int countBlockValue(int **grid, int blockIndex, int value);
int getBlockIndice(int rowIndex, int colIndex);
int getMaxFromGrid(int ** grid);
