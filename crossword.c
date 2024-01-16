#include "crossword.h"

time_t secondes;

/*
    fonction qui contient le déroulement du jeu
*/
void run(Crossword **cw, Crossword *c, int nbe, char *filename, char *str)
{
    int s = 0, k = 0;
    int *current = load_choix((*cw)->dictionnaire->dim, filename);
    float manus = 0.0f;
    char response[25];
    while (current[k]!=0)
    {
        k++;
    }
    while (k < (*cw)->dictionnaire->dim)
    {
        print_grille((*cw)->g);
        printf("\n\n");
        print_dictionnaire((*cw)->dictionnaire);
        printf("\n0-sauvegarder la partie en cours.\n");

        int choix = get_choice(k, (*cw)->dictionnaire->dim, current);
        if (choix == 0)
        {
            save_and_exit(cw, s, manus, current, filename);
            current[k] = current[k] == 0 ? choix : current[k];
            return;
        }

        printf("\nEntrer votre reponse :\t");
        // Taille de la réponse est la même que la taille de l'utilisateur
        lire(response, USERNAME_SIZE);

        int i = 0;
        while (!is_correct_answer(upper_case(response), (*cw)->dictionnaire[choix - 1], c) && i < nbe)
        {
            i++;
            manus += display_hint_and_get_manus(&(*cw)->dictionnaire[choix - 1], c);
            printf("\nIl vous reste %d essais possible\n", (nbe - i)+1);
            printf("\nVeillez re-essayer une nouvelle reponse:\t");
            lire(response, USERNAME_SIZE);
        }

        if (is_correct_answer(upper_case(response), (*cw)->dictionnaire[choix - 1], c))
        {
            s++;
            update_grid_with_answer((*cw)->g,(*cw)->dictionnaire[choix-1], upper_case(response), choix);
        }
        current[k] = current[k] == 0 ? choix : current[k];
        k++;
    }
    // (*cw)->stat->score += (float)(((float)s*SCORE / (float)(*cw)->dictionnaire->dim) - manus);
    (*cw)->stat->score += (float)((float)s*SCORE - manus); // / (float)(*cw)->dictionnaire->dim)
    print_grille((*cw)->g);
    char ch=getchar();
}

int get_choice(int turn, int maxChoices, int *currentChoices)
{
    int choice;

    printf("\nEntrez votre choix (le numéro doit être compris entre [0-%d]):\t", maxChoices);
    choice = lire_int();

    int r=1;
    while (r)
    {
        if (choice<=maxChoices && !isIn(currentChoices, maxChoices, choice) || choice==0)
        {
           r=0;
           return choice;
        }
        printf("\nChoix non disponible ou choix deja fait veuillez reessayer:\t");
        choice = lire_int();
    }
    return choice;
}

void save_and_exit(Crossword **cw, int score, float manus, int *currentChoices, char *filename)
{
    time_t secondes;
    time(&secondes);
    (*cw)->stat->heure_fin = *localtime(&secondes);
    (*cw)->stat->score += ((float)score / (float)(*cw)->dictionnaire->dim) - manus;
    sauvegarder_choix(currentChoices, (*cw)->dictionnaire->dim, filename);
    sauvegarder_partie(*cw);
}

bool is_correct_answer(char *response, Dictionnaire entry, Crossword *c)
{
    return strcmp(response, entry.indice_horizontal[0] != '-' ? c->dictionnaire[entry.id - 1].resultat_horizontal : c->dictionnaire[entry.id - 1].resultat_vertical) == 0;
}

/// @brief  display a hint and return the manus value
/// @param entry
/// @param c
/// @return
float display_hint_and_get_manus(Dictionnaire *entry, Crossword *c)
{
    if (demande_aide() == 1)
    {
        char firstLetter = entry->indice_horizontal[0] != '-' ? c->dictionnaire[entry->id - 1].resultat_horizontal[0] : c->dictionnaire[entry->id - 1].resultat_vertical[0];
        char lastLetter = entry->indice_horizontal[0] != '-' ? c->dictionnaire[entry->id - 1].resultat_horizontal[strlen(c->dictionnaire[entry->id - 1].resultat_horizontal) - 1] : c->dictionnaire[entry->id - 1].resultat_vertical[strlen(c->dictionnaire[entry->id - 1].resultat_vertical) - 1];
        size_t length = entry->indice_horizontal[0] != '-' ? strlen(c->dictionnaire[entry->id - 1].resultat_horizontal) : strlen(c->dictionnaire[entry->id - 1].resultat_vertical);
        printf("\nLa réponse commence par %c et se termine par %c et contient %ld caractères.\n", firstLetter, lastLetter, length);
        return 2.0f ;/// ((float)(*entry).dim * 6)
    }
    return 0.0f;
}

