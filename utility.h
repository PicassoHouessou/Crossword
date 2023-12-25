#ifndef ___UTILITY___
#define ___UTILITY___
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void viderBuffer();

/**
 * Lecture sécurisée d'une chaine de caractère
 */
int lire(char *chaine, int longueur);

/**
 * Lecture sécurisée d'un grand nombre
 */
long lireLong();

/**
 * Lecture sécurisée d'un  nombre
 * @return int
 */
int lireInt();

/**
    Function to check if an integer is contained in an integer array.
    @param arr The array to search in.
    @param size The size of the array.
    @param value The value to search for.
    @return True if the value is found, otherwise false.
*/
bool contains(int arr[], int size, int value);

/// @brief vérifier si un entier est contenu dans un tableau d'entiers
/// @param T tableaux qui contient tous les choix précedent
/// @param n taille du tableaux T
/// @param ch nouveau choix
/// @return une valeur 1 si le choix a déjà été fait et 0 sinon
int isIn(int T[], int n, int ch);
#endif // ___UTILITY___