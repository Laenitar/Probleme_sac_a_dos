#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
* Variable du problème
* n = nombre d'objet (Basé sur variable globale MAX)
* Aj = Poids de l'objet
* Cj = Cout de l'objet
* Xj = (Boolean) Objet récupéré
* B = la limite de poid du sac à dos
*/

#define MAX 100
#define CON 12

//====================DEFINITION=====================
typedef struct{
    unsigned int cout;
    unsigned int poids;
    unsigned int x;
}Objet;

typedef Objet tab[MAX];

typedef struct{
    tab t_objets;
    float b;
    unsigned int n;
    unsigned int z;
}Probleme;


//====================================================
Probleme sacADosFixe();
Probleme sacADosAleat(int n);
float calculB(tab t, unsigned int n);
void affichageProbleme(Probleme prob);
void progDynamique(Probleme prob);
int maximum(int a, int b);
void affichagePrgDynamique(int **M, int contenance, int n);
Probleme heuristique_gloutonne(Probleme P);
int indice_objet_optimum(Probleme P, float* optimum);


//====================MAIN===========================
int main(int argc, char const *argv[]) {
    Probleme prob;
    int n;
    int choixProb = 0;


    printf("A l'attention du correcteur !\n");
    printf("Le tableau d'objet est initialisé grâce à la variable global max. \nVeuillez la changez pour le mettre en adéquation averc le nombre d'objet généré aléatoirement. Merci\n");

    do{
        printf("Veuillez choisir un problème du sac à dos:\n");
        printf("\t1/ Problème fixe : 8 objets et 12 de contenance\n");
        printf("\t2/ Problème aléatoire\n");
        printf("\t9/ Quitter\n");
        printf("Choix : ");
        scanf("%d", &choixProb);
        printf("\n");

        switch (choixProb){
            case 1:
                prob = sacADosFixe();
                //affichageProbleme(prob);
                //Programmation Dynamique
                progDynamique(prob);
                break;
            case 2 :
                printf("Veuillez saisir le nombre d'objet que vous voulez créer aléatoirement : ");
                scanf("%d", &n);
                printf("\n");
                prob = sacADosAleat(n);
                //affichageProbleme(prob);
                //Programmation Dynamique
                progDynamique(prob);

            case 9:
                choixProb = 9;
                break;
            default:
                printf("Ce choix n\'existe pas, veuillez recommencez\n");

        }
    }while(choixProb != 9 );

    //prob = heuristique_gloutonne(prob);

    printf("\nExit\n");


    return 0;
}


//====================FONCTIONS======================
Probleme sacADosFixe(){
    Probleme prob;
    Objet obj;

    //A
    obj.cout = 5;
    obj.poids = 2;
    prob.t_objets[0] = obj;
    //B
    obj.cout = 8;
    obj.poids = 3;
    prob.t_objets[1] = obj;
    //C
    obj.cout = 14;
    obj.poids = 5;
    prob.t_objets[2] = obj;
    //D
    obj.cout = 6;
    obj.poids = 2;
    prob.t_objets[3] = obj;
    //E
    obj.cout = 13;
    obj.poids = 4;
    prob.t_objets[4] = obj;
    //F
    obj.cout = 17;
    obj.poids = 6;
    prob.t_objets[5] = obj;
    //G
    obj.cout = 10;
    obj.poids = 3;
    prob.t_objets[6] = obj;
    //H
    obj.cout = 4;
    obj.poids = 1;
    prob.t_objets[7] = obj;

    prob.b = CON;
    prob.n = 8;

    return prob;
}

Probleme sacADosAleat(int n) {
    srand(time(NULL));
    Probleme prob;
    Objet obj;
    for(int i=0; i<n; i++) {
        obj.cout = (unsigned int) (rand() / (double) RAND_MAX * (101 - 1) + 1);
        obj.poids = (unsigned int) (rand() / (double) RAND_MAX * (101 - 1) + 1);
        prob.t_objets[i] = obj;
        prob.t_objets[i].x=0;
    }
    prob.z = 0;
    prob.n = n;
    prob.b = calculB(prob.t_objets, n);

    return prob;
}

//Intialisation de la taille du sacs
float calculB(tab t, unsigned int n){
    float S = 0;
    for(unsigned int i = 0; i < n ; i++){
        S += t[i].cout;
    }
    srand(time(NULL));
    unsigned int nb_alea = rand()%3 +1;
    return 0.25*nb_alea*S;
}