/// @brief  Update the game grid with the correct answer.
/// @param grid
/// @param response
/// @param choice
void update_grid_with_answer(Grille *grid,Dictionnaire dic, char *response, int choice)
{
    int t, z;
    for (int i = 0; i < grid->nombre_ligne; i++)
    {
        for (int j = 0; j < grid->nombre_colonne; j++)
        {
            if (grid->grille[i][j].id == choice)
            {
                t = i;
                z = j;
                continue; // Exit the inner loop when found
            }
        }
    }
    if (grid->grille[t][z].id == choice)
    {
        if (strcmp(dic.indice_horizontal,"-")!=0)
        {
            for (int i = z; i < z+strlen(response); i++)
            {
                grid->grille[t][i].caractere = response[i-z];
            }
        }
        else
        {
            for (int i = t; i < t+strlen(response); i++)
            {
                grid->grille[i][z].caractere = response[i-t];
            }
        }
        
    }
}

void nouvelle_partie(Crossword **cw)
{
    time_t secondes;
    time(&secondes);
    (*cw)->stat = (Statistique *)malloc(sizeof(Statistique));
    (*cw)->stat->heure_debut = *localtime(&secondes);
    (*cw)->stat->score = 0.0f;

    char filename_dictionnaire[FILE_PATH_SIZE];
    char filename_grille[FILE_PATH_SIZE];
    char filename[60];
    char str[2] = " ";
    int nbe;
    Crossword *c = (Crossword *)malloc(sizeof(Crossword));

    int sujetChoisi = sujet();
    int niveauChoisi = choix_niveau();

    const char *niveaux[] = {"facile", "intermediaire", "difficile"};
    const char *sujets[] = {"divers", "education", "medecine"};

    if (sujetChoisi < 1 || sujetChoisi > 3)
        sujetChoisi = 1;
    if (niveauChoisi < 1 || niveauChoisi > 3)
        niveauChoisi = 1;
    sprintf(filename, "tmp/sauvegardes/%s/choix/%s.txt", sujets[sujetChoisi - 1], niveaux[niveauChoisi - 1]);
    sprintf(filename_dictionnaire, "dictionnaires/%s.txt", sujets[sujetChoisi - 1]);
    sprintf(filename_grille, "grilles/%s.txt", sujets[sujetChoisi - 1]);

    strcpy((*cw)->stat->niveau, niveaux[niveauChoisi - 1]);
    strcpy((*cw)->sujet, sujets[sujetChoisi - 1]);

    nbe = 4 - niveauChoisi;

    printf("\nEntrer votre nom:\t");
    (*cw)->u = malloc(sizeof(User));
    // scanf("%s", (*cw)->u->username);
    lire((*cw)->u->username, USERNAME_SIZE);

    c->dictionnaire = load_dictionnaire(filename_dictionnaire);
    c->g = load_grille(filename_grille);
    Dictionnaire *dic = remplacer_underscore_mots_dictionnaire(c->dictionnaire);
    (*cw)->dictionnaire = dic;
    (*cw)->g = generer_grille(c->g);
    (*cw)->stat->heure_fin = *localtime(&secondes);

    run(cw, c, nbe, filename, str);
    (*cw)->stat->heure_fin = *localtime(&secondes);
}

