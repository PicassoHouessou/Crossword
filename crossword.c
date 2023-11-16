#include "crossword.h"

time_t secondes;

int isIn(int T[],int n,int ch){
    for (int i = 0; i < n; i++)
    {
        if (T[i]==ch)
        {
            return 1;
        }
    }
    return 0;
}

void run(Crossword **cw,Crossword *c,int nbe){
    int s=0;
    int k=0;
    int current[(*cw)->dictionnaire->dim];
    float manus=0.0;
    while (k<(*cw)->dictionnaire->dim)
    {
        print_grille((*cw)->g);
        printf("\n\n");
        print_dictionnaire((*cw)->dictionnaire);
        printf("\n0-sauvegarder la partie en cours.\n");
        int choix;
        
        k==0?printf("\nEntrer votre choix le nombre doit etre compris entre [0-%d]:\t",(*cw)->dictionnaire->dim):printf("\nEntrer un second choix le nombre doit etre compris entre [0-%d]:\t",(*cw)->dictionnaire->dim);
        scanf("%d",&choix);
        char response[25];
        if(choix==0)
        {
            time(&secondes);
            (*cw)->stat->heure_fin=*localtime(&secondes);
            (*cw)->stat->score=((float)s/(float)(*cw)->dictionnaire->dim);
            sauvegarder_partie(*cw);
            k=(*cw)->dictionnaire->dim;
            return;
        }
        else if (isIn(current,(*cw)->dictionnaire->dim,choix)==1)
        {
            printf("\nVous avez d%cja fait ce choix ou votre choix est indisponible %d.\n",130,choix);
            while (isIn(current,(*cw)->dictionnaire->dim,choix)==1)
            {
                printf("\nVeillez re-%cssayer le nombre doit etre compris entre [0-%d] :\t",130,(*cw)->dictionnaire->dim);
                scanf("%d",&choix);
                 
            }
            printf("\nEntrer votre r%cponse form%c des lettres en majuscules :\t",130,130);
            scanf("%s",response);
        }
        else
        {
            printf("\nEntrer votre r%cponse form%c des lettres en majuscules :\t",130,130);
            scanf("%s",response);
            int i=0;
            while (strcmp(response,(*cw)->dictionnaire[choix-1].indice_horizontal[0]!='-'?(c)->dictionnaire[choix-1].resultat_horizontal:(c)->dictionnaire[choix-1].resultat_vertical)!=0 && i<nbe)
            {
                i++;
                if (demande_aide()==1)
                {
                    if ((*cw)->dictionnaire[choix-1].indice_horizontal[0]!='-')
                    {
                        printf("\nLa r%cponse commence par %c et se termine par %c et contient %ld caract%cres en majuscule.\n",130,(c)->dictionnaire[choix-1].resultat_horizontal[0],(c)->dictionnaire[choix-1].resultat_horizontal[strlen((c)->dictionnaire[choix-1].resultat_horizontal)-1],strlen((c)->dictionnaire[choix-1].resultat_horizontal),138);
                    }
                    else
                    {
                        printf("\nLa r%cponse commence par %c et se termine par %c et contient %ld caract%cres en majuscule.\n",130,(c)->dictionnaire[choix-1].resultat_vertical[0],(c)->dictionnaire[choix-1].resultat_vertical[strlen((c)->dictionnaire[choix-1].resultat_vertical)-1],strlen((c)->dictionnaire[choix-1].resultat_vertical),138);
                    }
                    manus += 0.25;
                }
                
                printf("\nR%cponse incorrecte, votre r%cponse doit contenir uniquement des caract%cres entre A et Z. Il vous reste %d %cssais possible\n",130,130,138,(nbe-i)+1,130);
                printf("\nVeillez re-%cssayer une nouvelle r%cponse:\t",130,130);
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
                for (int i = 0; i < (*cw)->g->nombre_ligne; i++)
                {
                    for (int j = 0; j < (*cw)->g->nombre_colonne; j++)
                    {
                        if ((*cw)->g->grille[i][j].id==choix)
                        {
                            t=i;
                            z=j;
                            continue;
                        }
                    }
                }
                for (int i = z; i < z+strlen(response); i++)
                {
                    
                    (*cw)->g->grille[t][i].caractere=response[i-z];

                }
            }
            else
            {
                strcpy((*cw)->dictionnaire[choix-1].resultat_vertical,response);
                int t,z;
                for (int i = 0; i < (*cw)->g->nombre_ligne; i++)
                {
                    for (int j = 0; j < (*cw)->g->nombre_colonne; j++)
                    {
                        if ((*cw)->g->grille[i][j].id==choix)
                        {
                            t=i;
                            z=j;
                            continue;
                        }
                    }
                }
                for (int i = t; i < t+strlen(response); i++)
                {
                    
                    (*cw)->g->grille[i][z].caractere=response[i-t];
                }
            } 
        }
        current[k]=choix;
        k++;
    }
    printf("%.2f\n",manus);
    (*cw)->stat->score=((float)s/(float)(*cw)->dictionnaire->dim)-manus;
    print_grille((*cw)->g);
}


