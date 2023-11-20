/**
 * @file sudoku.c
 * @author Célestin Besson
 * @brief Fichier principal du jeu
 * @version 1
 * @date 2023-10-25 to...
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>

// -------------------------------------------------------------------------
// Constantes
// -------------------------------------------------------------------------

#define TAILLE 9
#define CASE_VIDE 0

#define MAX_MSG_SIZE 500
#define MAX_SAISIE_SIZE 500

// Couleurs
#define BLUE_BG 44
#define BLUE_FG 34
#define YELLOW_BG 43
#define YELLOW_FG 33
#define GREEN_FG 32
#define RED_FG 31
#define FLASH_TEXT 5
#define WHITE_BG 37
#define WHITE_FG 47
#define BLACK_BG 40
#define BLACK_FG 30


// -------------------------------------------------------------------------
// Types
// -------------------------------------------------------------------------

typedef int t_grille[TAILLE][TAILLE];


// -------------------------------------------------------------------------
// Déclarations des fonctions
//-------------------------------------------------------------------------

void chargerGrille(t_grille grille);
void afficherGrille(t_grille grille);
void saisir(int *var);
bool possible(t_grille grille, int numLigne, int numColonne, int valeur);
bool grilleRempli(t_grille t_grille);


int main()
{
    t_grille grilleSudoku;
    int numLigne, numColonne, valeur;
    bool est_possible;

    chargerGrille(grilleSudoku);

    while (!grilleRempli(grilleSudoku))
    {
        afficherGrille(grilleSudoku);

        printf("Saisir le numéro de la ligne");
        saisir(&numLigne);
        printf("Ok %d\n\n", numLigne);
        numLigne--;

        printf("Saisir le numéro de la colonne");
        saisir(&numColonne);
        printf("Ok %d\n\n", numColonne);
        numColonne--;

        if (grilleSudoku[numLigne][numColonne] == CASE_VIDE) {
            printf("Saisir la valeur de la case %d:%d", numLigne + 1, numColonne + 1);
            saisir(&valeur);

            est_possible = possible(grilleSudoku, numLigne, numColonne, valeur);
            printf("%s", est_possible == 1 ? "Ok pas de problème" : "Pas possible, la valeur existe déjà soit dans la ligne, la colonne ou le block.");
        } else {
            printf("La case n'est pas vide.\n");
        }
    }

    printf("Bravo, tu es fini la grille\n");
}


// -------------------------------------------------------------------------
// Fonctions lier à la grille
// -------------------------------------------------------------------------

/**
 * @fn void chargerGrille(t_grille grille)
 * @brief Charge les valeurs d'un grille a partir d'un nom de fichier
 * 
 * @param grille 
 */
void chargerGrille(t_grille grille)
{
    char nomFichier[30];
    char cheminFichier[100];
    FILE *f;

    printf("Nom du fichier ? ");
    scanf("%s", nomFichier);

    // sprintf(nomFichier, "Grille1");

    sprintf(cheminFichier, "./grilles/%s.sud", nomFichier);


    f = fopen(cheminFichier, "rb");

    if (f == NULL)
    {
        printf("\n ERREUR sur le fichier %s\n", nomFichier);
    }
    else
    {
        fread(grille, sizeof(int), TAILLE * TAILLE, f);
    }
    fclose(f);
}

/**
 * @brief Affichage customiser de la grille
 * 
 * @param grille 
 */
void afficherGrille(t_grille grille) {
    int caseValeur;

    for (int ligne = 0; ligne < TAILLE; ligne++) {
        if (ligne == 0) {
            printf("   ");
            for (int colonne = 0; colonne < TAILLE; colonne++) {
                printf(" %d ", colonne + 1);
                if (colonne % 3 == 2) {
                    printf(" ");
                }
            }
            printf("\n");
            afficheLigneTiret();
        }

        for (int colonne = 0; colonne < TAILLE; colonne++) {

            if (colonne == 0) {
                printf("%d |", ligne + 1);
            }

            // Afiche la valeur
            caseValeur = grille[ligne][colonne];
            if (ligne != TAILLE + 1) {
                if (caseValeur == CASE_VIDE) {
                    printf(" . ");
                } else {
                    printf(" %d ", caseValeur);
                }
            }

            if (colonne % 3 == 2) {
                printf("|");
            }
        }

        printf("\n");
        if (ligne % 3 == 2 || ligne == TAILLE - 1) {
            afficheLigneTiret(ligne);
        }
    }
}

void afficheLigneTiret() {
    printf("  ");
    for (int colonne = 0; colonne < TAILLE; colonne++) {
        if (colonne == TAILLE - 1) {
            printf("----+");
        } else if (colonne % 3 == 0) {
            printf("+-");
        } else {
            printf("----");
            // printf("| 3  7  8  |");
        }
    }
    printf("\n");
}


bool grilleRempli(t_grille grille) {
    for (int lig = 0; lig < TAILLE; lig++) {
        for (int col = 0; col < TAILLE; col++) {
            if (grille[lig][col] == CASE_VIDE) {
                return false;
            }
        }
    }

    return true;
}

/**
 * @fn int countRowValue(int **grille, int ligneIndice, int valeur)
 * @brief 
 * 
 * @param grille 
 * @param ligneIndice 
 * @param valeur 
 * @return int 
 */
int compteLigneValeur(t_grille grille, int ligneIndice, int valeur) {
    int count = 0;

    for (int col = 0; col < TAILLE; col++) {
        if (grille[ligneIndice][col] == valeur) {
            count++;
        }
    }

    return count;
}


