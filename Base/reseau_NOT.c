#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Définition de la structure Neurone
typedef struct neur {
    int *poids;
    int biais;
} Neurone;
typedef Neurone* neurone;

// Définition de la structure Couche
typedef struct couch {
    neurone actuelle;
    struct couch* next;
} Couche;
typedef Couche* couche;

// Fonction qui initialise un neurone
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

    // Initialisation des poids et biais aléatoires
    for (int i = 0; i < nbPoids; i++) {
        n->poids[i] = rand() % 10;
    }
    n->biais = rand() % 10;

    return n;
}

// Fonction pour initialiser un neurone OU
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

    // Poids fixés à 1 et biais fixé à 1 (seuil minimum pour une opération OU)
    for (int i = 0; i < nbPoids; i++) {
        n->poids[i] = -1;
    }
    n->biais = 0;

    return n;
}

// Fonction qui calcule la sortie d'un neurone
int OutNeurone(neurone n, int *ei, int nbEntrer) {
    int somme = 0;
    for (int i = 0; i < nbEntrer; i++) {
        somme += ei[i] * n->poids[i];
    }
    return somme >= n->biais ? 1 : 0; // Retourne 1 si la somme dépasse le biais
}

// Fonction pour initialiser une couche spécifique au réseau OU
couche InitCoucheNOT(int nbNeurones, int nbEntrer) {
    couche tete = NULL;
    couche courant = NULL;

    for (int i = 0; i < nbNeurones; i++) {
        couche nouvelleCouche = (couche)malloc(sizeof(Couche));
        if (nouvelleCouche == NULL) {
            perror("Erreur d'allocation mémoire pour la couche");
            exit(EXIT_FAILURE);
        }

        nouvelleCouche->actuelle = InitNeuroneNOT(nbEntrer); // Initialisation du neurone OU
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

// Fonction pour afficher la composition d'une couche
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

// Fonction pour tester un réseau OU
void TestReseauNOT(couche reseauOU, int nbEntrer) {
    printf("Test du réseau OU :\n");

    // Afficher la composition du neurone OU
    AfficherCouche(reseauOU, nbEntrer, 1);

    // Tester toutes les combinaisons possibles d'entrées
    int totalCombinaisons = 1 << nbEntrer; // 2^nbEntrer combinaisons
    for (int i = 0; i < totalCombinaisons; i++) {
        int entrees[nbEntrer];
        
        // Générer les entrées binaires
        for (int j = 0; j < nbEntrer; j++) {
            entrees[j] = (i >> j) & 1; // Récupérer le bit j de i
        }

        // Calculer la sortie du neurone
        int sortie = OutNeurone(reseauOU->actuelle, entrees, nbEntrer);

        // Afficher les entrées et la sortie correspondante
        printf("Entrées : [");
        for (int j = 0; j < nbEntrer; j++) {
            printf("%d", entrees[j]);
            if (j < nbEntrer - 1) {
                printf(", ");
            }
        }
        printf("] -> Sortie : %d\n", sortie);
    }
}

// Fonction pour libérer la mémoire d'une couche
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

// Fonction principale
int main() {
    srand(time(NULL));  // Initialisation du générateur de nombres aléatoires

    // Réseau OU avec 3 entrées
    int nbEntrer = 1;  // Nombre d'entrées
    couche reseauNOT = InitCoucheNOT(1, nbEntrer); // 1 neurone pour le réseau OU

    // Test du réseau OU
    TestReseauNOT(reseauNOT, nbEntrer);

    // Libération de la mémoire
    freeCouche(reseauNOT);

    return 0;
}
