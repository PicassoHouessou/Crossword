#include "crossword.h"

time_t secondes;


/*
    fonction qui permet de vérifier si un entier est contenu dans un tableau d'entiers
*/
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


/*
    fonction qui contient le déroulement du jeu
*/
void run(Crossword **cw,Crossword *c,int nbe,char *filename,char *str){
    int s=0;
    int k=0;
    int* current=strcmp(str," ")==0?malloc(sizeof(int)*(*cw)->dictionnaire->dim):load_choix((*cw)->dictionnaire->dim,filename);
    float manus=0.0f;
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
            (*cw)->stat->score += ((float)s/(float)(*cw)->dictionnaire->dim)-manus;
            sauvegarder_partie((*cw));
            sauvegarder_choix(current,(*cw)->dictionnaire->dim,filename);
            k=(*cw)->dictionnaire->dim;
            return;
        }
        else if (isIn(current,(*cw)->dictionnaire->dim,choix)==1)
        {
            printf("\nVous avez deja fait ce choix ou votre choix est indisponible %d.\n",choix);
            while (isIn(current,(*cw)->dictionnaire->dim,choix)==1)
            { 
                printf("\nVeillez re-essayer le nombre doit etre compris entre [0-%d] :\t",(*cw)->dictionnaire->dim);
                scanf("%d",&choix);
                if(choix==0)
                {
                    time(&secondes);
                    (*cw)->stat->heure_fin=*localtime(&secondes);
                    (*cw)->stat->score += ((float)s/(float)(*cw)->dictionnaire->dim)-manus;
                    sauvegarder_partie((*cw));
                    sauvegarder_choix(current,(*cw)->dictionnaire->dim,filename);
                    k=(*cw)->dictionnaire->dim;
                    return;
                } 
            }
            printf("\nEntrer votre reponse forme des lettres en majuscules :\t");
            scanf("%s",response);
        }
        else
        {
            printf("\nEntrer votre reponse forme des lettres en majuscules :\t");
            scanf("%s",response);
            printf("\n%s\n",response);
            int i=0;
            while (strcmp(response,(*cw)->dictionnaire[choix-1].indice_horizontal[0]!='-'?(c)->dictionnaire[choix-1].resultat_horizontal:(c)->dictionnaire[choix-1].resultat_vertical)!=0 && i<nbe)
            {
                i++;
                if (demande_aide()==1)
                {
                    if ((*cw)->dictionnaire[choix-1].indice_horizontal[0]!='-')
                    {
                        printf("\nLa reponse commence par %c et se termine par %c et contient %ld caracteres en majuscule.\n",(c)->dictionnaire[choix-1].resultat_horizontal[0],(c)->dictionnaire[choix-1].resultat_horizontal[strlen((c)->dictionnaire[choix-1].resultat_horizontal)-1],strlen((c)->dictionnaire[choix-1].resultat_horizontal));
                    }
                    else
                    {
                        printf("\nLa reponse commence par %c et se termine par %c et contient %ld caracteres en majuscule.\n",(c)->dictionnaire[choix-1].resultat_vertical[0],(c)->dictionnaire[choix-1].resultat_vertical[strlen((c)->dictionnaire[choix-1].resultat_vertical)-1],strlen((c)->dictionnaire[choix-1].resultat_vertical));
                    }
                    manus += (float)1/(float)((*cw)->dictionnaire->dim*6);
                }
                printf("\nReponse incorrecte, votre reponse doit contenir uniquement des caracteres entre A et Z. Il vous reste %d essais possible\n",(nbe-i)+1);
                printf("\nVeillez re-essayer une nouvelle reponse:\t");
                scanf("%s",response);
            }
        }
        if (strcmp(response,(*cw)->dictionnaire[choix-1].indice_horizontal[0]!='-'?(c)->dictionnaire[choix-1].resultat_horizontal:(c)->dictionnaire[choix-1].resultat_vertical)==0)
        {
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
        current[k]=current[k]==0?choix:current[k];
        k++;
    }
    (*cw)->stat->score += (float)(((float)s/(float)(*cw)->dictionnaire->dim)-manus);
    print_grille((*cw)->g);
}



