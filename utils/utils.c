
/**
 * @fn void freeMatrix(int **matrix, int size)
 * @brief Free memory that has been allocated by a matrix
 * 
 * @param matrix 
 * @param size 
 */
void freeMatrix(int **matrix, int size) {
    for (int i = 0; i < size; i++) {
        if (matrix[i] != NULL) {
            free(matrix[i]);
        }
    }
    free(matrix);
}


/**
 * @brief If pointer is null exit program
 * 
 * @param pointer 
 */
void checkAllocation(int *pointer) {
    if (pointer == NULL) {
        fprintf(stderr, "Allocation impossible\n");
        exit(EXIT_FAILURE);
    }
}
