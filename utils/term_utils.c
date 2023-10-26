#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include "../types.h"


void setCursorPosition(int x, int y) {
    printf("\033[%d;%dH", y + 1, x + 1);
}


void getCursorPosition(int *x, int *y) {
    printf("\033[6n");
    scanf("\033[%d;%dR\r", x, y);
}


/**
 * @brief Custom printf for print with colors
 * 
 * @param foregroundColor 
 * @param backgroundColor 
 * @param format 
 * @param ... 
 */
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


/**
 * @brief Print error with style
 * 
 * @param buffer 
 */
void printError(char buffer[MAX_MSG_SIZE]) {
    if (!strcmp(buffer, "") == 0) {
        printfColor(RED_FG, -1, "\n%s\n\n", buffer);
    } else {
        printf("\n");
    }
}


/**
 * @brief 
 * 
 * @param seconds 
 */
void cooldown(int seconds)
{
    clock_t start = clock();
    clock_t period = seconds * CLOCKS_PER_SEC;
    clock_t elapsed;

    do {
        elapsed = clock() - start;
    } while(elapsed < period);
}


/**
 * @fn void printTypeEffect(char buffer[MAX_MSG_SIZE]) 
 * @brief 
 * 
 * @param buffer 
 */
void printTypeEffect(char buffer[MAX_MSG_SIZE]) {
    int bufferLenght = strlen(buffer);

    int i = 0;
    while (i < bufferLenght)
    {
        printf("%c", buffer[i]);
        cooldown(1);
        printf("%c", buffer[i]);

        i++;
    }
}


/**
 * @fn void clearTerm(void)
 * @brief Clear the terminal window
 * 
 */
void clearTerm(void) {
    #ifdef _WIN32
    system("cls");
    #elif defined(__unix__) || defined(__APPLE__)
    system("clear");
    #endif
}