void progDynamique(Probleme prob){
    int contenance = (int)prob.b;
    int M[prob.n][contenance+1];



    //Remplissage de la matrice à partir de la 2e ligne.
    for(int i=0; i<prob.n; i++) {
        printf("Poids objet %d : %d\n",i, prob.t_objets[i].cout);
        if(i==0){
            //Remplissage de la 1ere ligne de la matrice.
            for (int j = 0; j <= contenance; j++) {
                if (prob.t_objets[0].poids > j) {
                    M[0][j] = 0;
                } else {
                    M[0][j] = prob.t_objets[0].cout;
                }
            }
        }else {
            for (int j = 0; j <= contenance; j++) {
                if (prob.t_objets[i].poids > j) {
                    M[i][j] = M[i - 1][j];
                } else {
                    M[i][j] = maximum(M[i - 1][j], M[i - 1][j - prob.t_objets[i].poids] + prob.t_objets[i].cout);
                }
            }
        }
    }

    //Affichage de la matrice de programmation dynamique
    printf("Affichage de la matrice de programmation dynamique :\n******************\n");
    for (int i = 0; i < prob.n; i++) {
        printf("Objet %d\n", i);
        for (int j = 0; j <= contenance; j++) {
            printf("%d\t", M[i][j]);
        }
        printf("\n");
    }

    /*
     * Résolution de la programmation dynamique
     * Le bénéfice optimal et la solution optimale se trouvent dans la matrice
     */
    int j = contenance;
    int i = prob.n-1;

    //La derniere case founnit le bénéfice obtimal
    printf("\nLe bénéfice optimal est de : %d\n", M[i][j]);
    printf("La contenance du sac à dos est de : %0.2f\n", prob.b);


    //On recule sur la ligne de la valeur optimale pour trouver le optimal

    int totPoid = 0;
    int totCout = 0;
    //On cherche le poid minimal nécessaire pour le bénéfice optimal
    while(M[i][j] == M[i][j-1]){
        j--;
    }
    printf("\n");
    while(j>0){
        while(i>=0 && M[i][j] == M[i-1][j]){
            i--;
        }
        if(j>0){
            j = j-prob.t_objets[i].poids;

            printf("L'objet %d ,de poids %d, fait parti de la solution optimale\n",i, prob.t_objets[i].poids);
            totPoid += prob.t_objets[i].poids;
            totCout += prob.t_objets[i].cout;
        }
        i--;
    }
    printf("Le bénéfice sera de %d pour un poids de %d\n\n", totCout, totPoid);



}

int maximum(int a, int b){
    if(a>b)
        return a;

    return b;
}


//Affichage du probleme
void affichageProbleme(Probleme prob){
    printf("============================================\n");
    printf("Voici la liste des objets du problème :\n");
    for(int i=0; i<prob.n; i++){
        printf("Objet n°%d, cout : %d, poids : %d, pris : %d\n", i, prob.t_objets[i].cout,prob.t_objets[i].poids,prob.t_objets[i].x);
    }
    printf("Poids max du sac : %f\n", prob.b);
    printf("Z = %d\n", prob.z);
    printf("============================================\n");
}

Probleme heuristique_gloutonne(Probleme P){
    //Calcule du rapport cout/poid de chaque objets
    float optimum[P.n];
    for(unsigned int i = 0; i < P.n ; i++){
        optimum[i]= P.t_objets[i].cout/P.t_objets[i].poids;

        unsigned int arret=0;
        //On ajoute les objets optimum un à un tant que l'on peut
        while(!arret){
            //On récupère l'indice de l'objet optimal
            int indice_optimum = indice_objet_optimum(P,optimum);
            //Si on a trouvé un objet on passe l'objet à "pris" on ajoute le cout à z et on diminue la taille du sac
            if(indice_optimum!=-1){
                P.t_objets[indice_optimum].x=1;
                P.b -= P.t_objets[indice_optimum].poids;
                P.z+=P.t_objets[indice_optimum].cout;
            }
            else{
                arret=1;
            }
        }
    }
    return P;
}
//Renvoie l'indice de l'objet ayant le rapport cout/poid le plus élevé qui n'a pas encore été pris
//et qui rentre dans le sac
int indice_objet_optimum(Probleme P, float* optimum){
    float max = 0;
    int indice_optimum = -1;
    for(unsigned int i = 0; i < P.n ; i++)
    if (P.t_objets[i].x==0 && optimum[i]>max && P.t_objets[i].poids <= P.b){
        indice_optimum=i;
    }
    return indice_optimum;
}

void affichagePrgDynamique(int **M, int contenance, int n) {
    printf("Affichage de la matrice de programmation dynamique\n");
    for (int i = 0; i < n; i++) {
        printf("Objet %d\n", i);
        for (int j = 0; j < contenance; j++) {
            printf("%d\t", M[i][j]);
        }
        printf("\n");
    }
}