#include "term_utils.c"


void setCursorPosition(int x, int y);
void getCursorPosition(int *x, int *y);
void printfColor(int foregroundColor, int backgroundColor, const char *format, ...);
void clearTerm(void);
