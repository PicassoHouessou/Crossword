#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include <math.h>

#ifndef ___CROSSWORD___
#define ___CROSSWORD___

#define FACILE_NROW 12 // nombre de ligne de la grille du niveau facile
#define FACILE_NCOL 16 // nombre de colonne de grille du niveau facile
#define FACILE_DIC_SIZE 10  // taille du dictionnaire du niveau facile
#define INTER_DIC_SIZE 10 // taille du dictionnaire du niveau intermédiaire
#define DIFFICILE_DIC_SIZE 10 // taille du dictionnaire du niveau difficile
#define INTER_NROW 12  // nombre de ligne de la grille du niveau intermédiaire
#define INTER_NCOL 16 // nombre de colonne de grille du niveau intermédiaire
#define DIFFICILE_NROW 12 // nombre de ligne de la grille du niveau difficile
#define DIFFICILE_NCOL 16 // nombre de colonne de grille du niveau difficile

time_t secondes;

/// @brief structure pour concerver les statstiques du joueur
typedef struct stat
{
    char niveau[25];
    float score;
    struct tm heure_debut;
    struct tm heure_fin;
} Statistique;


/// @brief structure qui modélise la cellule d'une grille
typedef struct cellule
{
    int id;
    char caractere[1];
} Cellule;


/// @brief structure qui met en relation les indices 
/// @brief et leurs réponses associées suivant le sens horizontal et vertical
typedef struct dictionnaire
{
    int id;
    char indice_horizontal[100];
    char indice_vertical[100];
    char resultat_horizontal[25];
    char resultat_vertical[25];
} Dictionnaire;


/// @brief structure pour généraliser une partie qui est constitué du niveau, la grille qui est 
/// @brief une matrice, du dctionnaire qui est un tableau et un champ pour conserver les statistiques
typedef struct crossword
{
    char niveau[25];
    Cellule** grille;
    Dictionnaire *dictionnaire;
    Statistique *stat;
} Crossword;




/// @brief déclaration de la fonction qui va nous permettre de lancer une partie 
/// @param Crossword** 
/// @brief qui est un pointeur sur un pointeur de la partie du jeu encours. cette déclaration 
/// @brief nous permet d'éviter de retourner la structure qui représente une partie à la fin de la partie  
void nouvelle_partie(Crossword **);

/// @brief fonction qui contient toute l'implémentation du déroulement d'une partie
/// @param  Crossword **
/// @brief qui est un pointeur sur un pointeur de la partie du jeu encours. cette déclaration 
/// @brief nous permet d'éviter de retourner la structure qui représente une partie à la fin de la partie
/// @param  Crossword *
/// @brief qui est un pointeur sur les resultats de la partie du jeu encours.
/// @param  int taille du dictionnaire de la partie encours
/// @param  int nombre de ligne de la grille de la partie encours
/// @param  int nombre de colonne de la grille de la partie encours
/// @param  int nombre d'éssais possible pour trouver une réponse durant la partie encours
void run(Crossword **,Crossword *,int,int,int,int);


/// @brief déclaration de la fonction qui va nous permettre de lancer une partie 
/// @param Crossword** 
/// @brief qui est un pointeur sur un pointeur de la partie du jeu encours. cette déclaration 
/// @brief nous permet d'éviter de retourner la structure qui représente une partie à la fin de la partie
void reprendre_partie(Crossword **);

/// @brief fonction qui permet d'enregistrer la progression d'un joueur dans un fichier
/// @param  Crossword * contient la copie de la partie encours
void sauvegarder_partie(Crossword *);

/// @brief fonction pour afficher les statistique du joueur
void statistique();

/// @brief fonction qui permet de charger le contenu d'une grille enregistrer dans un fichier
/// @param  char * adresse relative du fichier contenant les informations de la grille
/// @param  int nombre de ligne de la grille
/// @param  int nombre de colonne de la grille
/// @return une matrice à deux dimensions représentant notre grille
Cellule **load_grille(char *,int,int);

/// @brief fonction qui permet de charger le contenu d'un dictionnaire enregistrer dans un fichier
/// @param  char * adresse relative du fichier contenant les informations du dictionnaire
/// @param  int la taille du dictionnaire 
/// @return un tableau représentant le dictionnaire de notre partie
Dictionnaire *load_dictionnaire(char *,int);

/// @brief fonction pour afficher notre grille sur la console
/// @param  Cellule ** représente notre grille
/// @param  int nombre de ligne de la grille
/// @param  int nombre de colonne de la grille
void print_grille(Cellule **,int,int);

/// @brief fonction pour afficher le contenu de notre dictionnaire sur la console
/// @param  Dictionnaire* tableau qui contient les informations de notre dictionnaire
/// @param  int la taille du tableau
void print_dictionnaire(Dictionnaire*,int);

/// @brief fonction pour libérer la mémoire occupée par notre partie
/// @param  Crossword ** contient l'adresse de notre partie encours
void free_Memory(Crossword **);


/// @brief fonction qui permet de générer une grille non remplie à partir d'une grille déjà remplie
/// @param  Cellule ** la grille dont on veut créer le clone
/// @param  int nombre de ligne de la grille 
/// @param  int nombre de colonne de la grille
/// @return  une copie non remplie de la grille prise en paramèttre
Cellule **generer_grille(Cellule **,int,int);

/// @brief fonction qui permet de générer un dictionnaire à partir d'un autre dictionnaire
/// @param  Dictionnaire * dictionnare dont on veut créer le clone
/// @param  int taille du dictionnaire
/// @return une copie  du dictionnaire pris en paramèttre
Dictionnaire *generer_dictionnaire(Dictionnaire *,int);

/// @brief fonction qui permet de remplacer les underscores qui séparant les différents mots des indices horizontaux et verticaux du dictionnaire
/// @param  Dictionnaire * tableau dont on veut remplacer les underscores qui separent les différents mots des indices horizontaux et verticaux
/// @param  int taille du tableau
/// @return un dictionnaire dont les underscores séparants les différents mots des indices horizontaux et verticaux ont été remplacés par un espace
Dictionnaire *remplacer_underscore_mots_dictionnaire(Dictionnaire *,int);


/// @brief fonction qui permet de remplacer les underscores qui séparant les différents mots des indices horizontaux et verticaux du dictionnaire
/// @param  Dictionnaire * tableau dont on veut remplacer les espaces qui separent les différents mots des indices horizontaux et verticaux
/// @param  int taille du tableau
/// @return un dictionnaire dont les espaces séparants les différents mots des indices horizontaux et verticaux ont été remplacés par un underscores
Dictionnaire *remplacer_espace_mots_dictionnaire(Dictionnaire *,int);

/// @brief fonction qui permet de remplacer dans une chaine de caractère un caratère par un autre
/// @param  char * chaine de caractère dont ont veut modifier certains de ses caractères
/// @param  char caractère a remplacé
/// @param  char caractère de remplacement
/// @return une chaine de caractère dont toutes les occurences du deuxième paramètre ont été remplacés par le troisième paramètre 
char *replace(char *,char,char);

/// @brief fonction qui permet de sélectioner le niveau de difficulté
/// @return un nombre compris entre 1 et 3 représentant le nveau de difficulté choisit par le joueur
int choix_niveau();

/// @brief fonction qui permet de selectionner l'opération à exercuter au lancement du jeu
/// @return un nombre compris entre 1 et 5 representant les différentes fonctionnalitions offertes par notre jeu
int menu();

#endif // ___CROSSWORD___

