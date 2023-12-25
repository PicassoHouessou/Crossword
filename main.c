#include "crossword.h"

int main(int argv, char *argc[])
{
    Crossword *cw = malloc(sizeof(Crossword));
    int r = 1;
    printf("\n\n************************************************************ Welcome to Crossworld *************************************************************************\n\n");
    while (r)
    {
        switch (menu())
        {
        case -1:
            break;
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
        default:
            // nouvelle_partie(&cw);
            break;
        }
    }
    printf("\n\n********************************************************************** Good Bye ****************************************************************************\n\n");
    free_memory(&cw);
    return EXIT_SUCCESS;
}