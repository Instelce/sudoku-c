#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void setCursorPosition(int x, int y);
void getCursorPosition(int *x, int *y);
void showMainMenu(int *canShowGame, int *loop);
void showGame(int *canShowGame);

int main() {
    int loop;
    int canShowGame;
    int choice;

    loop = 1;
    canShowGame = 0;
    choice = -1;

    while (loop) {
        showMainMenu(&canShowGame, &loop);
        showGame(&canShowGame);
    }

    return 0;
}

void showMainMenu(int *canShowGame, int *loop) {
    int choice;

    choice = -1;
    while (choice != 2 && *canShowGame == 0) {
        system("clear");
        printf("Sudoku\n[1] Nouvelle partie\n[2] Quitter\n: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
        case 1: *canShowGame = 1;
            break;
        case 2: *loop = 0;
            break;
        default:
            printf("\nSaisie incorrecte\n\n");
            break;
        }
    }
}

void showGame(int *canShowGame) {
    int choice;

    choice = -1;

    while (*canShowGame) {
        system("clear");
        printf("[1] Insérer une valeur\n[2] Retour au coup précédent\n[3] Retour au coup ...\n[4] Quitter la partie\n: ");
        scanf("%d", &choice);
        switch (choice) {
        case 4: *canShowGame = 0;
            break;
        default:
            printf("\nSaisie incorrecte\n");
            break;
        }
    }
}

void setCursorPosition(int x, int y)  {
    printf("\033[%d;%dH", y + 1, x + 1);
}

void getCursorPosition(int *x, int *y) {
    printf("\033[6n");
    scanf("\033[%d;%dR", x, y);
}