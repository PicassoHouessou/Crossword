#ifndef ___CROSSWORD___
#define ___CROSSWORD___

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define nrow 5

typedef struct cellule
{
    int id;
    char w;
} Cellule;

typedef struct dic
{
    int id;
    char indiceH[100];
    char indiceV[100];
    char resH[25];
    char resV[25];
} Dictionnaire;

typedef struct crossword
{
    char niveau[10];
    Cellule** g;
    Dictionnaire *dic;
} Crossword;

void nouvelle_partie();
void reprendre_partie();
void sauvegarder_partie();
void statistique();

Cellule **generer_grille(int,int);
Dictionnaire *fillDictionnaire(int);
void printGrille(Cellule **,int,int);
void printDictionnaire(Dictionnaire*,int);




#endif // ___CROSSWORD___