void nouvelle_partie(Crossword **cw)
{
    time(&secondes);
    (*cw)->stat=(Statistique*)malloc(sizeof(Statistique));
    (*cw)->stat->heure_debut=*localtime(&secondes);
    (*cw)->stat->score=0.0f;
    char filename_dictionnaire[50];
    char filename_grille[50];
    int nbe;
    Crossword *c=(Crossword*)malloc(sizeof(Crossword));
    switch (sujet())
    {
    case 1:
        strcpy(filename_dictionnaire,"dictionnaires/divers.txt");
        strcpy(filename_grille,"grilles/divers.txt");
        break;
    case 2:
        strcpy(filename_dictionnaire,"dictionnaires/education.txt");
        strcpy(filename_grille,"grilles/education.txt");
        break;
    default:
        strcpy(filename_dictionnaire,"dictionnaires/divers.txt");
        strcpy(filename_grille,"grilles/divers.txt");
        break;
    }
    switch (choix_niveau())
    {
    case 1:
        strcpy((*cw)->stat->niveau,"facile");
        nbe=3;
        break;
    case 2:
        strcpy((*cw)->stat->niveau,"intermediaire");
        nbe=2;
        break;
    case 3:
        strcpy((*cw)->stat->niveau,"diffcile");
        nbe=1;
        break;
    default:
        strcpy((*cw)->stat->niveau,"facile");
        nbe=3;
        break;
    }

    printf("\nEntrer votre nom :\t");
    (*cw)->u=malloc(sizeof(User));
    scanf("%s",(*cw)->u->username);
    c->dictionnaire=load_dictionnaire(filename_dictionnaire);
    c->g=load_grille(filename_grille);
    Dictionnaire *dic=remplacer_underscore_mots_dictionnaire(c->dictionnaire);
    (*cw)->dictionnaire=dic;
    (*cw)->g=generer_grille(c->g);
    print_grille((*cw)->g);
    (*cw)->stat->heure_fin=*localtime(&secondes);
    run(cw,c,nbe);
    (*cw)->stat->heure_fin=*localtime(&secondes);
}

