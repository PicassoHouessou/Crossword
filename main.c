#include "crossword.h"


int main(int argv,char* argc[]){
    // printf("\n%d\n",argv);
    // print_dictionnaire(remplacer_underscore_mots_dictionnaire(load_dictionnaire("dictionnaire_facile.txt",10),10),10);
    // print_grille(generer_grille(load_grille("facile.txt",12,16),12,16),12,16);
    Crossword *cw=malloc(sizeof(Crossword));
    nouvelle_partie(&cw,10,12,16,2);
    sauvegarder_partie(cw,10,12,16);
    free_Memory(&cw,12);
    return EXIT_SUCCESS;
}