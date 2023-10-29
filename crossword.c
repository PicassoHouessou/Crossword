#include "crossword.h"

void nouvelle_partie()
{
}

void reprendre_partie()
{
}

void sauvegarder_partie()
{
}

void statistique()
{
}

Cellule **generer_grille(int nr,int nc)
{
   Cellule ** grille=NULL;
   *grille=malloc(sizeof(Cellule)*nr);
   for (int i = 0; i < nr; i++)
   {
        grille[i]=malloc(sizeof(Cellule)*nc);
        for (int j = 0; j < nc; j++)
        {
            grille[i][j].id=0;
            grille[i][j].w='*';
        }
    
   }
   
    return grille;
}

Dictionnaire *fillDictionnaire(int n)
{
    FILE *f=NULL;
    Dictionnaire *dic=NULL;
    f=fopen("dictionnaire_facile.txt","r");
    if(f==NULL){
        return NULL;
    }
    else
    {
        dic=malloc(sizeof(Dictionnaire)*n);
        int i=0;
        while (fscanf(f,"%d  %s  %s  %s  %s",&dic[i].id,&dic[i].indiceH,&dic[i].indiceV,&dic[i].resH,&dic[i].resV)!=EOF && i<n)
        {
            i++;
        }
        
    }
    
    // dic[0].id=1;
    // strcpy(dic[0].indiceH,"France");
    // strcpy(dic[0].indiceV,"");
    // strcpy(dic[0].resH,"FRA");
    // strcpy(dic[0].indiceV,"");
    return dic;
}

void printGrille(Cellule **cel, int nr, int nc)
{
    if (cel!=NULL)
    {
        for (int i = 0; i < nr; i++)
        {
            for (int j = 0; j < nc; j++)
            {
                printf("\n--\n");
                printf("|%c|",cel[i][j].w);
                printf("\n--\n");
            }
            printf("\n");
        }
        
    }
    return;
}

void printDictionnaire(Dictionnaire * dic,int n)
{
    if (dic!=NULL)
    {
        for (int i = 0; i < n; i++)
        {
            printf("\nId = %d \t indiceH = %s\t indiceV = %s\t resH = %s\t resV = %s\n",dic[i].id,dic[i].indiceH,dic[i].indiceV,dic[i].resH,dic[i].resV);
        }
        
    }
    return;
}