void reprendre_partie(Crossword **cw)
{
    time(&secondes);
    (*cw)->stat=(Statistique*)malloc(sizeof(Statistique));
    (*cw)->stat->heure_debut=*localtime(&secondes);
    (*cw)->stat->score=0.0f;
    char filename_dictionnaire[100];
    char filename_grille[100];
    char filename[50];
    int nbe;
    Crossword *c=malloc(sizeof(Crossword));
    switch (sujet())
    {
    case 1:
        switch (choix_niveau())
        {
        case 1:
            strcpy(filename_dictionnaire,"sauvegardes/divers/dictionnaires/facile.txt");
            strcpy(filename_grille,"sauvegardes/divers/grilles/facile.txt");
            strcpy(filename,"grilles/divers.txt");
            strcpy((*cw)->stat->niveau,"facile");
            nbe=3;
            break;
        case 2:
            strcpy(filename_dictionnaire,"sauvegardes/divers/dictionnaires/intermediaire.txt");
            strcpy(filename_grille,"sauvegardes/divers/grilles/intermediaire.txt");
            strcpy(filename,"grilles/divers.txt");
            strcpy((*cw)->stat->niveau,"intermediaire");
            nbe=2;
            break;
        case 3:
            strcpy(filename_dictionnaire,"sauvegardes/divers/dictionnaires/difficile.txt");
            strcpy(filename_grille,"sauvegardes/divers/grilles/difficile.txt");
            strcpy(filename,"grilles/divers.txt");
            strcpy((*cw)->stat->niveau,"difficile");
            nbe=1;
            break;
        default:
            strcpy(filename_dictionnaire,"sauvegardes/divers/dictionnaires/facile.txt");
            strcpy(filename_grille,"sauvegardes/divers/grilles/facile.txt");
            strcpy(filename,"grilles/divers.txt");
            strcpy((*cw)->stat->niveau,"facile");
            nbe=3;
            break;
        }
        break;
    case 2:
        switch (choix_niveau())
        {
        case 1:
            strcpy(filename_dictionnaire,"sauvegardes/education/dictionnaires/facile.txt");
            strcpy(filename_grille,"sauvegardes/education/grilles/facile.txt");
            strcpy(filename,"grilles/education.txt");
            strcpy((*cw)->stat->niveau,"facile");
            nbe=3;
            break;
        case 2:
            strcpy(filename_dictionnaire,"sauvegardes/education/dictionnaires/intermediaire.txt");
            strcpy(filename_grille,"sauvegardes/education/grilles/intermediaire.txt");
            strcpy(filename,"grilles/education.txt");
            strcpy((*cw)->stat->niveau,"intermediaire");
            nbe=2;
            break;
        case 3:
            strcpy(filename_dictionnaire,"sauvegardes/education/dictionnaires/difficile.txt");
            strcpy(filename_grille,"sauvegardes/education/grilles/difficile.txt");
            strcpy(filename,"grilles/divers.txt");
            strcpy((*cw)->stat->niveau,"difficile");
            nbe=1;
            break;
        default:
            strcpy(filename_dictionnaire,"sauvegardes/education/dictionnaires/facile.txt");
            strcpy(filename_grille,"sauvegardes/education/grilles/facile.txt");
            strcpy(filename,"grilles/education.txt");
            strcpy((*cw)->stat->niveau,"facile");
            nbe=3;
            break;
        }
        break;
    default:
        switch (choix_niveau())
        {
        case 1:
            strcpy(filename_dictionnaire,"sauvegardes/divers/dictionnaires/facile.txt");
            strcpy(filename_grille,"sauvegardes/divers/grilles/facile.txt");
            strcpy(filename,"grilles/divers.txt");
            strcpy((*cw)->stat->niveau,"facile");
            nbe=3;
            break;
        case 2:
            strcpy(filename_dictionnaire,"sauvegardes/divers/dictionnaires/intermediaire.txt");
            strcpy(filename_grille,"sauvegardes/divers/grilles/intermediaire.txt");
            strcpy(filename,"grilles/divers.txt");
            strcpy((*cw)->stat->niveau,"intermediaire");
            nbe=2;
            break;
        case 3:
            strcpy(filename_dictionnaire,"sauvegardes/divers/dictionnaires/difficile.txt");
            strcpy(filename_grille,"sauvegardes/divers/grilles/difficile.txt");
            strcpy(filename,"grilles/divers.txt");
            strcpy((*cw)->stat->niveau,"difficile");
            nbe=1;
            break;
        default:
            strcpy(filename_dictionnaire,"sauvegardes/divers/dictionnaires/facile.txt");
            strcpy(filename_grille,"sauvegardes/divers/grilles/facile.txt");
            strcpy(filename,"grilles/divers.txt");
            strcpy((*cw)->stat->niveau,"facile");
            nbe=3;
            break;
        }
        break;
    }
    c->dictionnaire=load_dictionnaire(filename_dictionnaire);
    c->g=load_grille(filename);
    Dictionnaire *dic=remplacer_underscore_mots_dictionnaire(c->dictionnaire);
    (*cw)->dictionnaire=dic; 
    (*cw)->g=load_grille(filename_grille);
    run(cw,c,nbe);
    (*cw)->stat->heure_fin=*localtime(&secondes);
}

