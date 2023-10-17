#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "../types.h"


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
