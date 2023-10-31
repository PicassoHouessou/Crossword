#include "crossword.h"


int main(int argv,char* argc[]){
    Crossword *cw=malloc(sizeof(Crossword));
    nouvelle_partie(&cw,10,12,16,2);
    sauvegarder_partie(cw,10,12,16);
    free_Memory(&cw,12);
    return EXIT_SUCCESS;
}