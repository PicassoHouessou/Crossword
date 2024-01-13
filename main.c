#include "crossword.h"

int main(int argv, char *argc[])
{
    system("chmod  +x *.sh");
    system("./remove_save.sh");
    Crossword *cw = malloc(sizeof(Crossword));
    int r = 1;
    printf("\n\n************************************************************ Welcome to Crossword *************************************************************************\n\n");
    while (r)
    {
        switch (menu())
        {
        case 1:
            nouvelle_partie(&cw);
            break;
        case 2:
            reprendre_partie(&cw);
            break;
        case 3:
            statistique();
            break;
        case 4:
            r = 0;
            break;
        case 5:
            appropos();
            break;
        default:
            printf("\nVotre choix n'est pas disponible.\n");
            break;
        }
    }
    printf("\n\n********************************************************************** Good Bye ****************************************************************************\n\n");
    if (cw != NULL)
    {
        free_memory(&cw);
    }
    return EXIT_SUCCESS;
}