void sauvegarder_partie(Crossword *cw)
{
    char filename_dictionnaire[50];
    char filename_grille[50];
    if (strcmp(cw->g->niveau,"facile")==0)
    {
        strcpy(filename_dictionnaire,"sauvegardes/dictionnaire_facile.txt");
        strcpy(filename_grille,"sauvegardes/grille_facile.txt");
    }
    else if(strcmp(cw->g->niveau,"intermediaire")==0)
    {
        strcpy(filename_dictionnaire,"sauvegardes/dictionnaire_intermediaire.txt");
        strcpy(filename_grille,"sauvegardes/grille_intermediaire.txt");
    }
    else
    {
        strcpy(filename_dictionnaire,"sauvegardes/dictionnaire_difficile.txt");
        strcpy(filename_grille,"sauvegardes/grille_difficile.txt");
    }
    FILE *f=NULL;
    FILE *f1=NULL;
    FILE *f2=NULL;
    cw->dictionnaire=remplacer_espace_mots_dictionnaire(cw->dictionnaire);
    f=fopen(filename_dictionnaire,"w");
    f1=fopen(filename_grille,"w");
    f2=fopen("statistique/stat.txt","a+");
    if (f!=NULL && f1!=NULL&& f2!=NULL)
    {
        fprintf(f,"%d\n",cw->dictionnaire->dim);
        for (int i = 0; i < cw->dictionnaire->dim; i++)
        {
            fprintf(f,"%d\t\t%s\t\t%s\t\t%s\t\t%s\n",cw->dictionnaire[i].id,cw->dictionnaire[i].indice_horizontal,cw->dictionnaire[i].indice_vertical,cw->dictionnaire[i].resultat_horizontal,cw->dictionnaire[i].resultat_vertical);
        }
        fprintf(f1,"%d %d %s\n",cw->g->nombre_ligne,cw->g->nombre_colonne,cw->g->niveau);
        for (int i = 0; i < cw->g->nombre_ligne; i++)
        {
            for (int j = 0; j < cw->g->nombre_colonne; j++)
            {
                if (cw->g->grille[i][j].caractere==' ')
                {
                   
                    cw->g->grille[i][j].caractere='?';
                }
                fprintf(f1,"%d  %c\n",cw->g->grille[i][j].id,cw->g->grille[i][j].caractere);
            }
        }
        fprintf(f2,"%s  %s  %f %d  %d  %d %d  %d  %d  %d  %d\n",cw->u->username,cw->stat->niveau,cw->stat->score,cw->stat->heure_debut.tm_mday,cw->stat->heure_debut.tm_mon,cw->stat->heure_debut.tm_hour,cw->stat->heure_debut.tm_min,cw->stat->heure_debut.tm_sec,cw->stat->heure_fin.tm_hour,cw->stat->heure_fin.tm_min,cw->stat->heure_fin.tm_sec);
        fclose(f);
        fclose(f1);
        fclose(f2);
    }
    else
    {
        return;
    }
}


Grille *load_grille(char *filename)
{
    printf("%s",filename);
    Grille *g=(Grille*)malloc(sizeof(Grille));
    FILE *f=fopen(filename,"r");

    fscanf(f,"%d %d %s",&g->nombre_ligne,&g->nombre_colonne,g->niveau);
    int size=g->nombre_ligne*g->nombre_colonne+1;
    printf("%d ,%d",g->nombre_ligne,g->nombre_colonne);
    Cellule *vec=(Cellule*)malloc(sizeof(Cellule)*size);
    int k=0;
    while (fscanf(f,"%d %c",&vec[k].id,&vec[k].caractere)!=EOF)
    {
        k++;
    }
    k=0;
    Cellule** grille=malloc(sizeof(Cellule)*g->nombre_ligne);
    for (int i = 0; i < g->nombre_ligne; i++)
    {
        grille[i]=malloc(sizeof(Cellule)*g->nombre_colonne);
        for (int j = 0; j < g->nombre_colonne; j++)
        {
            grille[i][j].id=vec[k].id;
            
            grille[i][j].caractere=vec[k].caractere;
            k++;
        }
    }
    g->grille=grille;
    fclose(f);
    return g;
}


Dictionnaire *load_dictionnaire(char *filename)
{
    
    FILE *f=NULL;
    Dictionnaire *dic=NULL;
    f=fopen(filename,"r");
    if(f==NULL){
        printf("\nOuverture impossible\n");
        return NULL;
    }
    else
    {
        int dim;
        fscanf(f,"%d\n",&dim);
        dic=(Dictionnaire *)malloc(sizeof(Dictionnaire)*dim);
        dic->dim=dim;
        int i=0;
        while (fscanf(f,"%d  %s  %s  %s  %s",&dic[i].id,dic[i].indice_horizontal,dic[i].indice_vertical,dic[i].resultat_horizontal,dic[i].resultat_vertical)!=EOF && i<dim)
        {
            i++;
        }
        fclose(f);
    }
    return dic;
}


void print_grille(Grille *g)
{
    if (g->grille!=NULL)
    {
        for (int i = 0; i < g->nombre_ligne; i++)
        {
            printf("\n");
            for (int j = 0; j <  g->nombre_colonne; j++)
            {
                if (g->grille[i][j].id!=0)
                {
                    printf("|%d %c|\t",g->grille[i][j].id,g->grille[i][j].caractere);
                }
                else
                {
                    printf("  |%c|\t",g->grille[i][j].caractere);
                }
            }
            printf("\n");
        }
    }
    return;
}


