#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// === Définition des structures ===
typedef struct neur {
    int *poids;
    int biais;
} Neurone;
typedef Neurone* neurone;

typedef struct couch {
    neurone actuelle;
    struct couch* next;
} Couche;
typedef Couche* couche;

// === Fonctions d'initialisation ===

// Initialisation d'un neurone aléatoire
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

    for (int i = 0; i < nbPoids; i++) {
        n->poids[i] = rand() % 10;
    }
    n->biais = rand() % 10;

    return n;
}

// Initialisation d'une couche de neurones
couche InitCouche(int nbNeurones, int nbEntrer) {
    couche tete = NULL;
    couche courant = NULL;

    for (int i = 0; i < nbNeurones; i++) {
        couche nouvelleCouche = (couche)malloc(sizeof(Couche));
        if (nouvelleCouche == NULL) {
            perror("Erreur d'allocation mémoire pour la couche");
            exit(EXIT_FAILURE);
        }

        nouvelleCouche->actuelle = InitNeurone(nbEntrer);
        nouvelleCouche->next = NULL;

        if (tete == NULL) {
            tete = nouvelleCouche;
        } else {
            courant->next = nouvelleCouche;
        }
        courant = nouvelleCouche;
    }

    return tete;
}

// Initialisation d'un réseau
couche InitReseau(int nbre_couches, int *nbre_neur_couche, int nbEntrer) {
    couche tete = NULL;
    couche courant = NULL;

    for (int i = 0; i < nbre_couches; i++) {
        couche nouvelleCouche = InitCouche(nbre_neur_couche[i], nbEntrer);
        if (tete == NULL) {
            tete = nouvelleCouche;
        } else {
            courant->next = nouvelleCouche;
        }
        courant = nouvelleCouche;

        nbEntrer = nbre_neur_couche[i]; // Mise à jour des entrées
    }

    return tete;
}

// Initialisation d'un neurone NOT
neurone InitNeuroneNOT(int nbPoids) {
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

    for (int i = 0; i < nbPoids; i++) {
        n->poids[i] = -1; // Poids pour inverser l'entrée
    }
    n->biais = 0;

    return n;
}

// Initialisation d'une couche NOT
couche InitCoucheNOT(int nbNeurones, int nbEntrer) {
    couche tete = NULL;
    couche courant = NULL;

    for (int i = 0; i < nbNeurones; i++) {
        couche nouvelleCouche = (couche)malloc(sizeof(Couche));
        if (nouvelleCouche == NULL) {
            perror("Erreur d'allocation mémoire pour la couche");
            exit(EXIT_FAILURE);
        }

        nouvelleCouche->actuelle = InitNeuroneNOT(nbEntrer);
        nouvelleCouche->next = NULL;

        if (tete == NULL) {
            tete = nouvelleCouche;
        } else {
            courant->next = nouvelleCouche;
        }
        courant = nouvelleCouche;
    }

    return tete;
}

// === Fonctions de calcul et affichage ===

// Calcul de la sortie d'un neurone
int OutNeurone(neurone n, int *ei, int nbEntrer) {
    int somme = 0;
    for (int i = 0; i < nbEntrer; i++) {
        somme += ei[i] * n->poids[i];
    }
    return somme >= n->biais ? 1 : 0;
}

// Calcul des sorties d'une couche
int *Outcouche(couche coucheEntre, int *ei, int nbEntrer, int nbNeurones) {
    int *sorties = (int *)malloc(nbNeurones * sizeof(int));
    if (sorties == NULL) {
        perror("Erreur d'allocation mémoire pour les sorties");
        exit(EXIT_FAILURE);
    }

    couche courant = coucheEntre;
    for (int i = 0; i < nbNeurones; i++) {
        sorties[i] = OutNeurone(courant->actuelle, ei, nbEntrer);
        courant = courant->next;
    }

    return sorties;
}

// Affichage des paramètres d'une couche
void AfficherCouche(couche coucheEntre, int nbEntrer, int nbNeurones) {
    couche courant = coucheEntre;
    for (int i = 0; i < nbNeurones; i++) {
        printf("  Neurone %d : Poids [", i + 1);
        for (int j = 0; j < nbEntrer; j++) {
            printf("%d", courant->actuelle->poids[j]);
            if (j < nbEntrer - 1) {
                printf(", ");
            }
        }
        printf("], Biais = %d\n", courant->actuelle->biais);
        courant = courant->next;
    }
}


void freeCouche(couche c) {
    couche courant = c;
    while (courant != NULL) {
        couche suivant = courant->next;
        free(courant->actuelle->poids);  // Libérer les poids
        free(courant->actuelle);        // Libérer le neurone
        free(courant);                  // Libérer la couche
        courant = suivant;
    }
}

// Test du réseau général
void TestReseau(couche reseau, int *entrees, int nbre_couches, int *nbre_neur_couche, int nbEntrer) {
    printf("Test du réseau :\n");
    couche courant = reseau;
    int *sorties = entrees;

    for (int i = 0; i < nbre_couches; i++) {
        printf("Couche %d:\n", i + 1);
        AfficherCouche(courant, nbEntrer, nbre_neur_couche[i]);
        sorties = Outcouche(courant, sorties, nbEntrer, nbre_neur_couche[i]);
        printf("  Sorties : ");
        for (int j = 0; j < nbre_neur_couche[i]; j++) {
            printf("%d ", sorties[j]);
        }
        printf("\n");
        nbEntrer = nbre_neur_couche[i];
        courant = courant->next;
    }
    free(sorties);
}

// === Fonction principale ===
int main() {
    srand(time(NULL));

    // Définir les entrées possibles
    int entrees[4][2] = {
        {0, 0}, {0, 1}, {1, 0}, {1, 1}
    };

    // Tester la fonction AND
    printf("Test de la fonction AND :\n");
    for (int i = 0; i < 4; i++) {
        int A = entrees[i][0];
        int B = entrees[i][1];
        int sortieAND = A & B;
        printf("Entrée: A = %d, B = %d | Sortie: %d\n", A, B, sortieAND);
    }

    // Tester la fonction OR
    printf("\nTest de la fonction OR :\n");
    for (int i = 0; i < 4; i++) {
        int A = entrees[i][0];
        int B = entrees[i][1];
        int sortieOR = A | B;
        printf("Entrée: A = %d, B = %d | Sortie: %d\n", A, B, sortieOR);
    }

    // Tester la fonction NOT
    printf("\nTest de la fonction NOT :\n");
    for (int i = 0; i < 2; i++) {
        int A = i;
        int sortieNOT = !A;
        printf("Entrée: A = %d | Sortie: %d\n", A, sortieNOT);
    }

    // Tester un réseau multicouche avec A, B, C
    printf("\nTest d'un réseau multicouche avec A, B, C :\n");
    int entreesABC[8][3] = {
        {0, 0, 0}, {0, 0, 1}, {0, 1, 0}, {0, 1, 1},
        {1, 0, 0}, {1, 0, 1}, {1, 1, 0}, {1, 1, 1}
    };

    for (int i = 0; i < 8; i++) {
        int A = entreesABC[i][0];
        int B = entreesABC[i][1];
        int C = entreesABC[i][2];

        // Exemple : une logique qui combine les fonctions AND et OR
        int sortie1 = A & B;       // A AND B
        int sortie2 = sortie1 | C; // (A AND B) OR C

        printf("Entrée: A = %d, B = %d, C = %d | Sortie: %d\n", A, B, C, sortie2);
    }

    return 0;
}
