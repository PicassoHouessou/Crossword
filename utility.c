#include "utility.h"

void vider_buffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

int lire(char *chaine, int longueur)
{
    char *positionEntree = NULL;

    if (fgets(chaine, longueur, stdin) != NULL)
    {
        positionEntree = strchr(chaine, '\n');
        if (positionEntree != NULL)
        {
            *positionEntree = '\0';
        }
        else
        {
            vider_buffer();
        }
        return 1;
    }
    else
    {
        vider_buffer();
        return 0;
    }
}

long lire_long()
{
    char nombreTexte[100] = {0}; // 100 cases devraient suffire

    if (lire(nombreTexte, 100))
    {
        // Si lecture du texte ok, convertir le nombre en long et le retourner
        return strtol(nombreTexte, NULL, 10);
    }
    else
    {
        // Si problème de lecture, renvoyer 0
        return 0;
    }
}

int lire_int()
{
    char nombreTexte[100] = {0}; // 100 cases should be enough

    if (lire(nombreTexte, 100))
    {
        // If text reading is ok, convert the number to int and return it
        return (int)strtol(nombreTexte, NULL, 10);
    }
    else
    {
        // If there's a problem with reading, return 0
        return 0;
    }
}

bool contains(int arr[], int size, int value)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == value)
        {
            return true; // Exit immediately when found
        }
    }
    return false; // Return false if not found
}

int isIn(int T[], int n, int ch)
{
    for (int i = 0; i < n; i++)
    {
        if (T[i] == ch)
        {
            return 1;
        }
    }
    return 0;
}