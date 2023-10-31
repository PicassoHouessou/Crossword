#include "crossword.h"


void run(Crossword **cw,int n,int nr,int nc,int niveau){
    char filename_dictionnaire[25];
    char filename_grille[25];
    int nbe;
    Crossword *c=malloc(sizeof(Crossword));
    switch (niveau)
    {
    case 1:
        strcpy(filename_dictionnaire,"assets/dictionnaires/facile.txt");
        strcpy(filename_grille,"assets/grilles/facile.txt");
        strcpy((c)->niveau,"facile");
        strcpy((*cw)->niveau,"facile");
        nbe=3;
        break;
    case 2:
        strcpy(filename_dictionnaire,"assets/dictionnaires/intermediaire.txt");
        strcpy(filename_grille,"assets/grilles/intermediaire.txt");
        strcpy((c)->niveau,"intermediaire");
        strcpy((*cw)->niveau,"intermediaire");
        nbe=2;
        break;
    case 3:
        strcpy(filename_dictionnaire,"assets/dictionnaires/difficile.txt");
        strcpy(filename_grille,"assets/grilles/difficile.txt");
        strcpy((c)->niveau,"diffcile");
        strcpy((*cw)->niveau,"diffcile");
        nbe=1;
        break;
    default:
        strcpy(filename_dictionnaire,"assets/dictionnaires/facile.txt");
        strcpy(filename_grille,"assets/grilles/facile.txt");
        strcpy((c)->niveau,"facile");
        strcpy((*cw)->niveau,"facile");
        nbe=3;
        break;
    }

    c->dictionnaire=load_dictionnaire(filename_dictionnaire,n);
    c->grille=load_grille(filename_grille,nr,nc);
    
    Dictionnaire *dic=remplacer_underscore_mots_dictionnaire(c->dictionnaire,n);
    (*cw)->dictionnaire=dic; 
    
    (*cw)->grille=generer_grille(c->grille,nr,nc);
    int k=0;
    while (k<n)
    {
        print_grille((*cw)->grille,nr,nc);
        printf("\n\n");
        print_dictionnaire((*cw)->dictionnaire,n);
        int choix;
        k==0?printf("\nEntrer votre choix :\t"):printf("\nEntrer un second choix :\t");
        scanf("%d",&choix);
        char response[15];
        printf("\nEntrer votre r%cponse form%c des lettres en majuscules :\t",130,130);
        
        scanf("%s",response);
        if (strcmp(response,(*cw)->dictionnaire[choix-1].indice_horizontal[0]!='-'?(c)->dictionnaire[choix-1].resultat_horizontal:(c)->dictionnaire[choix-1].resultat_vertical)!=0 )
        {
            int i=0;
            while (strcmp(response,(*cw)->dictionnaire[choix-1].indice_horizontal[0]!='-'?(c)->dictionnaire[choix-1].resultat_horizontal:(c)->dictionnaire[choix-1].resultat_vertical)!=0 && i<nbe)
            {
                i++;
                printf("\nEchec. Il vous reste %d %cssais possible\n",(nbe-i),130);
                printf("\nVeillez re-%cssayer :\t",130);
                scanf("%s",response);
                
            }
        }
        if (strcmp(response,(*cw)->dictionnaire[choix-1].indice_horizontal[0]!='-'?(c)->dictionnaire[choix-1].resultat_horizontal:(c)->dictionnaire[choix-1].resultat_vertical)==0)
        {
            printf("\nBravo.\n");
            if ((*cw)->dictionnaire[choix-1].indice_horizontal[0]!='-')
            {
                strcpy((*cw)->dictionnaire[choix-1].resultat_horizontal,response);
                int t,z;
                for (int i = 0; i < nr; i++)
                {
                    for (int j = 0; j < nc; j++)
                    {
                        if ((*cw)->grille[i][j].id==choix)
                        {
                            t=i;
                            z=j;
                            continue;
                        }
                    }
                }
                for (int i = z; i < z+strlen(response); i++)
                {
                    (*cw)->grille[t][i].caractere[0]=response[i-z];
                }
            }
            else
            {
                strcpy((*cw)->dictionnaire[choix-1].resultat_vertical,response);
                int t,z;
                for (int i = 0; i < nr; i++)
                {
                    for (int j = 0; j < nc; j++)
                    {
                        if ((*cw)->grille[i][j].id==choix)
                        {
                            t=i;
                            z=j;
                            continue;
                        }
                    }
                }
                for (int i = t; i < t+strlen(response); i++)
                {
                    (*cw)->grille[i][z].caractere[0]=response[i-t];
                }
            }
            
        }
        k++;
    }
    print_grille((*cw)->grille,nr,nc);
    printf("\n\n");
    print_dictionnaire((*cw)->dictionnaire,n);

}


