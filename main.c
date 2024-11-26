#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct neur {
    int *poids;
    int biais;
    struct neur* next;
} Neurone;

typedef Neurone* neurone;

// Fonction qui initialise le neurone
neurone InitNeurone(int nbPoids) {
    neurone n = (neurone)malloc(sizeof(Neurone));
    if (n == NULL) {
        perror("Erreur d'allocation mémoire pour le neurone");
        exit(EXIT_FAILURE);
    }

    n->poids = (int*)malloc(nbPoids * sizeof(int));
    if (n->poids == NULL) {
        perror("Erreur d'allocation mémoire pour les poids");
        free(n);
        exit(EXIT_FAILURE);
    }

    // Initialisation aléatoire des poids et biais
    srand(time(NULL));
    for (int i = 0; i < nbPoids; i++) {
        n->poids[i] = rand() % 10;
    }
    n->biais = rand() % 10;
    n->next = NULL;

    return n;
}

int OutNeurone(neurone n, int *ei, int nbPoids) {
    int somme = 0;


    for (int i = 0; i < nbPoids; i++) {
        somme += ei[i] * n->poids[i]; // Calcul de la somme pondérée
    }
    somme += n->biais; // Ajout du biais

    if (somme >=n->biais){
        return 1;
    }
    return 0;
}

int main() {
    // Exemple d'utilisation
    int nbPoids = 3;
    neurone n = InitNeurone(nbPoids);
    
    int entrees[] = {1, 2, 3};
    int sortie = OutNeurone(n, entrees, nbPoids);
    
    printf("Sortie du neurone : %d\n", sortie);

    // Libération de la mémoire
    free(n->poids);
    free(n);

    return 0;
}