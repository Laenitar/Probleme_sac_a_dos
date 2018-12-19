#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100

typedef struct{
    unsigned int cout;
    unsigned int poids;
}Objet;

typedef Objet tab[MAX];

typedef struct{
    tab t_objets;
    float b;
}Probleme;

float calculB(tab t, unsigned int n);

int main(int argc, char const *argv[]) {
    printf("Hello THE World");
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
