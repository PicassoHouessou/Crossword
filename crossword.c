#include "crossword.h"

void nouvelle_partie(Crossword **cw,int n,int nr,int nc)
{
    printf("\n1-Niveau facile.\n");
    printf("\n2-Niveau interm%cdiaire.\n",130);
    printf("\n3-Niveau difficile.\n");
    int choix;
    printf("\nEntrez votre choix :\t");
    scanf("%d",&choix);
    if (choix==1)
    {
        strcpy((*cw)->niveau,"facile");
        Dictionnaire *dic=remplacer_underscore_mots_dictionnaire(load_dictionnaire("dictionnaire_facile.txt",n),n);
        (*cw)->dictionnaire=dic; 
        
        (*cw)->grille=generer_grille(load_grille("facile.txt",nr,nc),nr,nc);
        print_grille((*cw)->grille,nr,nc);
        printf("\n\n");
        print_dictionnaire((*cw)->dictionnaire,n);
    }
    
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

Cellule **load_grille(char *filename,int nr,int nc)
{
    Cellule ** grille=malloc(sizeof(Cellule)*nr);
    int size=nr*nc;
    Cellule *vec=(Cellule*)malloc(sizeof(Cellule)*size);
    int k=0;
    FILE *f=fopen(filename,"r");
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

Dictionnaire *load_dictionnaire(char *filename,int n)
{
    FILE *f=NULL;
    Dictionnaire *dic=NULL;
    f=fopen(filename,"r");
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
        printf("\nHorizontal\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tVertical\n");
        for (int i = 0; i < n; i++)
        {
            if (dic[i].indice_horizontal[0]=='-' && dic[i].indice_vertical[0]!='-')
            {
                printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t%d-%s.\n",dic[i].id,dic[i].indice_vertical);

            }
            else if (dic[i].indice_horizontal[0]!='-' && dic[i].indice_vertical[0]=='-')
            {
                printf("%d-%s.\n",dic[i].id,dic[i].indice_horizontal);

            }
            else
            {
                printf("%d-%s.\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t%d-%s.\n",dic[i].id,dic[i].indice_horizontal,dic[i].id,dic[i].indice_vertical);
            }
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

Dictionnaire *generer_dictionnaire(Dictionnaire *dic, int n)
{
    Dictionnaire *d=malloc(sizeof(Dictionnaire));
    for (int i = 0; i < n; i++)
    {
        d[i].id=dic[i].id;
        strcpy(d[i].indice_horizontal,dic[i].indice_horizontal);
        strcpy(d[i].indice_vertical,dic[i].indice_vertical);
        strcpy(d[i].resultat_horizontal,"");
        strcpy(d[i].resultat_vertical,"");
    }
    return d;
}

Dictionnaire * remplacer_underscore_mots_dictionnaire(Dictionnaire *dic, int n)
{
    for (int i = 0; i < n; i++)
    {
        strcpy(dic[i].indice_horizontal,replace(dic[i].indice_horizontal,'_',' '));
        strcpy(dic[i].indice_vertical,replace(dic[i].indice_vertical,'_',' '));
    }
    return dic;
}

char *replace(char *ch,char c, char r)
{
    for (int i = 0; i < strlen(ch); i++)
    {
        if (ch[i]==c)
        {
            ch[i]=r;
        }
    }
    return ch;
}