/**
 * @fn int countColValue(int **grille, int colonneIndice, int valeur)
 * @brief 
 * 
 * @param grille 
 * @param colonneIndice 
 * @param valeur 
 * @return int 
 */
int compteColonneValeur(t_grille grille, int colonneIndice, int valeur) {
    int count = 0;

    for (int lig = 0; lig < TAILLE; lig++) {
        if (grille[lig][colonneIndice] == valeur) {
            count++;
        }
    }

    return count;
}


/**
 * @fn int countBlockValue(int **grille, int blocIndice, int valeur)
 * @brief 
 * 
 * @param grille 
 * @param blocIndice 
 * @param valeur 
 * @return int 
 */
int compteBlocValeur(t_grille grille, int blocIndice, int valeur) {
    int count = 0;
    int blocLigne = 0;
    int blocLigneDebut = 0;
    int ilig;
    int icol;

    for (int bIndex = 0; bIndex < TAILLE; bIndex++) 
    {
        for (int lig = 0; lig < 3; lig++) 
        {
            for (int col = 0; col < 3; col++) 
            {
                ilig = lig + blocLigne * 3;
                icol = col + blocLigneDebut;
                if (grille[ilig][icol] == valeur && bIndex == blocIndice) {
                    count++;
                }
            }
        }
        blocLigneDebut+=3;

        // nouvelle ligne de bloc
        if (bIndex % 3 == 2 && bIndex != 0) {
            blocLigne++;
            blocLigneDebut = 0;
        }
    }

    return count;
}


/**
 * @fn int getBlockIndice(int ligneIndice, int colonneIndice)
 * @brief Get the Block Indice from lig and col index
 * 
 * @param ligneIndice 
 * @param colonneIndice 
 * @return int 
 */
int obtenirBlocIndice(int ligneIndice, int colonneIndice) {
    int ilig = 0;
    int icol = 0;
    int blocLigne = 0;
    int blocLigneDebut = 0;

    for (int blocIndice = 0; blocIndice < TAILLE; blocIndice++) {
        for (int lig = 0; lig < 3; lig++) {
            for (int col = 0; col < 3; col++) {
                ilig = lig + blocLigne * 3;
                icol = col + blocLigneDebut;

                if (ilig == ligneIndice && icol == colonneIndice) {
                    return blocIndice;
                }
            }
        }

        blocLigneDebut+=3;

        // new "line"
        if (blocIndice % 3 == 2 && blocIndice != 0) {
            blocLigne++;
            blocLigneDebut = 0;
        }
    }

    return 0;
}


bool possible(t_grille grille, int numLigne, int numColonne, int valeur) {
    bool resultat = true;
    t_grille tempGrille;
    copierGrille(grille, tempGrille);
    tempGrille[numLigne][numColonne] = valeur;

    if (compteLigneValeur(tempGrille, numLigne, valeur) > 1 ||
        compteColonneValeur(tempGrille, numColonne, valeur) > 1 ||
        compteBlocValeur(tempGrille, obtenirBlocIndice(numLigne, numColonne), valeur) > 1) {
        resultat = false;
    }

    return resultat;
}

void copierGrille(t_grille grille, t_grille nouvelleGrille) {
    for (int lig = 0; lig < TAILLE; lig++) {
        for (int col = 0; col < TAILLE; col++) {
            nouvelleGrille[lig][col] = grille[lig][col];
        }
    }
}


// -------------------------------------------------------------------------
// Fonctions lier au terminal
// -------------------------------------------------------------------------

/**
 * @fn void saisir(int *S, char message[])
 * @brief Permet de saisir et de vérifier une valeur 
 * 
 * @param var
 * @param message 
 */
void saisir(int *var) {
    char saisieCh[MAX_SAISIE_SIZE];

    printf("\n> ");
    scanf("%s", saisieCh);

    while (sscanf(saisieCh, "%d", var) == 0)
    {
        printErreur("Veuillez saisir un nombre entier et non pas autre chose.");
        printf("> ");
        scanf("%s", saisieCh);
    }


    // if (sscanf(saisieCh, "%d", var) != 0) {
    //     printf("nice");
    // } else {
    //     printf("shit");
    // }
}




/**
 * @fn void printfCouleur(int couleurPremierPlan, int couleurFond, const char *format, ...)
 * @brief Impression personnalisée de texte avec des couleurs
 * 
 * @param couleurPremierPlan 
 * @param couleurFond 
 * @param format 
 * @param ... 
 */
void printfCouleur(int couleurPremierPlan, int couleurFond, const char *format, ...) {
    char message[MAX_MSG_SIZE] = "";

    va_list args;

    va_start(args, format);
    vsnprintf(message, MAX_MSG_SIZE, format, args);
    va_end(args);

    if (couleurFond == -1) {
        printf("\033[%dm%s\033[0m", couleurPremierPlan, message);
    } else if (couleurPremierPlan == -1) {
        printf("\033[%dm%s\033[0m", couleurFond, message);
    } else {
        printf("\033[%d,%dm%s\033[0m", couleurPremierPlan, couleurFond, message);
    }
}

/**
 * @fn void effaceTerminal()
 * @brief Effacer la fenêtre du terminal
 * 
 */
void effaceTerminal() {
    #ifdef _WIN32
    system("cls");
    #elif defined(__unix__) || defined(__APPLE__)
    system("clear");
    #endif
}

/**
 * @brief Affiche une erreur 
 * 
 * @param message 
 */
void printErreur(char message[]) {
    printfCouleur(RED_FG, -1, "\n%s\n\n", message);
}
