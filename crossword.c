#include "crossword.h"


void run(Crossword **cw,Crossword *c,int n,int nr,int nc,int nbe){ 
    int s=0;
    int k=0;
    while (k<n)
    {
        print_grille((*cw)->grille,nr,nc);
        printf("\n\n");
        print_dictionnaire((*cw)->dictionnaire,n);
        printf("\n0-sauvegarder la partie en cours.\n");
        int choix;
        k==0?printf("\nEntrer votre choix :\t"):printf("\nEntrer un second choix :\t");
        scanf("%d",&choix);
        char response[15];
        printf("\nEntrer votre r%cponse form%c des lettres en majuscules :\t",130,130);
        scanf("%s",response);
        if(choix==0)
        {
            sauvegarder_partie(*cw);
            (*cw)->stat->heure_fin=*localtime(&secondes);
            sauvegarder_statistique((*cw)->stat);
            return;
        }
        else if (strcmp(response,(*cw)->dictionnaire[choix-1].indice_horizontal[0]!='-'?(c)->dictionnaire[choix-1].resultat_horizontal:(c)->dictionnaire[choix-1].resultat_vertical)!=0 )
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
            s++;
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
    (*cw)->stat->score +=(s/n);
    print_grille((*cw)->grille,nr,nc);
    printf("\n\n");
    print_dictionnaire((*cw)->dictionnaire,n);
}

void nouvelle_partie(Crossword **cw)
{
    time_t secondes;
    time(&secondes);
    (*cw)->stat=malloc(sizeof(Statistique));
    (*cw)->stat->heure_debut=*localtime(&secondes);
    (*cw)->stat->score=0.0f;
    char filename_dictionnaire[25];
    char filename_grille[25];
    int nbe,n,nr,nc;
    Crossword *c=malloc(sizeof(Crossword));
    switch (choix_niveau())
    {
    case 1:
        strcpy(filename_dictionnaire,"dictionnaires/facile.txt");
        strcpy(filename_grille,"grilles/facile.txt");
        strcpy((c)->niveau,"facile");
        strcpy((*cw)->niveau,"facile");
        nr=FACILE_NROW;
        nc=FACILE_NCOL;
        n=FACILE_DIC_SIZE;
        strcpy((*cw)->stat->niveau,"facile");
        nbe=3;
        break;
    case 2:
        strcpy(filename_dictionnaire,"dictionnaires/intermediaire.txt");
        strcpy(filename_grille,"grilles/intermediaire.txt");
        strcpy((c)->niveau,"intermediaire");
        strcpy((*cw)->niveau,"intermediaire");
        strcpy((*cw)->stat->niveau,"intermediaire");
        nr=INTER_NROW;
        nc=INTER_NCOL;
        n=INTER_DIC_SIZE;
        nbe=2;
        break;
    case 3:
        strcpy(filename_dictionnaire,"dictionnaires/difficile.txt");
        strcpy(filename_grille,"grilles/difficile.txt");
        strcpy((c)->niveau,"diffcile");
        strcpy((*cw)->niveau,"diffcile");
        strcpy((*cw)->stat->niveau,"diffcile");
        nr=DIFFICILE_NROW;
        nc=DIFFICILE_NCOL;
        n=DIFFICILE_DIC_SIZE;
        nbe=1;
        break;
    default:
        strcpy(filename_dictionnaire,"dictionnaires/facile.txt");
        strcpy(filename_grille,"grilles/facile.txt");
        strcpy((c)->niveau,"facile");
        strcpy((*cw)->niveau,"facile");
        strcpy((*cw)->stat->niveau,"facile");
        nr=FACILE_NROW;
        nc=FACILE_NCOL;
        n=FACILE_DIC_SIZE;
        nbe=3;
        break;
    }
    c->dictionnaire=load_dictionnaire(filename_dictionnaire,n);
    c->grille=load_grille(filename_grille,nr,nc);
    Dictionnaire *dic=remplacer_underscore_mots_dictionnaire(c->dictionnaire,n);
    (*cw)->dictionnaire=dic; 
    (*cw)->grille=generer_grille(c->grille,nr,nc);
    run(cw,c,n,nr,nc,nbe);
    (*cw)->stat->heure_fin=*localtime(&secondes);
}

void sauvegarder_statistique(Statistique *stat){
    FILE *f=NULL;
    f=fopen("statistique/stat.txt","w");
    if (f!=NULL)
    {
        fprintf(f,"%s  %.4f %d  %d  %d  %d  %d  %d",stat->niveau,stat->score,stat->heure_debut.tm_hour,stat->heure_debut.tm_min,stat->heure_debut.tm_sec,stat->heure_fin.tm_hour,stat->heure_fin.tm_min,stat->heure_fin.tm_sec);
        fclose(f);
    }
    else
    {
        exit(EXIT_FAILURE);
    }
}

void reprendre_partie(Crossword **cw)
{
    time(&secondes);
    (*cw)->stat=(Statistique*)malloc(sizeof(Statistique));
    (*cw)->stat->heure_debut=*localtime(&secondes);
    (*cw)->stat->score=0.0f;
    char filename_dictionnaire[50];
    char filename_grille[50];
    char filename[50];
    int nbe,n,nr,nc;
    Crossword *c=malloc(sizeof(Crossword));
    switch (choix_niveau())
    {
    case 1:
        strcpy(filename_dictionnaire,"sauvegardes/dictionnaire_facile.txt");
        strcpy(filename_grille,"sauvegardes/grille_facile.txt");
        strcpy(filename,"grilles/facile.txt");
        strcpy((c)->niveau,"facile");
        strcpy((*cw)->niveau,"facile");
        nr=FACILE_NROW;
        nc=FACILE_NCOL;
        n=FACILE_DIC_SIZE;
        strcpy((*cw)->stat->niveau,"facile");
        nbe=3;
        break;
    case 2:
        strcpy(filename_dictionnaire,"sauvegardes/dictionnaire_intermediaire.txt");
        strcpy(filename_grille,"sauvegardes/grille_intermediaire.txt");
        strcpy(filename,"grilles/intermediaire.txt");
        strcpy((c)->niveau,"intermediaire");
        strcpy((*cw)->niveau,"intermediaire");
        strcpy((*cw)->stat->niveau,"intermediaire");
        nr=INTER_NROW;
        nc=INTER_NCOL;
        n=INTER_DIC_SIZE;
        nbe=2;
        break;
    case 3:
        strcpy(filename_dictionnaire,"sauvegardes/dictionnaire_difficile.txt");
        strcpy(filename_grille,"sauvegardes/grille_difficile.txt");
        strcpy(filename,"grilles/difficile.txt");
        strcpy((c)->niveau,"difficile");
        strcpy((*cw)->niveau,"difficile");
        strcpy((*cw)->stat->niveau,"difficile");
        nr=DIFFICILE_NROW;
        nc=DIFFICILE_NCOL;
        n=DIFFICILE_DIC_SIZE;
        nbe=1;
        break;
    default:
        strcpy(filename_dictionnaire,"sauvegardes/dictionnaire_facile.txt");
        strcpy(filename_grille,"sauvegardes/grille_facile.txt");
        strcpy(filename,"grilles/facile.txt");
        strcpy((c)->niveau,"facile");
        strcpy((*cw)->niveau,"facile");
        strcpy((*cw)->stat->niveau,"facile");
        nr=FACILE_NROW;
        nc=FACILE_NCOL;
        n=FACILE_DIC_SIZE;
        nbe=3;
        break;
    }
    c->dictionnaire=load_dictionnaire(filename_dictionnaire,n);
    c->grille=load_grille(filename,nr,nc);
    Dictionnaire *dic=remplacer_underscore_mots_dictionnaire(c->dictionnaire,n);
    (*cw)->dictionnaire=dic; 
    (*cw)->grille=load_grille(filename_grille,nr,nc);
    run(cw,c,n,nr,nc,nbe);
    (*cw)->stat->heure_fin=*localtime(&secondes);
}

void sauvegarder_partie(Crossword *cw)
{
    int n,nr,nc;
    char filename_dictionnaire[50];
    char filename_grille[50];
    if (strcmp(cw->niveau,"facile")==0)
    {
        strcpy(filename_dictionnaire,"sauvegardes/dictionnaire_facile.txt");
        strcpy(filename_grille,"sauvegardes/grille_facile.txt");
        nr=FACILE_NROW;
        nc=FACILE_NCOL;
        n=FACILE_DIC_SIZE;
    }
    else if(strcmp(cw->niveau,"intermediaire")==0)
    {
        strcpy(filename_dictionnaire,"sauvegardes/dictionnaire_intermediaire.txt");
        strcpy(filename_grille,"sauvegardes/grille_intermediaire.txt");
        nr=INTER_NROW;
        nc=INTER_NCOL;
        n=INTER_DIC_SIZE;
    }
    else
    {
        strcpy(filename_dictionnaire,"sauvegardes/dictionnaire_difficile.txt");
        strcpy(filename_grille,"sauvegardes/grille_difficile.txt");
        nr=DIFFICILE_NROW;
        nc=DIFFICILE_NCOL;
        n=DIFFICILE_DIC_SIZE;
    }
    FILE *f=NULL;
    FILE *f1=NULL;
    cw->dictionnaire=remplacer_espace_mots_dictionnaire(cw->dictionnaire,n);
    f=fopen(filename_dictionnaire,"w");
    f1=fopen(filename_grille,"w");
    if (f!=NULL && f1!=NULL)
    {
        for (int i = 0; i < n; i++)
        {
            fprintf(f,"%d\t\t%s\t\t%s\t\t%s\t\t%s\n",cw->dictionnaire[i].id,cw->dictionnaire[i].indice_horizontal,cw->dictionnaire[i].indice_vertical,cw->dictionnaire[i].resultat_horizontal,cw->dictionnaire[i].resultat_vertical);
        }
        for (int i = 0; i < nr; i++)
        {
            for (int j = 0; j < nc; j++)
            {
                if (strcmp(cw->grille[i][j].caractere," ")==0)
                {
                    strcpy(cw->grille[i][j].caractere,"-");
                }
                fprintf(f1,"%d  %s\n",cw->grille[i][j].id,cw->grille[i][j].caractere);
            }
        }
        fclose(f);
        fclose(f1);
    }
    else
    {
        return;
    }
}

Cellule **load_grille(char *filename,int nr,int nc)
{
    Cellule ** grille=grille=malloc(sizeof(Cellule)*nr);
    FILE *f=fopen(filename,"r");

    int size=nr*nc;
    Cellule *vec=(Cellule*)malloc(sizeof(Cellule)*size);
    int k=0;
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
                    printf("  |%s|\t",cel[i][j].caractere);
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


void free_Memory(Crossword **cw){
    int nr;
    if (strcmp((*cw)->niveau,"facile")==0)
    {
        nr=FACILE_NROW;
    }
    else if (strcmp((*cw)->niveau,"intermedaire")==0)
    {
        nr=INTER_NROW;
    }
    else
    {
        nr=DIFFICILE_NROW;
    }
    
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

Dictionnaire *remplacer_espace_mots_dictionnaire(Dictionnaire *dic, int n)
{
    for (int i = 0; i < n; i++)
    {
        strcpy(dic[i].indice_horizontal,replace(dic[i].indice_horizontal,' ','_'));
        strcpy(dic[i].indice_vertical,replace(dic[i].indice_vertical,' ','_'));
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
    printf("\n\n Choix du niveau de difficult%c.\n\n",130);
    printf("\n1-Niveau facile.\n");
    printf("\n2-Niveau interm%cdiaire.\n",130);
    printf("\n3-Niveau difficile.\n");
    int choix;
    printf("\nEntrez votre choix :\t");
    scanf("%d",&choix);
    return choix;
}

int menu()
{
    printf("\n\n Menu du jeu.\n\n",130);
    printf("\n1-Nouvelle partie.\n");
    printf("\n2-Reprendre une partie.\n");
    printf("\n3-Sauvegarder une partie.\n");
    printf("\n4-Statistique.\n");
    printf("\n5-Quitter une partie.\n");
    int choix;
    printf("Entrer votre choix :\t");
    scanf("%d",&choix);
    return choix;
}

void statistique(){
    FILE *f=NULL;
    f=fopen("statistique/stat.txt","r");
    if (f!=NULL)
    {
        char niveau[15];
        int h1,h2,m1,m2,s1,s2;
        float score;
        while (fscanf(f,"%s  %.4f  %d  %d  %d  %d  %d  %d",niveau,&score,&h1,&m1,&s1,&h2,&m2,&s2)!=EOF)
        {
            printf("\n%s\t\t\t\t\t\t%.2f\t\t\t\t\t\t%d:%d:%d\t\t\t\t\t\t%d:%d:%d\n",niveau,score*100,h1,m1,s1,h2,m2,s2);
        }
        fclose(f);
    }
    return;
}