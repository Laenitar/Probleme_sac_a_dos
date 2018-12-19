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

#define MAX 10

typedef struct{
    unsigned int cout;
    unsigned int poids;
}Objet;

typedef Objet tab[MAX];

typedef struct{
    tab t_objets;
    float b;
}Probleme;

Probleme sacADosAleat(int n);
float calculB(tab t, unsigned int n);
void affichageProbleme(Probleme prob);


int main(int argc, char const *argv[]) {
    printf("Hello THE World\n");
    Probleme prob = sacADosAleat(MAX);
    affichageProbleme(prob);
}



Probleme sacADosAleat(int n) {
    srand(time(NULL));
    Probleme prob;
    Objet obj;
    for(int i=0; i<n; i++) {
        obj.cout = (unsigned int) (rand() / (double) RAND_MAX * (101 - 1) + 1);
        obj.poids = (unsigned int) (rand() / (double) RAND_MAX * (101 - 1) + 1);
        prob.t_objets[i] = obj;
    }
    prob.b = calculB(prob.t_objets, n);

    return prob;
}


float calculB(tab t, unsigned int n){
    float S = 0;
    for(unsigned int i = 0; i < n ; i++){
        S += t[i].cout;
    }
    srand(time(NULL));
    unsigned int nb_alea = rand()%3 +1;
    return 0.25*nb_alea*S;
}

void affichageProbleme(Probleme prob){
    printf("Voici la liste des objets du problème :\n");
    for(int i=0; i<MAX; i++){
        printf("Objet n°%d, cout : %d, poids : %d\n", i, prob.t_objets[i].cout,prob.t_objets[i].poids);
    }
}