/*
   fonction pour lancer une nouvelle partie
*/
void nouvelle_partie(Crossword **cw)
{
    time(&secondes);
    (*cw)->stat=(Statistique*)malloc(sizeof(Statistique));
    (*cw)->stat->heure_debut=*localtime(&secondes);
    (*cw)->stat->score=0.0f;
    char filename_dictionnaire[50];
    char filename_grille[50];
    char filename[60];
    char str[2]=" ";
    int nbe;
    Crossword *c=(Crossword*)malloc(sizeof(Crossword));
    switch (sujet())
    {
    case 1:
        switch (choix_niveau())
        {
        case 1:
            strcpy((*cw)->stat->niveau,"facile");
            strcpy(filename,"sauvegardes/divers/grilles/facile_choix.txt");
            nbe=3;
            break;
        case 2:
            strcpy((*cw)->stat->niveau,"intermediaire");
            strcpy(filename,"sauvegardes/divers/grilles/intermediaire_choix.txt");
            nbe=2;
            break;
        case 3:
            strcpy((*cw)->stat->niveau,"diffcile");
            strcpy(filename,"sauvegardes/divers/grilles/difficile_choix.txt");
            nbe=1;
            break;
        default:
            strcpy((*cw)->stat->niveau,"facile");
            strcpy(filename,"sauvegardes/divers/grilles/facile_choix.txt");
            nbe=3;
            break;
        }
        strcpy(filename_dictionnaire,"dictionnaires/divers.txt");
        strcpy(filename_grille,"grilles/divers.txt");
        strcpy((*cw)->sujet,"divers");
        break;
    case 2:
        switch (choix_niveau())
        {
        case 1:
            strcpy((*cw)->stat->niveau,"facile");
            strcpy(filename,"sauvegardes/education/grilles/facile_choix.txt");
            nbe=3;
            break;
        case 2:
            strcpy((*cw)->stat->niveau,"intermediaire");
            strcpy(filename,"sauvegardes/education/grilles/intermediaire_choix.txt");
            nbe=2;
            break;
        case 3:
            strcpy((*cw)->stat->niveau,"diffcile");
            strcpy(filename,"sauvegardes/education/grilles/difficile_choix.txt");
            nbe=1;
            break;
        default:
            strcpy((*cw)->stat->niveau,"facile");
            strcpy(filename,"sauvegardes/education/grilles/facile_choix.txt");
            nbe=3;
            break;
        }
        strcpy(filename_dictionnaire,"dictionnaires/education.txt");
        strcpy(filename_grille,"grilles/education.txt");
        strcpy((*cw)->sujet,"education");
        break;
    case 3:
        switch (choix_niveau())
        {
        case 1:
            strcpy((*cw)->stat->niveau,"facile");
            strcpy(filename,"sauvegardes/medecine/grilles/facile_choix.txt");
            nbe=3;
            break;
        case 2:
            strcpy((*cw)->stat->niveau,"intermediaire");
            strcpy(filename,"sauvegardes/medecine/grilles/intermediaire_choix.txt");
            nbe=2;
            break;
        case 3:
            strcpy((*cw)->stat->niveau,"diffcile");
            strcpy(filename,"sauvegardes/medecine/grilles/difficile_choix.txt");
            nbe=1;
            break;
        default:
            strcpy((*cw)->stat->niveau,"facile");
            strcpy(filename,"sauvegardes/medecine/grilles/facile_choix.txt");
            nbe=3;
            break;
        }
        strcpy(filename_dictionnaire,"dictionnaires/medecine.txt");
        strcpy(filename_grille,"grilles/medecine.txt");
        strcpy((*cw)->sujet,"medecine");
        break;
    default:
        switch (choix_niveau())
        {
        case 1:
            strcpy((*cw)->stat->niveau,"facile");
            strcpy(filename,"sauvegardes/divers/grilles/facile_choix.txt");
            nbe=3;
            break;
        case 2:
            strcpy((*cw)->stat->niveau,"intermediaire");
            strcpy(filename,"sauvegardes/divers/grilles/intermediaire_choix.txt");
            nbe=2;
            break;
        case 3:
            strcpy((*cw)->stat->niveau,"diffcile");
            strcpy(filename,"sauvegardes/divers/grilles/difficile_choix.txt");
            nbe=1;
            break;
        default:
            strcpy((*cw)->stat->niveau,"facile");
            strcpy(filename,"sauvegardes/divers/grilles/facile_choix.txt");
            nbe=3;
            break;
        }
        strcpy(filename_dictionnaire,"dictionnaires/divers.txt");
        strcpy(filename_grille,"grilles/divers.txt");
        strcpy((*cw)->sujet,"divers");
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
    (*cw)->stat->heure_fin=*localtime(&secondes);
    run(cw,c,nbe,filename,str);
    (*cw)->stat->heure_fin=*localtime(&secondes);
}


/*
    fonction pour continuer une partie sauvegarder précédemment
*/
void reprendre_partie(Crossword **cw)
{
    char filename[60];
    time(&secondes);
    (*cw)->stat=NULL; 
    char filename_dictionnaire[100];
    char filename_grille[100];
    char file[50];
    char name[15];
    char str[10];
    strcpy(str, "rerun");
    printf("\nEntrer votre nom :\t");
    scanf("%s",name);
    int nbe;
    Crossword *c=malloc(sizeof(Crossword));
    switch (sujet())
    {
    case 1:
        switch (choix_niveau())
        {
        case 1:
            (*cw)->stat=load_statistique("divers",name,"facile");
            strcpy(filename_dictionnaire,"sauvegardes/divers/dictionnaires/facile.txt");
            strcpy(filename_grille,"sauvegardes/divers/grilles/facile.txt");
            strcpy(file,"grilles/divers.txt");
            (*cw)->stat->heure_debut=*localtime(&secondes);

            strcpy((*cw)->stat->niveau,"facile");
            strcpy(filename,"sauvegardes/divers/grilles/facile_choix.txt");
            nbe=3;
            break;
        case 2:

            (*cw)->stat=load_statistique("divers",name,"intermediaire");
            (*cw)->stat->heure_debut=*localtime(&secondes);
            strcpy(filename_dictionnaire,"sauvegardes/divers/dictionnaires/intermediaire.txt");
            strcpy(filename_grille,"sauvegardes/divers/grilles/intermediaire.txt");
            strcpy(file,"grilles/divers.txt");
            strcpy((*cw)->stat->niveau,"intermediaire");
            strcpy(filename,"sauvegardes/divers/grilles/intermediaire_choix.txt");
            nbe=2;
            break;
        case 3:

            (*cw)->stat=load_statistique("divers",name,"difficile");
            (*cw)->stat->heure_debut=*localtime(&secondes);
            strcpy(filename_dictionnaire,"sauvegardes/divers/dictionnaires/difficile.txt");
            strcpy(filename_grille,"sauvegardes/divers/grilles/difficile.txt");
            strcpy(file,"grilles/divers.txt");
            strcpy((*cw)->stat->niveau,"difficile");
            strcpy(filename,"sauvegardes/divers/grilles/difficile_choix.txt");
            nbe=1;
            break;
        default:
            (*cw)->stat=load_statistique("divers",name,"facile");
            (*cw)->stat->heure_debut=*localtime(&secondes);
            strcpy(filename_dictionnaire,"sauvegardes/divers/dictionnaires/facile.txt");
            strcpy(filename_grille,"sauvegardes/divers/grilles/facile.txt");
            strcpy(file,"grilles/divers.txt");
            strcpy(filename,"sauvegardes/divers/grilles/facile_choix.txt");
            strcpy((*cw)->stat->niveau,"facile");
            nbe=3;
            break;
        }
        strcpy((*cw)->sujet,"divers");
        break;
    case 2:
        switch (choix_niveau())
        {
        case 1:
            (*cw)->stat=load_statistique("education",name,"facile");
            (*cw)->stat->heure_debut=*localtime(&secondes);
            strcpy(filename_dictionnaire,"sauvegardes/education/dictionnaires/facile.txt");
            strcpy(filename_grille,"sauvegardes/education/grilles/facile.txt");
            strcpy(filename,"sauvegardes/education/grilles/facile_choix.txt");
            strcpy(file,"grilles/education.txt");
            strcpy((*cw)->stat->niveau,"facile");
            nbe=3;
            break;
        case 2:
            (*cw)->stat=load_statistique("education",name,"intermediaire");
            (*cw)->stat->heure_debut=*localtime(&secondes);
            strcpy(filename_dictionnaire,"sauvegardes/education/dictionnaires/intermediaire.txt");
            strcpy(filename_grille,"sauvegardes/education/grilles/intermediaire.txt");
            strcpy(file,"grilles/education.txt");
            strcpy(filename,"sauvegardes/education/grilles/intermediaire_choix.txt");
            strcpy((*cw)->stat->niveau,"intermediaire");
            nbe=2;
            break;
        case 3:
            (*cw)->stat=load_statistique("education",name,"difficile");
            (*cw)->stat->heure_debut=*localtime(&secondes);
            strcpy(filename_dictionnaire,"sauvegardes/education/dictionnaires/difficile.txt");
            strcpy(filename_grille,"sauvegardes/education/grilles/difficile.txt");
            strcpy(file,"grilles/divers.txt");
            strcpy(filename,"sauvegardes/education/grilles/difficile_choix.txt");
            strcpy((*cw)->stat->niveau,"difficile");
            nbe=1;
            break;
        default:
            (*cw)->stat=load_statistique("education",name,"facile");
            (*cw)->stat->heure_debut=*localtime(&secondes);
            strcpy(filename_dictionnaire,"sauvegardes/education/dictionnaires/facile.txt");
            strcpy(filename_grille,"sauvegardes/education/grilles/facile.txt");
            strcpy(file,"grilles/education.txt");
            strcpy(filename,"sauvegardes/education/grilles/facile_choix.txt");
            strcpy((*cw)->stat->niveau,"facile");
            nbe=3;
            break;
        }
        strcpy((*cw)->sujet,"education");
        break;
    case 3:
        switch (choix_niveau())
        {
        case 1:
            (*cw)->stat=load_statistique("medecine",name,"facile");
            (*cw)->stat->heure_debut=*localtime(&secondes);
            strcpy(filename_dictionnaire,"sauvegardes/medecine/dictionnaires/facile.txt");
            strcpy(filename_grille,"sauvegardes/medecine/grilles/facile.txt");
            strcpy(file,"grilles/medecine.txt");
            strcpy(filename,"sauvegardes/medecine/grilles/facile_choix.txt");
            strcpy((*cw)->stat->niveau,"facile");
            nbe=3;
            break;
        case 2:
            (*cw)->stat=load_statistique("medecine",name,"intermediaire");
            (*cw)->stat->heure_debut=*localtime(&secondes);
            strcpy(filename_dictionnaire,"sauvegardes/medecine/dictionnaires/intermediaire.txt");
            strcpy(filename_grille,"sauvegardes/medecine/grilles/intermediaire.txt");
            strcpy(file,"grilles/medecine.txt");
            strcpy(filename,"sauvegardes/medecine/grilles/intermediaire_choix.txt");
            strcpy((*cw)->stat->niveau,"intermediaire");
            nbe=2;
            break;
        case 3:
            (*cw)->stat=load_statistique("medecine",name,"difficile");
            (*cw)->stat->heure_debut=*localtime(&secondes);
            strcpy(filename_dictionnaire,"sauvegardes/medecine/dictionnaires/difficile.txt");
            strcpy(filename_grille,"sauvegardes/medecine/grilles/difficile.txt");
            strcpy(file,"grilles/medecine.txt");
            strcpy(filename,"sauvegardes/medecine/grilles/difficile_choix.txt");
            strcpy((*cw)->stat->niveau,"difficile");
            nbe=1;
            break;
        default:
            (*cw)->stat=load_statistique("medecine",name,"facile");
            (*cw)->stat->heure_debut=*localtime(&secondes);
            strcpy(filename_dictionnaire,"sauvegardes/medecine/dictionnaires/facile.txt");
            strcpy(filename_grille,"sauvegardes/medecine/grilles/facile.txt");
            strcpy(filename,"sauvegardes/medecine/grilles/facile_choix.txt");
            strcpy(file,"grilles/medecine.txt");
            strcpy((*cw)->stat->niveau,"facile");
            nbe=3;
            break;
        }
        strcpy((*cw)->sujet,"medecine");
        break;
    default:
        switch (choix_niveau())
        {
        case 1:
        
            (*cw)->stat=load_statistique("divers",name,"facile");
            (*cw)->stat->heure_debut=*localtime(&secondes);
            strcpy(filename_dictionnaire,"sauvegardes/divers/dictionnaires/facile.txt");
            strcpy(filename_grille,"sauvegardes/divers/grilles/facile.txt");
            strcpy(filename,"sauvegardes/divers/grilles/facile_choix.txt");
            strcpy(file,"grilles/divers.txt");
            strcpy((*cw)->stat->niveau,"facile");
            nbe=3;
            break;
        case 2:
            (*cw)->stat=load_statistique("divers",name,"intermediaire");
            (*cw)->stat->heure_debut=*localtime(&secondes);
            strcpy(filename_dictionnaire,"sauvegardes/divers/dictionnaires/intermediaire.txt");
            strcpy(filename_grille,"sauvegardes/divers/grilles/intermediaire.txt");
            strcpy(filename,"sauvegardes/divers/grilles/intermediaire_choix.txt");
            strcpy(file,"grilles/divers.txt");
            strcpy((*cw)->stat->niveau,"intermediaire");
            nbe=2;
            break;
        case 3:
            (*cw)->stat=load_statistique("divers",name,"difficile");
            (*cw)->stat->heure_debut=*localtime(&secondes);
            strcpy(filename_dictionnaire,"sauvegardes/divers/dictionnaires/difficile.txt");
            strcpy(filename_grille,"sauvegardes/divers/grilles/difficile.txt");
            strcpy(filename,"sauvegardes/divers/grilles/difficile_choix.txt");
            strcpy(file,"grilles/divers.txt");
            strcpy((*cw)->stat->niveau,"difficile");
            nbe=1;
            break;
        default:
            (*cw)->stat=load_statistique("divers",name,"facile");
            (*cw)->stat->heure_debut=*localtime(&secondes);
            strcpy(filename_dictionnaire,"sauvegardes/divers/dictionnaires/facile.txt");
            strcpy(filename_grille,"sauvegardes/divers/grilles/facile.txt");
            strcpy(filename,"sauvegardes/divers/grilles/facile_choix.txt");
            strcpy(file,"grilles/divers.txt");
            strcpy((*cw)->stat->niveau,"facile");
            nbe=3;
            break;
        }
        strcpy((*cw)->sujet,"divers");
        break;
    }
    c->dictionnaire=load_dictionnaire(filename_dictionnaire);
    c->g=load_grille(file);
    Dictionnaire *dic=remplacer_underscore_mots_dictionnaire(c->dictionnaire);
    (*cw)->dictionnaire=dic; 
    (*cw)->g=load_grille(filename_grille);
    run(cw,c,nbe,filename,str);
    (*cw)->stat->heure_fin=*localtime(&secondes);
}


/* 
    fonction pour sauvegarder la progression d'une partie dans les fichiers
*/
void sauvegarder_partie(Crossword *cw)
{
    char filename_dictionnaire[100];
    char filename_grille[100];
    if (strcmp(cw->g->niveau,"facile")==0)
    {
        if (strcmp(cw->sujet,"divers")==0){
            strcpy(filename_dictionnaire,"sauvegardes/divers/dictionnaires/facile.txt");
            strcpy(filename_grille,"sauvegardes/divers/grilles/facile.txt");
        }
        else if (strcmp(cw->sujet,"education")==0){
            strcpy(filename_dictionnaire,"sauvegardes/education/dictionnaires/facile.txt");
            strcpy(filename_grille,"sauvegardes/education/grilles/facile.txt");
        }
        else{
            strcpy(filename_dictionnaire,"sauvegardes/medecine/dictionnaires/facile.txt");
            strcpy(filename_grille,"sauvegardes/medecine/grilles/facile.txt");
        }
    }
    else if(strcmp(cw->g->niveau,"intermediaire")==0)
    {
        if (strcmp(cw->sujet,"divers")==0){
            strcpy(filename_dictionnaire,"sauvegardes/divers/dictionnaires/difficile.txt");
            strcpy(filename_grille,"sauvegardes/divers/grilles/difficile.txt");
        }
        else if (strcmp(cw->sujet,"education")==0){
            strcpy(filename_dictionnaire,"sauvegardes/education/dictionnaires/difficile.txt");
            strcpy(filename_grille,"sauvegardes/education/grilles/difficile.txt");
        }
        else{
            strcpy(filename_dictionnaire,"sauvegardes/medecine/dictionnaires/difficile.txt");
            strcpy(filename_grille,"sauvegardes/medecine/grilles/difficile.txt");
        }
    }
    else
    {
        if (strcmp(cw->sujet,"divers")==0){
            strcpy(filename_dictionnaire,"sauvegardes/divers/dictionnaires/facile.txt");
            strcpy(filename_grille,"sauvegardes/divers/grilles/facile.txt");
        }
        else if (strcmp(cw->sujet,"education")==0){
            strcpy(filename_dictionnaire,"sauvegardes/education/dictionnaires/facile.txt");
            strcpy(filename_grille,"sauvegardes/education/grilles/facile.txt");
        }
        else{
            strcpy(filename_dictionnaire,"sauvegardes/medecine/dictionnaires/facile.txt");
            strcpy(filename_grille,"sauvegardes/medecine/grilles/facile.txt");
        }
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
        fprintf(f1,"%d %d\n",cw->g->nombre_ligne,cw->g->nombre_colonne);
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
        fprintf(f2,"%s  %s  %s  %f %d  %d  %d %d  %d  %d  %d  %d\n",cw->sujet,cw->u->username,cw->stat->niveau,cw->stat->score,cw->stat->heure_debut.tm_mday,cw->stat->heure_debut.tm_mon,cw->stat->heure_debut.tm_hour,cw->stat->heure_debut.tm_min,cw->stat->heure_debut.tm_sec,cw->stat->heure_fin.tm_hour,cw->stat->heure_fin.tm_min,cw->stat->heure_fin.tm_sec);
        fclose(f);
        fclose(f1);
        fclose(f2);
    }
    else
    {
        return;
    }
}


/*
    fonction pour charger une grille enregistrer dans un fichier
*/
Grille *load_grille(char *filename)
{
    Grille *g=(Grille*)malloc(sizeof(Grille));
    FILE *f=fopen(filename,"r");

    fscanf(f,"%d %d",&g->nombre_ligne,&g->nombre_colonne);
    int size=g->nombre_ligne*g->nombre_colonne+1;
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
            
            grille[i][j].caractere=vec[k].caractere=='?'?' ':vec[k].caractere;
            k++;
        }
    }
    g->grille=grille;
    fclose(f);
    return g;
}



