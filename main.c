#include "crossword.h"


int main(int argv,char* argc[]){
    // printf("\n%d\n",argv);
    // printDictionnaire(fillDictionnaire(10),10);
    printGrille(generer_grille(10,10),10,10);
    return EXIT_SUCCESS;
}