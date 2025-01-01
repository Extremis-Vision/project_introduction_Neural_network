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

    // Initialisation aléatoire des poids et biais
    for (int i = 0; i < nbPoids; i++) {
        n->poids[i] = rand() % 10;
    }
    n->biais = rand() % 10;

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

// Fonction qui initialise une couche de neurones
couche InitCouche(int nbNeurones, int nbEntrer) {
    couche tete = NULL;
    couche courant = NULL;

    for (int i = 0; i < nbNeurones; i++) {
        couche nouvelleCouche = (couche)malloc(sizeof(Couche));
        if (nouvelleCouche == NULL) {
            perror("Erreur d'allocation mémoire pour la couche");
            exit(EXIT_FAILURE);
        }

        nouvelleCouche->actuelle = InitNeurone(nbEntrer);  // Initialisation du neurone
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

// Fonction qui libère la mémoire d'une couche
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

// Fonction qui calcule les sorties d'une couche
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

// Fonction qui initialise un réseau de couches
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

        // Les entrées pour les couches suivantes sont égales au nombre de neurones de la couche actuelle
        nbEntrer = nbre_neur_couche[i];
    }

    return tete;
}

// Fonction principale
int main() {
    srand(time(NULL));  // Initialisation du générateur de nombres aléatoires

    // Définition des paramètres du réseau
    int nbre_couches = 3;
    int nbre_neur_couche[] = {5, 4, 3};  // Nombre de neurones par couche
    int nbEntrer = 3;                    // Nombre d'entrées pour la première couche
    int entrees[] = {1, 0, 1};           // Entrées pour le réseau

    // Initialisation du réseau
    couche reseau = InitReseau(nbre_couches, nbre_neur_couche, nbEntrer);

    // Calcul des sorties du réseau (par couche)
    couche courant = reseau;
    int *sorties = entrees;
    for (int i = 0; i < nbre_couches; i++) {
        int nbNeurones = nbre_neur_couche[i];
        sorties = Outcouche(courant, sorties, nbEntrer, nbNeurones);
        nbEntrer = nbNeurones;  // Mise à jour des entrées pour la couche suivante
        courant = courant->next;
    }

    // Libération de la mémoire
    free(sorties);
    freeCouche(reseau);

    return 0;
}
