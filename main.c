#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct neur {
    int *poids;
    int biais;
    struct neur* next; // Pourquoi ici ??? 
} Neurone;

typedef Neurone* neurone;

typedef struct couch {
    neurone value;
    struct couch* next;
} Couche;

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

    return somme >= n->biais ? 1 : 0;
}

Couche* InitCouche(int nbNeuronnes, int nbPoids) {
    Couche* tete = NULL;

    for (int i = 0; i < nbNeuronnes; i++) {
        Couche* nouvelleCouche = (Couche*)malloc(sizeof(Couche));
        if (nouvelleCouche == NULL) {
            perror("Erreur d'allocation mémoire pour la couche");
            exit(EXIT_FAILURE);
        }
        nouvelleCouche->value = InitNeurone(nbPoids);
        nouvelleCouche->next = NULL;

        if (tete == NULL) {
            tete = nouvelleCouche;
        } else {
            Couche* courant = tete;
            while (courant->next != NULL) {
                courant = courant->next;
            }
            courant->next = nouvelleCouche;
        }
    }

    return tete;
}

Couche Outcouche(){

};

void FreeCouche(Couche* couche) {
    while (couche != NULL) {
        Couche* temp = couche;
        couche = couche->next;

        free(temp->value->poids);
        free(temp->value);
        free(temp);
    }
}

int main() {
    // Exemple d'utilisation
    int nbPoids = 3;
    int nbNeuronnes = 5;

    Couche* couche = InitCouche(nbNeuronnes, nbPoids);

    // Exemple de calcul avec tous les neurones de la couche
    int entrees[] = {1, 2, 3};

    Couche* currentCouche = couche;
    
    int index = 0;
    
    while (currentCouche != NULL) {
        if (currentCouche->value != NULL) {
            int sortie = OutNeurone(currentCouche->value, entrees, nbPoids);
            printf("Sortie du neurone %d de la couche : %d\n", index + 1, sortie);
        }
        
        currentCouche = currentCouche->next;
        index++;
    }

    // Libération de la mémoire
    FreeCouche(couche);

    return 0;
}