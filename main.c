#include "crossword.h"


int main(int argv,char* argc[]){
    // printf("\n%d\n",argv);
    // printDictionnaire(fillDictionnaire(10),10);
    print_grille(generer_grille(load_grille(12,16),12,16),12,16);
    return EXIT_SUCCESS;
}