/*
    fonction pour continuer une partie sauvegarder précédemment
*/
void reprendre_partie(Crossword **cw)
{
    char filename[100], filename_dictionnaire[FILE_PATH_SIZE], filename_grille[FILE_PATH_SIZE], file[60];
    time_t secondes;
    time(&secondes);
    (*cw)->stat = NULL;
    char name[15];
    printf("\nEntrer votre nom :\t");
    lire(name, 15);
    int nbe;
    Crossword *c = malloc(sizeof(Crossword));

    // Get subject and difficulty level
    char *subject = get_subject(sujet());
    char *difficulty = get_difficulty(choix_niveau());

    // Load statistics
    (*cw)->stat = load_statistique(subject, name, difficulty);
    (*cw)->stat->heure_debut = *localtime(&secondes);
    strcpy((*cw)->stat->niveau, difficulty);

    // Setup file paths
    sprintf(filename_dictionnaire, "users/%s/sauvegardes/%s/dictionnaires/%s.txt",name, subject, difficulty);
    sprintf(filename_grille, "users/%s/sauvegardes/%s/grilles/%s.txt",name, subject, difficulty);
    sprintf(file, "grilles/%s.txt", subject);
    sprintf(filename, "users/%s/sauvegardes/%s/choix/%s.txt",name, subject, difficulty);

    // Set subject and number of attempts
    strcpy((*cw)->sujet, subject);
    nbe = get_number_of_attempts(difficulty);

    // Load game components
    c->dictionnaire = load_dictionnaire(filename_dictionnaire);
    c->g = load_grille(file);
    Dictionnaire *dic = remplacer_underscore_mots_dictionnaire(c->dictionnaire);
    (*cw)->dictionnaire = dic;
    (*cw)->g = load_grille(filename_grille);

    // Start the game
    run(cw, c, nbe, filename, "rerun");
    (*cw)->stat->heure_fin = *localtime(&secondes);
}

// Helper function to get subject
char *get_subject(int subjectCode)
{
    switch (subjectCode)
    {
    case 1:
        return "divers";
    case 2:
        return "education";
    case 3:
        return "medecine";
    default:
        printf("\nVotre choix n'est pas disponible.\n");
    }
}

char *get_difficulty(int levelCode)
{
    switch (levelCode)
    {
    case 1:
        return "facile";
    case 2:
        return "intermediaire";
    case 3:
        return "difficile";
    default:
        printf("\nVotre choix n'est pas disponible.\n");
    }
    
}

int get_number_of_attempts(char *difficulty)
{
    if (strcmp(difficulty, "facile") == 0)
    {
        return 3;
    }
    else if (strcmp(difficulty, "intermediaire") == 0)
    {
        return 2;
    }
    else
    {
        return 1;
    }
}

/*
    fonction pour sauvegarder la progression d'une partie dans les fichiers
*/
void sauvegarder_partie(Crossword *cw)
{
    char filename_dictionnaire[FILE_PATH_SIZE], filename_grille[FILE_PATH_SIZE], stat_file[] = "statistique/stat.txt";

    char str[100];

    sprintf(str,"%s\t%s","./script.sh",cw->u->username);
    // Construct file paths based on 'sujet' and 'niveau'
    sprintf(filename_dictionnaire, "tmp/sauvegardes/%s/dictionnaires/%s.txt", cw->sujet, cw->stat->niveau);
    sprintf(filename_grille, "tmp/sauvegardes/%s/grilles/%s.txt", cw->sujet, cw->stat->niveau);

    FILE *f = fopen(filename_dictionnaire, "w");
    FILE *f1 = fopen(filename_grille, "w");
    FILE *f2 = fopen(stat_file, "a+");

    cw->dictionnaire=remplacer_espace_mots_dictionnaire(cw->dictionnaire);
    if (f && f1 && f2)
    {
        // Save Dictionary
        fprintf(f, "%d\n", cw->dictionnaire->dim);
        for (int i = 0; i < cw->dictionnaire->dim; i++)
        {
            fprintf(f, "%d\t\t%s\t\t%s\t\t%s\t\t%s\n",
                    cw->dictionnaire[i].id,
                    cw->dictionnaire[i].indice_horizontal,
                    cw->dictionnaire[i].indice_vertical,
                    cw->dictionnaire[i].resultat_horizontal,
                    cw->dictionnaire[i].resultat_vertical);
        }

        // Save Grid
        fprintf(f1, "%d %d\n", cw->g->nombre_ligne, cw->g->nombre_colonne);
        for (int i = 0; i < cw->g->nombre_ligne; i++)
        {
            for (int j = 0; j < cw->g->nombre_colonne; j++)
            {
                char to_write = (cw->g->grille[i][j].caractere == ' ') ? '?' : cw->g->grille[i][j].caractere;
                fprintf(f1, "%d  %c\n", cw->g->grille[i][j].id, to_write);
            }
        }

        // Save Statistics
        fprintf(f2, "%s  %s  %s  %f %d  %d  %d %d  %d  %d  %d  %d\n",
                cw->sujet, cw->u->username, cw->stat->niveau, cw->stat->score,
                cw->stat->heure_debut.tm_mday, cw->stat->heure_debut.tm_mon,
                cw->stat->heure_debut.tm_hour, cw->stat->heure_debut.tm_min,
                cw->stat->heure_debut.tm_sec, cw->stat->heure_fin.tm_hour,
                cw->stat->heure_fin.tm_min, cw->stat->heure_fin.tm_sec);

        fclose(f);
        fclose(f1);
        fclose(f2);
        system(str);
    }
}