/*
    fonction qui permet de charger un dictionnaire enregistrer dans un fichier
*/
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


/*
    fonction pour affiche une grille
*/
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



/*
    fonction pour affiche un dictionnaire
*/
void print_dictionnaire(Dictionnaire * dic)
{
    if (dic!=NULL)
    {
        printf("\n\tHorizontal\t\t\t\t\t\t\t\t\t\t\t\t\tVertical\n");
        for (int i = 0; i < dic->dim; i++)
        {
            if (dic[i].indice_horizontal[0]=='-' && dic[i].indice_vertical[0]!='-')
            {
                printf("\t\t\t\t\t\t\t\t\t\t\t%d-%s.\n\n",dic[i].id,dic[i].indice_vertical);
            }
            else if (dic[i].indice_horizontal[0]!='-' && dic[i].indice_vertical[0]=='-')
            {
                printf("%d-%s.\n\n",dic[i].id,dic[i].indice_horizontal);
            }
            else
            {
                printf("%d-%s.\t\t\t\t\t\t\t\t\t\t%d-%s.\n",dic[i].id,dic[i].indice_horizontal,dic[i].id,dic[i].indice_vertical);
            }
        }
    }
    return;
}


/*
    fonction qui permet de liberer la mémoire allouée pour une partie du jeu
*/
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
    free(cw);
    return;
}

