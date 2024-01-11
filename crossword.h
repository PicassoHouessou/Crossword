#ifndef ___CROSSWORD___
#define ___CROSSWORD___

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "utility.h"

#define USERNAME_SIZE 25
#define LEVEL_SIZE 30
#define GRID_LEVEL_SIZE 20
#define SUBJECT_SIZE 50
#define DICTIONARY_ENTRY_SIZE 255
#define ANSWER_SIZE 50
#define FILE_PATH_SIZE 150

/*
    structure pour conserver le nom du joueur
*/
typedef struct user
{
    char username[USERNAME_SIZE];
} User;

/// @brief structure pour concerver les statstiques du joueur
typedef struct stat
{
    char niveau[LEVEL_SIZE];
    float score;
    struct tm heure_debut;
    struct tm heure_fin;
} Statistique;

/// @brief structure qui modélise la cellule d'une grille
typedef struct cellule
{
    int id;
    char caractere;
} Cellule;

/// @brief structure qui met en relation les indices
/// @brief et leurs réponses associées suivant le sens horizontal et vertical
typedef struct dictionnaire
{
    int id;
    char indice_horizontal[255];
    char indice_vertical[255];
    char resultat_horizontal[50];
    char resultat_vertical[50];
    int dim;
} Dictionnaire;

/// @brief structure pour généraliser une partie qui est constitué du niveau, la grille qui est
/// @brief une matrice, du dctionnaire qui est un tableau et un champ pour conserver les statistiques
typedef struct gril
{
    char niveau[GRID_LEVEL_SIZE];
    Cellule **grille;
    int nombre_ligne;
    int nombre_colonne;
} Grille;

/// @brief structure de donnée pour contenir les informations d'une partie
typedef struct crossword
{
    User *u;
    Grille *g;
    Dictionnaire *dictionnaire;
    Statistique *stat;
    char sujet[50];
} Crossword;

/// @brief Lance une nouvelle partie
/// @param Crossword** paramètre qui va contenir les informations sur la partie encours
/// @brief qui est un pointeur sur un pointeur de la partie du jeu encours. cette déclaration
/// @brief nous permet d'éviter de retourner la structure qui représente une partie à la fin de la partie
void nouvelle_partie(Crossword **);

/// @brief fonction qui contient toute l'implémentation du déroulement d'une partie
/// @param  Crossword ** paramètre qui va contenir les informations sur la partie encours
/// @brief qui est un pointeur sur un pointeur de la partie du jeu encours. cette déclaration
/// @brief nous permet d'éviter de retourner la structure qui représente une partie à la fin de la partie
/// @param  Crossword * parametre pour contenir les informations complete sur la partie encours
/// @param  int nombre d'éssais possible pour trouver une réponse durant la partie encours
void run(Crossword **, Crossword *, int, char *, char *);

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
Grille *load_grille(char *);

/// @brief fonction qui permet de charger le contenu d'un dictionnaire enregistrer dans un fichier
/// @param  char * adresse relative du fichier contenant les informations du dictionnaire
/// @param  int la taille du dictionnaire
/// @return un tableau représentant le dictionnaire de notre partie
Dictionnaire *load_dictionnaire(char *);

/// @brief fonction pour afficher notre grille sur la console
/// @param  Cellule ** représente notre grille
/// @param  int nombre de ligne de la grille
/// @param  int nombre de colonne de la grille
/// @return void
void print_grille(Grille *);

/// @brief fonction pour afficher le contenu de notre dictionnaire sur la console
/// @param  Dictionnaire* tableau qui contient les informations de notre dictionnaire
/// @param  int la taille du tableau
void print_dictionnaire(Dictionnaire *);

/// @brief fonction pour libérer la mémoire occupée par notre partie
/// @param  Crossword ** contient l'adresse de notre partie encours
/// @return void
void free_memory(Crossword **);

/// @brief fonction qui permet de générer une grille non remplie à partir d'une grille déjà remplie
/// @param  Cellule ** la grille dont on veut créer le clone
/// @param  int nombre de ligne de la grille
/// @param  int nombre de colonne de la grille
/// @return  une copie non remplie de la grille prise en paramèttre
Grille *generer_grille(Grille *);

