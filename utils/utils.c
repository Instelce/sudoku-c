


void checkAllocation(int *pointer) {
    if (pointer == NULL) {
        fprintf(stderr, "Allocation impossible\n");
        exit(EXIT_FAILURE);
    }
}
