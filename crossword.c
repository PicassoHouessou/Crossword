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

Cellule **load_grille(int nr,int nc)
{
    Cellule ** grille=malloc(sizeof(Cellule)*nr);
    int size=nr*nc;
    Cellule *vec=(Cellule*)malloc(sizeof(Cellule)*size);
    int k=0;
    FILE *f=fopen("facile.txt","r");
    while (fscanf(f,"%d %s",&vec[k].id,&vec[k].caractere)!=EOF)
    {
        k++;
    }
    k=0;
    for (int i = 0; i < nr; i++)
    {
        grille[i]=malloc(sizeof(Cellule)*nc);
        for (int j = 0; j < nc; j++)
        {
            grille[i][j].id=vec[k].id;
            strcpy(grille[i][j].caractere,vec[k].caractere);
            k++;
        }
    }
    
    return grille;
}

Dictionnaire *fill_dictionnaire(int n)
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
        while (fscanf(f,"%d  %s  %s  %s  %s",&dic[i].id,&dic[i].indice_horizontal,&dic[i].indice_vertical,&dic[i].resultat_horizontal,&dic[i].resultat_vertical)!=EOF && i<n)
        {
            i++;
        }
        
    }
    return dic;
}

void print_grille(Cellule **cel, int nr, int nc)
{
    if (cel!=NULL)
    {
        for (int i = 0; i < nr; i++)
        {
            printf("\n");
            for (int j = 0; j < nc; j++)
            {
                if (cel[i][j].id!=0)
                {
                    printf("|%d %s|\t",cel[i][j].id,cel[i][j].caractere);
                }
                else
                {
                    printf("|%s|\t",cel[i][j].caractere);
                }
                
            }
            printf("\n");
        }
        
    }
    return;
}

void print_dictionnaire(Dictionnaire * dic,int n)
{
    if (dic!=NULL)
    {
        for (int i = 0; i < n; i++)
        {
            printf("\nId = %d \t indice_horizontal = %s\t indice_vertical = %s\t resultat_horizontal = %s\t resultat_vertical = %s\n",dic[i].id,dic[i].indice_horizontal,dic[i].indice_vertical,dic[i].resultat_horizontal,dic[i].resultat_vertical);
        }
        
    }
    return;
}



void free_Memory(Crossword **cw,int nr){
    if (cw!=NULL)
    {
        for (int i = 0; i < nr; i++)
        {
           free((*cw)->grille[i]);
        }
        free((*cw)->dictionnaire);
        free(*cw);
    }
    return;
}

Cellule **generer_grille(Cellule **grille, int nr, int nc)
{
    Cellule ** g=malloc(sizeof(Cellule)*nr);
    for (int i = 0; i < nr; i++)
    {
        g[i]=malloc(sizeof(Cellule)*nc);
        for (int j = 0; j < nc; j++)
        {
            g[i][j].id=grille[i][j].id;
            strcpy(g[i][j].caractere,grille[i][j].caractere[0]=='*'?grille[i][j].caractere:" ");
        }
    }
    return g;
}
