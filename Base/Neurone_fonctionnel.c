#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Définition de la structure Neurone :
typedef struct neur {
    int *poids;
    int biais;
} Neurone;

typedef Neurone* neurone;

// Définition de la structure Couche :
typedef struct couch {
    Neurone actuelle;
    struct couch* next;
} Couche;

typedef Couche* couche;

// Définition de l'initialisation des neurones : 
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
    for (int i = 0; i < nbPoids; i++) {
        n->poids[i] = rand() % 10;
        printf("Poids[%d] = %d\n", i, n->poids[i]);
    }
    n->biais = rand() % 10;
    printf("Le biais est : %d\n", n->biais);
    return n;
}

// Définition de la fonction sortie des neurones : 
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
    printf("%d\n", somme);
    return somme >= n->biais ? 1 : 0; // Retourne 1 si la somme est >= au biais
}

int main() {
    srand(time(NULL));  // Initialisation du générateur de nombres aléatoires

    // Nombre de poids (entrées)
    int nbPoids = 3;

    // Initialisation du neurone
    printf("Initialisation du neurone...\n");
    neurone n = InitNeurone(nbPoids);

    // Définition des entrées
    int entrees[] = {1, 0, 0}; // Exemple d'entrées
    printf("\nEntrées pour le neurone : ");
    for (int i = 0; i < nbPoids; i++) {
        printf("%d ", entrees[i]);
    }
    printf("\n");

    // Calcul de la sortie
    printf("\nCalcul de la sortie...\n");
    int sortie = OutNeurone(n, entrees, nbPoids);
    printf("Sortie du neurone : %d\n", sortie);

    // Libération de la mémoire pour le neurone
    free(n->poids);
    free(n);

    return 0;
}
