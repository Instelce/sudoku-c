# Peudo code

Célestin Besson - 1A1

## Programme principal

```pseudo-code
programme principal c’est
début
 loop : booléen;
 canShowGame : booléen;
 
 loop := vrai;
 canShowGame := faux;

 tant que (loop) faire:
  showMainMenu(entF/sortF canShowGame, entF/sortF loop);
  showGame(entF/sortF canShowGame);
 finfaire
fin
```

## Contantes & types

define SUDOKU_SIZE 9

entier t_grid[SUDOKU_SIZE][SUDOKU_SIZE];

## Fonctions

- [showMainMenu](#showMainMenu)
- [showGame](#showGame)

- [createSudokuGrid](#createSudokuGrid)
- [createSudokuGridFrom](#createSudokuGridFrom)
- [updateGridEmptyValueIndexFromGrid](#updateGridEmptyValueIndexFromGrid)

- [printCase](#printCase)
- [printSudoku](#printSudoku)

- [countValue](#countValue)
- [countRowValue](#countRowValue)
- [countColValue](#countColValue)
- [countBlockValue](#countBlockValue)
- [getBlockIndice](#getBlockIndice)
- [getMaxOfGrid](#getMaxOfGrid)

- [freeMatrix](#freeMatrix)
- [checkAllocation](#checkAllocation)

- [printfColor](#printfColor)
- [printError](#printError)
- [clearTerm](#clearTerm)


---


<h3 id="showMainMenu">showMainMenu</h3>

**procedure** showMainMenu

Affichage du menu principale si le paramètre *canShowGame* est faux.
Modifie les variables *canShowGame* et *loop* passé en paramètre, pour arrêter ou lancer le jeu.

**paramètres**

*canShowGame* (Entrée/Sortie) : boolean, <br>
*loop* (Entrée/Sortie) : boolean, <br>


---


<h3 id="showGame">showGame</h3>

**procedure** showGame

Affichage du jeu si le paramètre *canShowGame* est vrai. <br>
Modifie la variable *canShowGame* pour revenir au menu principal.

Fait appel à :

- createSudokuGridFrom
- createSudokuGrid
- updateGridEmptyValueIndexFromGrid
- checkAllocation
- getMaxFromGrid
- initMoves
- printSudoku
- printMoves
- printError
- countRowValue
- countColValue
- countBlockValue
- getBlockIndice
- updateMove
- freeMatrix

**paramètres**

*canShowGame* (Entrée/Sortie) : boolean, <br>


---

<h3 id="createSudokuGrid">createSudokuGrid</h3>

**fonction** createSudokuGrid

**paramètres**

*caseValue* (Entrée) : entier, <br>

**resultat**

pointeur de pointeur d'entier, où toutes les valeurs sont initialisé à la valeur de *caseValue*.

---

<h3 id="createSudokuGridFrom">createSudokuGridFrom</h3>

**fonction** createSudokuGridFrom

**paramètres**

*startGrid* (Entrée) : t_grid, <br>

**resultat**

pointeur de pointeur d'entier, où toute les valeurs seront initialisé par les valeurs de la matrice passé en paramètre *startGrid*.

---

<h3 id="updateGridEmptyValueIndexFromGrid">updateGridEmptyValueIndexFromGrid</h3>

**procedure** updateGridEmptyValueIndexFromGrid

Met à jour la grille *indexGrid* passé en paramère, avec les index des cases vides d'une autre grille.

**paramètres**

*indexGrid* (Entrée/Sortie) : pointeur de pointeur d'entier, <br>
*grid* (Entrée/Sortie) : pointeur de pointeur d'entier


---


<h3 id="printCase">printCase</h3>

**procedure** printCase

Affiche une case avec de la couleur. Et permet de centrer les valeurs.

**paramètres**

*value* (Entrée) : caractère, <br>
*foregroundColor* (Entrée) : entier <br>
*backgroundColor* (Entrée) : entier


---


<h3 id="printSudoku">printSudoku</h3>

**procedure** printSudoku

Affichage de la grille du sudoku, en fonction des paramètres d'entrées.

**paramètres**

*grid* (Entrée/Sortie) : pointeur de pointeur d'entier, <br>
*indexGrid* (Entrée/Sortie) : pointeur de pointeur d'entier, <br>
*showIndex* (Entrée) : booleen, permmet d'afficher les valeurs de la matrice *indexGrid* <br>
*errorValue* (Entrée) : entier, permet d'afficher en rouge les cases qui génère une erreur quand l'utilisateur met la une valeur qui existe déjà dans la ligne/colonne/bloc. Si elle est négative, aucun affichage <br>
*selectedCase* (Entré/Sortie) : pointeur, contient deux valeurs qui sont les positions de la case sélectionné. Si aucune case est sélectionné, la première valeur est négative.


---


<h3 id="countValue">countValue</h3>

**fonction** countValue

**paramètres**

*grid* (Entrée/Sortie) : pointeur de pointeur d'entier, <br>
*value* (Entrée) : entier,

**resultat**

entier, retourne le nombre de fois que la valeur (*value*) est présente dans la grille (*grid*).


---


<h3 id="countRowValue">countRowValue</h3>

**fonction** countRowValue

**paramètres**

*grid* (Entrée/Sortie) : pointeur de pointeur d'entier, <br>
*rowIndex* (Entrée) : entier, <br>
*value* (Entrée) : entier,

**resultat**

entier, retourne le nombre de fois que la valeur (*value*) est présente dans la ligne n (*rowIndex*) de la grille (*grid*).


---


<h3 id="countColValue">countColValue</h3>

**fonction** countColValue

**paramètres**

*grid* (Entrée/Sortie) : pointeur de pointeur d'entier, <br>
*colIndex* (Entrée) : entier, <br>
*value* (Entrée) : entier,

**resultat**

entier, retourne le nombre de fois que la valeur (*value*) est présente dans la colonne n (*colIndex*) de la grille (*grid*).


---


<h3 id="countBlockValue">countBlockValue</h3>

**fonction** countBlockValue

**paramètres**

*grid* (Entrée/Sortie) : pointeur de pointeur d'entier, <br>
*blockIndex* (Entrée) : entier, <br>
*value* (Entrée) : entier,

**resultat**

entier, retourne le nombre de fois que la valeur (*value*) est présente dans le bloc n (*blockIndex*) de la grille (*grid*).


---


<h3 id="getBlockIndice">getBlockIndice</h3>

**fonction** getBlockIndice

**paramètres**

*rowIndex* (Entrée) : entier, <br>
*colIndex* (Entrée) : entier,

**resultat**

entier, retourne l'indice du block ou se trouve la case de coordonné (*rowIndex*, *colIndex*).


---


<h3 id="getValuePos">getValuePos</h3>

**fonction** getValuePos

Marche uniquement avec une matrice n'ayant pas de valeur en double.

**paramètres**

*grid* (Entrée/Sortie) : pointeur de pointeur d'entier, <br>
*value* (Entrée) : entier,

**resultat**

entier, retourne l'indice de la case qui contient la valeur de la variable *value*.


---


<h3 id="getMaxOfGrid">getMaxOfGrid</h3>

**fonction** getMaxOfGrid

**paramètres**

*grid* (Entrée/Sortie) : pointeur de pointeur d'entier, <br>

**resultat**

entier, retourne la valeur maximale de la grille (*grid*) passé en paramètre.


---


<h3 id="freeMatrix">freeMatrix</h3>

**procéduce** freeMatrix

Libérer la mémoire allouée par une matrice

**paramètres**

*matrix* (Entrée/Sortie) : pointeur de pointeur de tout type, <br>
*size* (Entrée) : entier, taille de la matrice <br>


---


<h3 id="checkAllocation">checkAllocation</h3>

**procéduce** checkAllocation

Arrête le programme si le pointeur passé en paramère est null.

**paramètres**

*pointeur* (Entrée/Sortie) : pointeur, <br>


---


<h3 id="printfColor">printfColor</h3>

**procéduce** printfColor

Affiche en couleur du texte.

**paramètres**

*foregroundColor* (Entrée) : entier, <br>
*backgroundColor* (Entrée) : entier, <br>
*text* (Entrée) : tableau de caractère, <br>


---


<h3 id="printError">printError</h3>

**procéduce** printError

Affichage customisé d'une erreur.

**paramètres**

*text* (Entrée) : tableau de caractère,


---


<h3 id="clearTerm">clearTerm</h3>

**procéduce** clearTerm

Efface le terminal.

**paramètres**

*Aucun paramètre*

