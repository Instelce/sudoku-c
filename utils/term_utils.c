#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "../types.h"


void setCursorPosition(int x, int y) {
    printf("\033[%d;%dH", y + 1, x + 1);
}


void getCursorPosition(int *x, int *y) {
    printf("\033[6n");
    scanf("\033[%d;%dR\r", x, y);
}


void printfColor(int foregroundColor, int backgroundColor, const char *format, ...) {
    char buffer[MAX_MSG_SIZE] = "";

    va_list args;

    va_start(args, format);
    vsnprintf(buffer, MAX_MSG_SIZE, format, args);
    va_end(args);

    if (backgroundColor == -1) {
        printf("\033[%dm%s\033[0m", foregroundColor, buffer);
    } else if (foregroundColor == -1) {
        printf("\033[%dm%s\033[0m", backgroundColor, buffer);
    } else {
        printf("\033[%d,%dm%s\033[0m", foregroundColor, backgroundColor, buffer);
    }
}


void clearTerm(void) {
    #ifdef _WIN32
    system("cls");
    #elif defined(__unix__) || defined(__APPLE__)
    system("clear");
    #endif
}