/*
    fonction pour charger une grille enregistrer dans un fichier
*/
Grille *load_grille(char *filename)
{
    Grille *g = (Grille *)malloc(sizeof(Grille));
    FILE *f = NULL;

    f = fopen(filename, "r");
    if (f==NULL)
    {
        printf("\nSauvegarde non disponible.\n");
        return NULL;
    }
    else
    {
        fscanf(f, "%d %d", &g->nombre_ligne, &g->nombre_colonne);
        int size = g->nombre_ligne * g->nombre_colonne + 1;
        Cellule *vec = (Cellule *)malloc(sizeof(Cellule) * size);
        int k = 0;
        while (fscanf(f, "%d %c", &vec[k].id, &vec[k].caractere) != EOF)
        {
            k++;
        }
        k = 0;
        Cellule **grille = malloc(sizeof(Cellule) * g->nombre_ligne);
        for (int i = 0; i < g->nombre_ligne; i++)
        {
            grille[i] = malloc(sizeof(Cellule) * g->nombre_colonne);
            for (int j = 0; j < g->nombre_colonne; j++)
            {
                grille[i][j].id = vec[k].id;

                grille[i][j].caractere = vec[k].caractere == '?' ? ' ' : vec[k].caractere;
                k++;
            }
        }
        g->grille = grille;
        fclose(f);
    }

    return g;
}

