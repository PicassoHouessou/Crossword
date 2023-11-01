#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include <math.h>

#ifndef ___CROSSWORD___
#define ___CROSSWORD___

#define FACILE_NROW 12
#define FACILE_NCOL 16
#define FACILE_DIC_SIZE 10
#define INTER_DIC_SIZE 10
#define DIFFICILE_DIC_SIZE 10
#define INTER_NROW 12
#define INTER_NCOL 16
#define DIFFICILE_NROW 12
#define DIFFICILE_NCOL 16

time_t secondes;
typedef struct stat
{
    char niveau[15];
    float score;
    struct tm heure_debut;
    struct tm heure_fin;
} Statistique;

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
    Statistique *stat;
} Crossword;
void nouvelle_partie(Crossword **);
void run(Crossword **,Crossword *,int,int,int,int);
void re_run(Crossword **);
void reprendre_partie(Crossword **);
void sauvegarder_partie(Crossword *);
void statistique();
void sauvegarder_statistique(Statistique *);

Cellule **load_grille(char *,int,int);
Dictionnaire *load_dictionnaire(char *,int);
void print_grille(Cellule **,int,int);
void print_dictionnaire(Dictionnaire*,int);
void free_Memory(Crossword **);

Cellule **generer_grille(Cellule **,int,int);

Dictionnaire *generer_dictionnaire(Dictionnaire *,int);

Dictionnaire *remplacer_underscore_mots_dictionnaire(Dictionnaire *,int);
Dictionnaire *remplacer_espace_mots_dictionnaire(Dictionnaire *,int);

char *replace(char *,char,char);
int choix_niveau();
int menu();

#endif // ___CROSSWORD___

