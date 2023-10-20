#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main () {
    int startValue;
    int squareSize = 3;
    int fieldLenght = squareSize * squareSize;
    int a;

    srand(time(NULL));

    startValue = rand() % 9 + 1;
    a = startValue - 1;

    for (int blockCounter = 0; blockCounter < squareSize; blockCounter++)
    {
        for (int rowCounter = 0; rowCounter < squareSize; rowCounter++)
        {
            for (int colCounter = 0; colCounter < fieldLenght; colCounter++)
            {
                printf("%d\t", (a + 1));
                a = (a + 1) % fieldLenght;
            }
            printf("\n");
            a = (a + squareSize) % fieldLenght;
        }
        a = (a + 1) % fieldLenght;
    }

    return 0;
}