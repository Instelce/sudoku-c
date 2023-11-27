# Helper function 


## tCase n°1

```pseudo-code
typedef struct {
    int valeur;
    int candidats[TAILLE];
    int nbCandidats;
} tCase1;
```

```pseudo-code
procédure ajouterCandidat( entF/sortF laCase : tCase1, entF val: entier)
    début
        si laCase.nbCandidat < TAILLE alors
            laCase.candidat[laCase.nbCandidat + 1] = val;
            laCase.nbCandidat++;
        finsi
    fin
```

```pseudo-code
procédure retirerCandidat( entF/sortF laCase : tCase1, entF val : entier)
    début
        entier : valIndice;

        valIndice := 0;
        pour i de 1 à laCase.nbCandidat faire
            si (laCase.candidats[i] == val AND valIndice == 0) alors
                valIndice := i;
            finsi
            si (valIndice != 0) alors
                laCase.candidat[i - 1] := laCase.candidat[i];
            finsi
        finfaire

        laCase.nbCandidat--;
    fin
```

```pseudo-code
fonction estCandidat( entF laCase : tCase1, entF val : entier) délivre booléen
    début
        entier : i;
        boolean : resultat;

        i := 0;
        resultat := FAUX;
        tant que i < laCase.nbCandidat AND laCase[i] != val faire
            i++;
        finfaire

        si laCase.candidats[i] == val alors
            resultat := VRAI;
        finsi

        retourne resultat;
    fin
```

```pseudo-code
fonction nbCandidats(entF laCase : tCase1) délivre entier
    début
        retourne laCase.nbCandidat;
    fin
```

## tCase n°2

```pseudo-code
typedef struct {
    int valeur;
    bool candidats[TAILLE+1];
    int nbCandidats;
} tCase2;
```

```pseudo-code
procédure ajouterCandidat( entF/sortF laCase : tCase1, entF val: entier)
    début
        laCase.candidat[val + 1] = true;
        laCase.nbCandidat++;
    fin
```

```pseudo-code
procédure retirerCandidat( entF/sortF laCase : tCase1, entF val : entier)
    début
        laCase.candidat[val + 1] = false;
        laCase.nbCandidat--;
    fin
```

```pseudo-code
fonction estCandidat( entF laCase : tCase1, entF val : entier) délivre booléen
    début
        retourne laCase.candidats[val + 1];
    fin
```

```pseudo-code
fonction nbCandidats(entF laCase : tCase1) délivre entier
    début
        retourne laCase.nbCandidat;
    fin
```

