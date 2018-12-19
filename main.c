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

#define MAX 20

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
Probleme sacADosAleat(int n);
float calculB(tab t, unsigned int n);
void affichageProbleme(Probleme prob);
Probleme heuristique_gloutonne(Probleme P);
int indice_objet_optimum(Probleme P, float* optimum);

//====================MAIN===========================
int main() {

    Probleme prob = sacADosAleat(MAX);
    affichageProbleme(prob);
    prob = heusterique_gloutonne(prob);
    affichageProbleme(prob);
    return 0;
}


//====================FONCTIONS======================
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

//Affichage du probleme
void affichageProbleme(Probleme prob){
    printf("============================================\n");
    printf("Voici la liste des objets du problème :\n");
    for(int i=0; i<MAX; i++){
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
