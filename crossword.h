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
    char caractere;
} Cellule;

typedef struct dic
{
    int id;
    char indice_horizontal[100];
    char indice_vertical[100];
    char resultat_horizontal[25];
    char resultat_vertical[25];
} Dictionnaire;

typedef struct crossword
{
    char niveau[10];
    Cellule** grille;
    Dictionnaire *dictionnaire;
} Crossword;

void nouvelle_partie();
void reprendre_partie();
void sauvegarder_partie();
void statistique();

Cellule **generer_grille(int,int);
Dictionnaire *fill_dictionnaire(int);
void print_grille(Cellule **,int,int);
void print_dictionnaire(Dictionnaire*,int);




#endif // ___CROSSWORD___

