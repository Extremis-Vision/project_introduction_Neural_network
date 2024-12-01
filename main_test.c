#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct neur {
    int *poids;
    int biais;
} Neurone;

typedef Neurone* neurone;

typedef struct couch {
    Neurone actuelle;
    struct couch* next;
} Couche;

typedef Couche* couche;

// Fonction qui initialise le neurone
neurone InitNeurone(int nbPoids, int range) {
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
    for (int i = 0; i < nbPoids; i++) {
        n->poids[i] = rand() % range;
        printf("neurone n %d = %d\n", i, n->poids[i]);
    }
    n->biais = rand() % range;
    printf("Le biais est %d\n", n->biais);
    return n;
}

int OutNeurone(neurone n, int *ei, int nbPoids) {
    int somme = 0;

    for (int i = 0; i < nbPoids; i++) {
        somme += ei[i] * n->poids[i]; // Calcul de la somme pondérée
        printf("%d * %d", ei[i], n->poids[i]);
        if (i == (nbPoids - 1)) {
            printf(" = ");
        } else {
            printf(" + ");
        }
    }
    printf(" %d\n", somme);
    return somme >= n->biais ? 1 : 0; // Retourne 1 si la somme est positive
}

int main() {
    srand(time(NULL));  // Initialisation du générateur de nombres aléatoires une seule fois

    // Exemple d'utilisation
    int nbPoids = 3;

    // Initialisation du neurone
    int range = 2;
    neurone n = InitNeurone(nbPoids, range + 1);

    // Définition des entrées
    int entrees[] = {1, 0, 0}; // Entrée pour le neurone

    // Calcul de la sortie
    int sortie = OutNeurone(n, entrees, nbPoids);

    // Affichage du résultat
    printf("Sortie du neurone : %d\n", sortie);

    // Libération de la mémoire pour le neurone
    free(n->poids);
    free(n);
    return 0;
}