/*
    fonction qui permet de générer une grille non remplie à partir d'une grille déjà remplie
*/
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


/*
    fonction qui permet de remplacer les underscores dans les mots du dictionnaire
*/
Dictionnaire * remplacer_underscore_mots_dictionnaire(Dictionnaire *dic)
{
    for (int i = 0; i < dic->dim; i++)
    {
        strcpy(dic[i].indice_horizontal,replace(dic[i].indice_horizontal,'_',' '));
        strcpy(dic[i].indice_vertical,replace(dic[i].indice_vertical,'_',' '));
    }
    return dic;
}

/*
    fonction qui permet de remplacer les espace par les underscore dans les mots du dictionnaire
*/
Dictionnaire *remplacer_espace_mots_dictionnaire(Dictionnaire *dic)
{
    for (int i = 0; i < dic->dim; i++)
    {
        strcpy(dic[i].indice_horizontal,replace(dic[i].indice_horizontal,' ','_'));
        strcpy(dic[i].indice_vertical,replace(dic[i].indice_vertical,' ','_'));
    }
    return dic;
}

/*
    fonction qui permet de remplacer un caractère par un autre dans une chaine de caractère
*/
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


/*
    fonction qui permet de choisir le niveau de difficulté
*/
int choix_niveau()
{
    printf("\n\n Choix du niveau de difficulte.\n\n");
    printf("\n1-Niveau facile.\n");
    printf("\n2-Niveau intermediaire.\n");
    printf("\n3-Niveau difficile.\n");
    int choix;
    printf("\nEntrez votre choix :\t");
    scanf("%d",&choix);
    printf("\n\n");
    return choix;
}


