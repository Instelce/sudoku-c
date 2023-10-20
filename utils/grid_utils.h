#include "grid_utils.c"
#include "../types.h"

int ** createSudokuGrid(int value, int size);
int ** createSudokuGridFrom(t_grid grid, int size);
void freeMatrix(int **matrix, int size);

void printCase(int value, int foregroundColor, int backgroundColor);
void printSudoku(int **grid, int **indexGrid, int showIndex, int *selectedCase);

int countValue(int **grid, int value);
int countRowValue(int **grid, int rowIndex, int value);
int countColValue(int **grid, int colIndex, int value);
int countBlockValue(int **grid, int blockIndex, int value);
int getBlockIndice(int rowIndex, int colIndex);
int getMaxFromGrid(int ** grid);

void updateGridEmptyValueIndexFromGrid(int **indexGrid, int **grid, int size);