void nouvelle_partie(Crossword **cw,int n,int nr,int nc,int nbe)
{
    run(cw,n,nr,nc,choix_niveau());
}

void reprendre_partie()
{
}

void sauvegarder_partie(Crossword *cw,int n,int nr,int nc)
{
    char filename_dictionnaire[50];
    char filename_grille[50];

    if (strcmp(cw->niveau,"facile")==0)
    {
        strcpy(filename_dictionnaire,"assets/sauvegardes/dictionnaire_facile.txt");
        strcpy(filename_grille,"assets/sauvegardes/grille_facile.txt");
    }
    else if(strcmp(cw->niveau,"intermediaire")==0)
    {
        strcpy(filename_dictionnaire,"assets/sauvegardes/dictionnaire_intermediaire.txt");
        strcpy(filename_grille,"assets/sauvegardes/grille_intermediaire.txt");
    }
    else
    {
        strcpy(filename_dictionnaire,"assets/sauvegardes/dictionnaire_difficile.txt");
        strcpy(filename_grille,"assets/sauvegardes/grille_difficile.txt");
    }
    FILE *f=NULL;
    FILE *f1=NULL;
    f=fopen(filename_dictionnaire,"w");
    f1=fopen(filename_grille,"w");
    if (f!=NULL && f1!=NULL)
    {
        fprintf(f,"%d\n",n);
        for (int i = 0; i < n; i++)
        {
            fprintf(f,"%d\t\t%s\t\t%s\t\t%s\t\t%s\n",cw->dictionnaire[i].id,cw->dictionnaire[i].indice_horizontal,cw->dictionnaire[i].indice_vertical,cw->dictionnaire[i].resultat_horizontal,cw->dictionnaire[i].resultat_vertical);
        }
        fprintf(f1,"%d\t\t%d\n",nr,nc);
        for (int i = 0; i < nr; i++)
        {
            for (int j = 0; j < nc; j++)
            {
                fprintf(f1,"%d\t%s\n",cw->grille[i][j].id,cw->grille[i][j].caractere);
            }
        }
        fclose(f);
        fclose(f1);
        return; 
    }
    return;
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
    fclose(f);
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
        fclose(f);
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
                printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t%d-%s.\n",dic[i].id,dic[i].indice_vertical);
            }
            else if (dic[i].indice_horizontal[0]!='-' && dic[i].indice_vertical[0]=='-')
            {
                printf("%d-%s.\n",dic[i].id,dic[i].indice_horizontal);
            }
            else
            {
                printf("%d-%s.\t\t\t\t\t\t\t\t\\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t%d-%s.\n",dic[i].id,dic[i].indice_horizontal,dic[i].id,dic[i].indice_vertical);
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

int choix_niveau()
{
    printf("\n1-Niveau facile.\n");
    printf("\n2-Niveau interm%cdiaire.\n",130);
    printf("\n3-Niveau difficile.\n");
    int choix;
    printf("\nEntrez votre choix :\t");
    scanf("%d",&choix);
    return choix;
}
