#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// === Définition des structures ===
typedef struct {
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
// OU
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


// ET 


neurone InitNeuroneET(int nbPoids) {
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

    // Poids fixés à 1 et biais fixé au nombre d'entrées (nbPoids)
    for (int i = 0; i < nbPoids; i++) {
        n->poids[i] = 1;
    }
    n->biais = nbPoids;

    return n;
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

// vider les réseaux
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

// === Fonction principale ===
int main() {
    srand(time(NULL));

    // Définir les entrées possibles
    int entrees[8][3] = {
        {0, 0, 0}, {0, 0, 1}, {0, 1, 0}, {0, 1, 1},
        {1, 0, 0}, {1, 0, 1}, {1, 1, 0}, {1, 1, 1}
    };

    // === Tester la fonction ET ===
// === Tester la fonction ET ===
    printf("Test de la fonction ET :\n");
    couche reseauET = InitCoucheET(1, 2); // 1 neurone pour l'opération ET, 2 entrées
    for (int i = 0; i < 4; i++) {
        int A = i / 2;  // Premier bit : 0, 0, 1, 1
        int B = i % 2;  // Second bit  : 0, 1, 0, 1
        int *sortiesET = Outcouche(reseauET, (int[]){A, B}, 2, 1);  // Calcul de la sortie
        printf("Entrée: A = %d, B = %d | Sortie ET : %d\n", A, B, sortiesET[0]);
        free(sortiesET);
    }
    freeCouche(reseauET);

       // === Tester la fonction OU ===
    printf("\nTest de la fonction OU :\n");
    couche reseauOU = InitCoucheOU(1, 2); // 1 neurone pour l'opération OU, 2 entrées
    for (int i = 0; i < 4; i++) {
        int A = i / 2;  // Premier bit : 0, 0, 1, 1
        int B = i % 2;  // Second bit  : 0, 1, 0, 1
        int *sortiesOU = Outcouche(reseauOU, (int[]){A, B}, 2, 1);  // Calcul de la sortie
        printf("Entrée: A = %d, B = %d | Sortie OU : %d\n", A, B, sortiesOU[0]);
        free(sortiesOU);
    }
    freeCouche(reseauOU);

    // === Tester la fonction NOT ===
    printf("\nTest de la fonction NOT :\n");
    couche reseauNOT = InitCoucheNOT(1, 1); // 1 neurone pour l'opération NOT, 1 entrée
    for (int i = 0; i < 2; i++) {
        int A = i;  // A = 0 ou 1
        int *sortiesNOT = Outcouche(reseauNOT, (int[]){A}, 1, 1);  // Calcul de la sortie
        printf("Entrée: A = %d | Sortie NOT : %d\n", A, sortiesNOT[0]);
        free(sortiesNOT);
    }
    freeCouche(reseauNOT);

    // === Tester l'expression (A ET (non B) ET C) OU (A ET (non C)) ===
    printf("\nTest de l'expression (A ET (non B) ET C) OU (A ET (non C)) :\n");

    // Initialisation des couches nécessaires
    couche reseauET1 = InitCoucheET(1, 2);  // Pour A ET (non B)
    couche reseauET2 = InitCoucheET(1, 2);  // Pour le résultat de la première ET combinée avec C
    couche reseauOUFinal = InitCoucheOU(1, 2); // Pour le OU final
    couche reseauNOT_B = InitCoucheNOT(1, 1); // Pour NOT B
    couche reseauNOT_C = InitCoucheNOT(1, 1); // Pour NOT C

    for (int i = 0; i < 8; i++) {
        int A = entrees[i][0];
        int B = entrees[i][1];
        int C = entrees[i][2];

        // Calculer NOT B
        int *sortieNOT_B = Outcouche(reseauNOT_B, (int[]){B}, 1, 1);

        // Calculer A ET (non B)
        int *sortieET1 = Outcouche(reseauET1, (int[]){A, sortieNOT_B[0]}, 2, 1);

        // Calculer A ET (non B) ET C
        int *sortieET2 = Outcouche(reseauET2, (int[]){sortieET1[0], C}, 2, 1);

        // Calculer NOT C
        int *sortieNOT_C = Outcouche(reseauNOT_C, (int[]){C}, 1, 1);

        // Calculer A ET (non C)
        int *sortieET3 = Outcouche(reseauET1, (int[]){A, sortieNOT_C[0]}, 2, 1);

        // Calculer le OU final : (A ET (non B) ET C) OU (A ET (non C))
        int *sortieOU = Outcouche(reseauOUFinal, (int[]){sortieET2[0], sortieET3[0]}, 2, 1);

        // Afficher les résultats
        printf("Entrées: A = %d, B = %d, C = %d | Sortie = %d\n", A, B, C, sortieOU[0]);

        // Libérer les mémoires intermédiaires
        free(sortieNOT_B);
        free(sortieET1);
        free(sortieET2);
        free(sortieNOT_C);
        free(sortieET3);
        free(sortieOU);
    }

    // Libération des couches
    freeCouche(reseauET1);
    freeCouche(reseauET2);
    freeCouche(reseauOUFinal);
    freeCouche(reseauNOT_B);
    freeCouche(reseauNOT_C);

    return 0;
}
