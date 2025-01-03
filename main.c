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

// Fonction pour tester les couches
void TestReseau(couche reseau, int *entrees, int nbre_couches, int *nbre_neur_couche, int nbEntrer) {
    printf("Test du réseau :\n");
    couche courant = reseau;
    int *sorties = entrees;

    for (int i = 0; i < nbre_couches; i++) {
        printf("Couche %d:\n", i + 1);

        // Afficher la composition de la couche
        printf("  Composition :\n");
        AfficherCouche(courant, nbEntrer, nbre_neur_couche[i]);

        // Calcul des sorties de la couche
        printf("  Sorties : ");
        sorties = Outcouche(courant, sorties, nbEntrer, nbre_neur_couche[i]);
        for (int j = 0; j < nbre_neur_couche[i]; j++) {
            printf("%d ", sorties[j]);
        }
        printf("\n");

        // Mise à jour des entrées et passage à la couche suivante
        nbEntrer = nbre_neur_couche[i];
        courant = courant->next;
    }
    free(sorties);
}
neurone InitNeuroneOU(int nbPoids) {
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
        n->poids[i] = 1;
    }
    n->biais = 1;

    return n;
}


couche InitCoucheOU(int nbNeurones, int nbEntrer) {
    couche tete = NULL;
    couche courant = NULL;

    for (int i = 0; i < nbNeurones; i++) {
        couche nouvelleCouche = (couche)malloc(sizeof(Couche));
        if (nouvelleCouche == NULL) {
            perror("Erreur d'allocation mémoire pour la couche");
            exit(EXIT_FAILURE);
        }

        nouvelleCouche->actuelle = InitNeuroneOU(nbEntrer); // Initialisation du neurone OU
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

void TestReseauOU(couche reseauOU, int nbEntrer) {
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

void TestReseauET(couche reseauET, int nbEntrer) {
    printf("Test du réseau ET :\n");

    // Afficher la composition du neurone ET
    AfficherCouche(reseauET, nbEntrer, 1);

    // Tester toutes les combinaisons possibles d'entrées
    int totalCombinaisons = 1 << nbEntrer; // 2^nbEntrer combinaisons
    for (int i = 0; i < totalCombinaisons; i++) {
        int entrees[nbEntrer];
        
        // Générer les entrées binaires
        for (int j = 0; j < nbEntrer; j++) {
            entrees[j] = (i >> j) & 1; // Récupérer le bit j de i
        }

        // Calculer la sortie du neurone
        int sortie = OutNeurone(reseauET->actuelle, entrees, nbEntrer);

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

couche InitCoucheET(int nbNeurones, int nbEntrer) {
    couche tete = NULL;
    couche courant = NULL;

    for (int i = 0; i < nbNeurones; i++) {
        couche nouvelleCouche = (couche)malloc(sizeof(Couche));
        if (nouvelleCouche == NULL) {
            perror("Erreur d'allocation mémoire pour la couche");
            exit(EXIT_FAILURE);
        }

        nouvelleCouche->actuelle = InitNeuroneET(nbEntrer); // Initialisation du neurone ET
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
// Fonction principale
int main() {
    srand(time(NULL));  // Initialisation du générateur de nombres aléatoires

    // Définition des paramètres du réseau
    int nbre_couches = 3;
    int nbre_neur_couche[] = {5, 4, 3};
    int nbEntrer = 3;                    // Nombre d'entrées pour la première couche
    int entrees[] = {1, 0, 1};           // Entrées pour le réseau

    // Initialisation du réseau
    couche reseau = InitReseau(nbre_couches, nbre_neur_couche, nbEntrer);

    // Test du réseau
    TestReseau(reseau, entrees, nbre_couches, nbre_neur_couche, nbEntrer);

    // Libération de la mémoire
    freeCouche(reseau);

    return 0;
}