/*
    fonction qui permet d'afficher le menu du jeu
*/
int menu()
{
    printf("\n\n Menu du jeu.\n\n");
    printf("\n1-Nouvelle partie.\n");
    printf("\n2-Reprendre une partie.\n");
    printf("\n3-Statistique.\n");
    printf("\n4-Quitter une partie.\n");
    int choix;
    printf("\nEntrer votre choix :\t");
    scanf("%d",&choix);
    printf("\n\n");
    if (choix>=1 && choix<=5)
    {
        return choix;
    }
    return -1;
}


/*
    fonction qui permet d'afficher le menu de démande d'aide
*/
int demande_aide()
{
    printf("\nToute aide est equivalent a un manu de 1/6 de votre reccompense avant la demande d'aide.\n");
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


/*
    fonction qui permet d'afficher le menu pour choisir le sujet de la partie encours
*/
int sujet()
{
    printf("\nChoix du sujet.\n");
    printf("\n1-Divers.\n");
    printf("\n2-Education.\n");
    printf("\n3-Medecine.\n");
    int choix;
    printf("\nEntrer votre choix:\t");
    scanf("%d",&choix);
    if (choix>=1 || choix<=3)
    {
        return choix;
    }
    return 0;
}


/*
    fonction pour charger les statistiques d'une partie précedemment sauvegardée
*/
Statistique *load_statistique(char * s, char *n, char * dif)
{
    FILE *f=NULL;
    f=fopen("statistique/stat.txt","r");
    if (f!=NULL)
    {
        char niveau[15];
        int h1,h2,m1,m2,s1,s2,m,d;
        char username[25];
        char sub[50];
        float score;
        while (fscanf(f,"%s %s %s %f %d %d %d %d %d %d %d %d",sub,username,niveau,&score,&d,&m,&h1,&m1,&s1,&h2,&m2,&s2)!=EOF)
        {
            if (strcmp(username,n)==0 && strcmp(sub,s)==0 && strcmp(niveau,dif)==0)
            {
                Statistique *stat=malloc(sizeof(Statistique));
                stat->score=score;
                return stat;
            }
            
        }
        fclose(f);
    }
    return NULL;
}


/* 
    fonction pour enregistrer les choix d'une partie dans un fichier
*/
void sauvegarder_choix(int *T, int n,char *filename)
{
    FILE *f=NULL;
    printf("\nfilename=%s\n",filename);
    f=fopen(filename,"w");
    if (f!=NULL)
    {
        for (int i = 0; i < n; i++)
        {
            fprintf(f,"%d\n",T[i]);
        }
        fclose(f);
    }
    else
    {
        return;
    }
    
}


/*
    fonction pour charger les choix précedemments sauvegardée
*/
int *load_choix(int n,char *filename)
{
    FILE *f=NULL;
    int *T=malloc(sizeof(int)*n);
    f=fopen(filename,"r");
    if (f!=NULL)
    {
        int i=0;
        while (fscanf(f,"%d",&T[i])!=EOF)
        {
            i++;
        }
        fclose(f);
        return T;
    }
    for (int i = 0; i < n; i++)
    {
        T[i] =0;
    }
    return T;
}

/*
    fonction qui permet d'afficher les statistiques d'un joueur
*/
void statistique(){
    FILE *f=NULL;
    f=fopen("statistique/stat.txt","r");
    if (f!=NULL)
    {
        char niveau[15];
        int h1,h2,m1,m2,s1,s2,m,d;
        char name[25];
        char username[25];
        char sub[50];
        printf("\nEntrer votre nom d'utilisateur:\t");
        scanf("%s",name);
        float score;
        printf("------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
        printf("Sujet\t\t|\t\tNiveau\t\t|\t\tScore\t\t|\tDate\t\t|\tHeure de D%cbut\t\t|\tHeure de Fin\n",130);
        printf("------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
        while (fscanf(f,"%s %s %s %f %d %d %d %d %d %d %d %d",sub,username,niveau,&score,&d,&m,&h1,&m1,&s1,&h2,&m2,&s2)!=EOF)
        {
            if (strcmp(username,name)==0)
            {
                printf("\n%s\t\t|%s\t|\t\t%.4f\t\t|\t%d/%d\t\t|\t%d:%d:%d\t\t\t|\t%d:%d:%d\n",sub,niveau,(score*100),d,m,h1,m1,s1,h2,m2,s2);
                printf("------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
            }
            
        }
        fclose(f);
    }
    return;
}