/*
    fonction qui permet de charger un dictionnaire enregistrer dans un fichier
*/
Dictionnaire *load_dictionnaire(char *filename)
{

    FILE *f = NULL;
    Dictionnaire *dic = NULL;
    f = fopen(filename, "r");
    if (f == NULL)
    {
        printf("\nSauvegarde non disponible.\n");
        return NULL;
    }
    else
    {
        int dim;
        fscanf(f, "%d\n", &dim);
        dic = (Dictionnaire *)malloc(sizeof(Dictionnaire) * dim);
        dic->dim = dim;
        int i = 0;
        while (fscanf(f, "%d  %s  %s  %s  %s", &dic[i].id, dic[i].indice_horizontal, dic[i].indice_vertical, dic[i].resultat_horizontal, dic[i].resultat_vertical) != EOF && i < dim)
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
    if (g->grille != NULL)
    {
        for (int i = 0; i < g->nombre_ligne; i++)
        {
            printf("\n");
            for (int j = 0; j < g->nombre_colonne; j++)
            {
                if (g->grille[i][j].id != 0)
                {
                    printf("|%d %c|\t", g->grille[i][j].id, g->grille[i][j].caractere);
                }
                else
                {
                    printf("  |%c|\t", g->grille[i][j].caractere);
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
void print_dictionnaire(Dictionnaire *dic)
{
    if (dic != NULL)
    {
        printf("\n\tHorizontal\t\t\t\t\t\t\t\t\t\t\t\t\tVertical\n");
        for (int i = 0; i < dic->dim; i++)
        {
            if (dic[i].indice_horizontal[0] == '-' && dic[i].indice_vertical[0] != '-')
            {
                printf("\t\t\t\t\t\t\t\t\t\t\t%d-%s.\n\n", dic[i].id, dic[i].indice_vertical);
            }
            else if (dic[i].indice_horizontal[0] != '-' && dic[i].indice_vertical[0] == '-')
            {
                printf("%d-%s.\n\n", dic[i].id, dic[i].indice_horizontal);
            }
            else
            {
                printf("%d-%s.\t\t\t\t\t\t\t\t\t\t%d-%s.\n", dic[i].id, dic[i].indice_horizontal, dic[i].id, dic[i].indice_vertical);
            }
        }
    }
    return;
}

/*
    fonction qui permet de liberer la mémoire allouée pour une partie du jeu
*/
void free_memory(Crossword **cw)
{

    if (cw!=NULL && (*cw) != NULL)
    {
        free((*cw)->dictionnaire);
        free((*cw)->stat);
        free((*cw)->g);
        free(*cw);
    }
    return;
}

/*
    fonction qui permet de générer une grille non remplie à partir d'une grille déjà remplie
*/
Grille *generer_grille(Grille *g)
{
    Grille *gril = malloc(sizeof(Grille));
    Cellule **cel = malloc(sizeof(Cellule) * g->nombre_ligne);
    for (int i = 0; i < g->nombre_ligne; i++)
    {
        cel[i] = malloc(sizeof(Cellule) * g->nombre_colonne);
        for (int j = 0; j < g->nombre_colonne; j++)
        {
            cel[i][j].id = g->grille[i][j].id;

            cel[i][j].caractere = g->grille[i][j].caractere == '*' ? g->grille[i][j].caractere : ' ';
        }
    }
    gril->grille = cel;
    gril->nombre_ligne = g->nombre_ligne;
    gril->nombre_colonne = g->nombre_colonne;
    strcpy(gril->niveau, g->niveau);
    return gril;
}

/*
    fonction qui permet de remplacer les underscores dans les mots du dictionnaire
*/
Dictionnaire *remplacer_underscore_mots_dictionnaire(Dictionnaire *dic)
{
    for (int i = 0; i < dic->dim; i++)
    {
        strcpy(dic[i].indice_horizontal, replace(dic[i].indice_horizontal, '_', ' '));
        strcpy(dic[i].indice_vertical, replace(dic[i].indice_vertical, '_', ' '));
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
        strcpy(dic[i].indice_horizontal, replace(dic[i].indice_horizontal, ' ', '_'));
        strcpy(dic[i].indice_vertical, replace(dic[i].indice_vertical, ' ', '_'));
    }
    return dic;
}

/*
    fonction qui permet de remplacer un caractère par un autre dans une chaine de caractère
*/
char *replace(char *ch, char c, char r)
{
    for (int i = 0; i < strlen(ch); i++)
    {
        if (ch[i] == c)
        {
            ch[i] = r;
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
    choix = lire_int();
    printf("\n\n");
    while (!(choix >= 1 && choix <= 3))
    {
        printf("\nChoix non disponible veuillez reessayer:\t");
        choix = lire_int();
    }
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
    printf("\n5-About.\n");
    int choix;
    printf("\nEntrer votre choix :\t");
    choix = lire_int();
    printf("\n\n");
    while (!(choix >= 1 && choix <= 5))
    {
        printf("\nChoix non disponible veuillez reessayer:\t");
        choix = lire_int();
    }
    return choix;
}

/*
    fonction qui permet d'afficher le menu de démande d'aide
*/
int demande_aide()
{
    int choix;
    printf("\nToute aide vous coutera 2 points.\n");
    printf("\nAvez-vous besoin d'aide [1|*].\n");
    printf("\nEntrer votre choix:\t");
    
    choix=lire_int();
    while (!(choix>=0 && choix<=1))
    {
        printf("\nVeuillez reessayer:\t");
        choix=lire_int();
    }
    return choix;
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
    choix = lire_int();
    while (!(choix >= 1 && choix <= 3))
    {
        printf("\nChoix non disponible veuillez reessayer:\t");
        choix = lire_int();
    }
    return choix;
}

/*
    fonction pour charger les statistiques d'une partie précedemment sauvegardée
*/
Statistique *load_statistique(char *s, char *n, char *dif)
{
    FILE *f = NULL;
    f = fopen("statistique/stat.txt", "r");
    if (f != NULL)
    {
        char niveau[15];
        int h1, h2, m1, m2, s1, s2, m, d;
        char username[USERNAME_SIZE];
        char sub[50];
        float score;
        while (fscanf(f, "%s %s %s %f %d %d %d %d %d %d %d %d", sub, username, niveau, &score, &d, &m, &h1, &m1, &s1, &h2, &m2, &s2) != EOF)
        {
            if (strcmp(username, n) == 0 && strcmp(sub, s) == 0 && strcmp(niveau, dif) == 0)
            {
                Statistique *stat = malloc(sizeof(Statistique));
                stat->score = score;
                return stat;
            }
        }
        fclose(f);
    }
    return NULL;
}

void sauvegarder_choix(int *T, int n, char *filename)
{
    FILE *f = NULL;
    f = fopen(filename, "w");
    if (f != NULL)
    {
        for (int i = 0; i < n; i++)
        {
            fprintf(f, "%d\n", T[i]);
        }
        fclose(f);
    }
    else
    {
        return;
    }
}

int *load_choix(int n, char *filename)
{
    FILE *f = NULL;
    int *T = malloc(sizeof(int) * n);
    f = fopen(filename, "r");
    if (f != NULL)
    {
        int i = 0;
        while (fscanf(f, "%d", &T[i]) != EOF)
        {
            i++;
        }
        fclose(f);
        return T;
    }
    for (int i = 0; i < n; i++)
    {
        T[i] = 0;
    }
    return T;
}

/*
    fonction qui permet d'afficher les statistiques d'un joueur
*/
void statistique()
{
    FILE *f = NULL;
    f = fopen("statistique/stat.txt", "r");
    if (f != NULL)
    {
        char niveau[15];
        int h1, h2, m1, m2, s1, s2, m, d;
        char name[USERNAME_SIZE];
        char username[USERNAME_SIZE];
        char sub[50];
        printf("\nEntrer votre nom d'utilisateur:\t");
        lire(name, USERNAME_SIZE);
        float score;
        printf("------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
        // printf("Sujet\t\t|\t\tNiveau\t\t|\t\tScore\t\t|\tDate\t\t|\tHeure de D%cbut\t\t|\tHeure de Fin\n", 130);
        printf("Sujet\t\t\t\t|Niveau\t\t\t|\t\t\t\tScore\t\t\t|\t\t\t\tDuree(min)\n");
        printf("------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
        while (fscanf(f, "%s %s %s %f %d %d %d %d %d %d %d %d", sub, username, niveau, &score, &d, &m, &h1, &m1, &s1, &h2, &m2, &s2) != EOF)
        {
            if (strcmp(username, name) == 0)
            {
                // printf("\n%s\t\t|%s\t|\t\t%.4f\t\t|\t%d/%d\t\t|\t%d:%d:%d\t\t\t|\t%d:%d:%d\n", sub, niveau, (score * FILE_PATH_SIZE), d, m, h1, m1, s1, h2, m2, s2);
                printf("\n%s\t\t\t\t|%s\t|\t\t\t\t%.4f\t\t\t\t|\t\t\t\t%.4f\n", sub, niveau, (score), duration(h2,m2,s2,h1,m1,s1));
                printf("------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
            }
        }
        fclose(f);
        return;
    }
    printf("\nAucune statistique disponible.\n");
    return;
}


char *upper_case(char *str){
    for (int i = 0; str[i]!='\0'; i++) {
      if(str[i] >= 'a' && str[i] <= 'z') {
         str[i] = str[i] -32;
      }
   }
   return str;
}

void appropos()
{
    
    printf("\nNotre jeu est base sur trois sujets precises:\n");
    printf("\n1-Divers qui met en vigueur votre culture sportive et celle sur les noms des pays.\n");
    printf("\n2-Education qui met en vigueur votre culture informatique.\n");
    printf("\n3-medecine qui met en vigueur votre culture dans le domaine de la medecine.\n");
    char c=getchar();
}

float duration(int h1,int m1,int s1,int h2,int m2,int s2)
{
    float tim=((float)(h1*60)+(float)m1 +((float)(s1)/(float)60))-((float)(h2*60)+(float)m2 +((float)(s2)/(float)60));
    return tim;
}