void print_dictionnaire(Dictionnaire * dic)
{
    if (dic!=NULL)
    {
        printf("\n\tHorizontal\t\t\t\t\t\t\t\t\t\t\t\t\tVertical\n");
        for (int i = 0; i < dic->dim; i++)
        {
            if (dic[i].indice_horizontal[0]=='-' && dic[i].indice_vertical[0]!='-')
            {
                printf("\t\t\t\t\t\t\t\t\t\t\t%d-%s.\n",dic[i].id,dic[i].indice_vertical);
            }
            else if (dic[i].indice_horizontal[0]!='-' && dic[i].indice_vertical[0]=='-')
            {
                printf("%d-%s.\n",dic[i].id,dic[i].indice_horizontal);
            }
            else
            {
                printf("%d-%s.\t\t\t\t\t\t\t\t\t\t%d-%s.\n",dic[i].id,dic[i].indice_horizontal,dic[i].id,dic[i].indice_vertical);
            }
        }
    }
    return;
}



void free_Memory(Crossword **cw){
    
    if ((*cw)!=NULL)
    {
        for (int i = 0; i < (*cw)->g->nombre_ligne; i++)
        {
           free((*cw)->g->grille[i]);
        }
        free((*cw)->dictionnaire);
        free((*cw)->stat);
        free((*cw)->g);
        free(*cw);
    }
    return;
}

Grille *generer_grille(Grille *g)
{
    Grille * gril=malloc(sizeof(Grille));
    Cellule** cel=malloc(sizeof(Cellule)*g->nombre_ligne);
    for (int i = 0; i < g->nombre_ligne; i++)
    {
        cel[i]=malloc(sizeof(Cellule)*g->nombre_colonne);
        for (int j = 0; j < g->nombre_colonne; j++)
        {
            cel[i][j].id=g->grille[i][j].id;
            
            cel[i][j].caractere=g->grille[i][j].caractere=='*'?g->grille[i][j].caractere:' ';

        }
    }
    gril->grille=cel;
    gril->nombre_ligne=g->nombre_ligne;
    gril->nombre_colonne=g->nombre_colonne;
    strcpy(gril->niveau,g->niveau);
    return gril;
}


Dictionnaire * remplacer_underscore_mots_dictionnaire(Dictionnaire *dic)
{
    for (int i = 0; i < dic->dim; i++)
    {
        strcpy(dic[i].indice_horizontal,replace(dic[i].indice_horizontal,'_',' '));
        strcpy(dic[i].indice_vertical,replace(dic[i].indice_vertical,'_',' '));
    }
    return dic;
}

Dictionnaire *remplacer_espace_mots_dictionnaire(Dictionnaire *dic)
{
    for (int i = 0; i < dic->dim; i++)
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
    printf("\n\n");
    return choix;
}

int menu()
{
    printf("\n\n Menu du jeu.\n\n");
    printf("\n1-Nouvelle partie.\n");
    printf("\n2-Reprendre une partie.\n");
    printf("\n3-Sauvegarder une partie.\n");
    printf("\n4-Statistique.\n");
    printf("\n5-Quitter une partie.\n");
    int choix;
    printf("\nEntrer votre choix :\t");
    scanf("%d",&choix);
    printf("\n\n");

    return choix;
}

int demande_aide()
{
    printf("\nToute aide est %cquivalent a un manu de 0.25 de votre score avant la demande d'aide.\n",130);
    printf("\n1-Avoir de l'aide.\n");
    printf("\nEntrer votre choix:\t");
    int choix;
    scanf("%d",&choix);
    if (choix==1)
    {
        return 1;
    }
    return 0;
}

int sujet()
{
    printf("\nChoix du sujet.\n");
    printf("\n1-Divers.\n");
    printf("\n2-Education.\n");
    int choix;
    printf("\nEntrer votre choix:\t");
    scanf("%d",&choix);
    if (choix>=1 || choix<=2)
    {
        return choix;
    }
    return 0;
}

void statistique(){
    FILE *f=NULL;
    f=fopen("statistique/stat.txt","r");
    if (f!=NULL)
    {
        char niveau[15];
        int h1,h2,m1,m2,s1,s2,m,d;
        char name[25];
        char username[25];
        printf("\nEntrer votre nom d'utilisateur:\t");
        scanf("%s",name);
        float score;
        printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
        printf("Niveau\t\t|\t\tScore\t\t|\t\t\tDate\t\t|\t\t\tHeure de D%cbut\t\t|\t\tHeure de Fin\n",130);
        printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
        while (fscanf(f,"%s %s %f %d %d %d %d %d %d %d %d",username,niveau,&score,&d,&m,&h1,&m1,&s1,&h2,&m2,&s2)!=EOF)
        {
            if (strcmp(username,name)==0)
            {
                printf("\n%s\t\t|\t\t%.2f\t\t|\t\t%d/%d\t\t|\t\t\t%d:%d:%d\t\t|\t\t\t%d:%d:%d\n",niveau,(score*100),d,m,h1,m1,s1,h2,m2,s2);
                printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
            }
            
        }
        fclose(f);
    }
    return;
}