/// @brief fonction qui permet de remplacer les underscores qui séparant les différents mots des indices horizontaux et verticaux du dictionnaire
/// @param  Dictionnaire * tableau dont on veut remplacer les underscores qui separent les différents mots des indices horizontaux et verticaux
/// @param  int taille du tableau
/// @return un dictionnaire dont les underscores séparants les différents mots des indices horizontaux et verticaux ont été remplacés par un espace
Dictionnaire *remplacer_underscore_mots_dictionnaire(Dictionnaire *);

/// @brief fonction qui permet de remplacer les underscores qui séparant les différents mots des indices horizontaux et verticaux du dictionnaire
/// @param  Dictionnaire * tableau dont on veut remplacer les espaces qui separent les différents mots des indices horizontaux et verticaux
/// @param  int taille du tableau
/// @return un dictionnaire dont les espaces séparants les différents mots des indices horizontaux et verticaux ont été remplacés par un underscores
Dictionnaire *remplacer_espace_mots_dictionnaire(Dictionnaire *);

/// @brief fonction qui permet de remplacer dans une chaine de caractère un caratère par un autre
/// @param  char * chaine de caractère dont ont veut modifier certains de ses caractères
/// @param  char caractère a remplacé
/// @param  char caractère de remplacement
/// @return une chaine de caractère dont toutes les occurences du deuxième paramètre ont été remplacés par le troisième paramètre
char *replace(char *, char, char);

/// @brief fonction qui permet de sélectioner le niveau de difficulté
/// @return un nombre compris entre 1 et 3 représentant le nveau de difficulté choisit par le joueur
int choix_niveau();

/// @brief fonction qui permet de selectionner l'opération à exercuter au lancement du jeu
/// @return un nombre compris entre 1 et 5 representant les différentes fonctionnalitions offertes par notre jeu
int menu();

/// @brief fonction qui permet a un joueur de demander de l'aide sur le résultat d'un indice pendant une partie
/// @return un entier indiquant l'action a éxécuté
int demande_aide();

/// @brief fonction qui permet a un joueur de choisir le sujet sur lequel va porter la partie encours
/// @return un entier indiquant l'action a éxécuté
int sujet();

Statistique *load_statistique(char *, char *, char *);

/// @brief enregistre les choix d'une partie dans un fichier
/// @param T
/// @param n
/// @param filename
void sauvegarder_choix(int *T, int n, char *filename);

/// @brief Charger les choix précédemment sauvegardés
/// @param
/// @param
/// @return
int *load_choix(int, char *);

/// @brief   Retourne le domaine (ou le sujet)
/// @param subjectCode
/// @return char* le sujet
char *get_subject(int subjectCode);

/// @brief Helper function to get difficulty level
/// @return char* la difficulté entre {facile,intermediare,difficile}
char *get_difficulty(int levelCode);

/// @brief Helper function to determine the number of attempts based on difficulty
/// @return int
int get_number_of_attempts(char *difficulty);

/// @brief Lire le choix de l'utilisateur qui est un nombre compris entre 0 et 9
/// @param turn
/// @param maxChoices
/// @param currentChoices
/// @return le choix de l'utilisateur
int get_choice(int turn, int maxChoices, int *currentChoices);

/// @brief Verifie si la réponse donnée est correcte
/// @param char response
/// @param Dictionnaire entry
/// @param Crossword c
/// @return true si la réponse est correcte et false sinon
bool is_correct_answer(char *response, Dictionnaire entry, Crossword *c);

/// @brief Sauvegarde l'état du jeu
/// @param Crossword cw
/// @param int score
/// @param int float manus
/// @param currentChoices
/// @param filename
void save_and_exit(Crossword **cw, int score, float manus, int *currentChoices, char *filename);

float display_hint_and_get_manus(Dictionnaire *entry, Crossword *c);

/// @brief Mets à jour la grille avec la réponse
/// @param grid
/// @param response
/// @param choice
void update_grid_with_answer(Grille *grid,Dictionnaire dic, char *response, int choice);

char * upper_case(char*);

#endif // ___CROSSWORD___