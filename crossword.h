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
    char caractere[1];
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

void nouvelle_partie(Crossword **,int,int,int,int);
void run(Crossword **,int,int,int,int);
void reprendre_partie();
void sauvegarder_partie();
void statistique();

Cellule **load_grille(char *,int,int);
Dictionnaire *load_dictionnaire(char *,int);
void print_grille(Cellule **,int,int);
void print_dictionnaire(Dictionnaire*,int);
void free_Memory(Crossword **,int);

Cellule **generer_grille(Cellule **,int,int);

Dictionnaire *generer_dictionnaire(Dictionnaire *,int);

Dictionnaire *remplacer_underscore_mots_dictionnaire(Dictionnaire *,int);

char *replace(char *,char,char);
int choix_niveau();


#endif // ___CROSSWORD___

