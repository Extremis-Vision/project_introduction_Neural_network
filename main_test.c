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
        printf("neurone n %d = %d\n", i, n->poids[i]);
    }
    n->biais = rand() % 10;
    printf("Le biais est %d\n", n->biais);
    return n;
}

// Fonction qui initialise une couche de neurones
couche InitCouche(int nbNeurones, int nbEntrer) {
    Couche* tete = NULL;
    Couche* courant = NULL;

    for (int i = 0; i < nbNeurones; i++) {
        Couche* nouvelleCouche = (Couche*)malloc(sizeof(Couche));
        if (nouvelleCouche == NULL) {
            perror("Erreur d'allocation mémoire pour la couche");
            exit(EXIT_FAILURE);
        }
        nouvelleCouche->actuelle = *InitNeurone(nbEntrer);  // Initialisation du neurone
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
    Couche* current = c;
    while (current != NULL) {
        Couche* next = current->next;
        free(current->actuelle.poids);  // Libérer la mémoire des poids
        free(current);  // Libérer la mémoire de la couche
        current = next;
    }
}



// Fonction pour calculer les sorties pour une couche de neurones
int *Outcouche(couche c, int *ei, int nbEntrer) {
    int *liste = (int *)malloc(nbEntrer * sizeof(int));  // Allocation de mémoire pour la liste

    if (liste == NULL) {
        printf("Erreur d'allocation de mémoire !\n");
        return NULL;  // Retourner NULL si l'allocation échoue
    }

    Couche* current = c;  // Conserver un pointeur séparé pour itérer dans la couche

    for (int i = 0; i < nbEntrer; i++) {
        // Appliquer l'opération OutNeurone sur le neurone actuel
        liste[i] = OutNeurone(&current->actuelle, ei, nbEntrer);  // Passer l'adresse du neurone
        printf("Sortie du neurone : %d\n", liste[i]);
        current = current->next;  // Passer au neurone suivant dans la couche
    }

    // Afficher les valeurs dans liste
    printf("Liste des sorties : ");
    for (int i = 0; i < nbEntrer; i++) {
        printf("%d ", liste[i]);
    }
    printf("\n");

    return liste;  // Retourner la liste des sorties
}

int OutNeurone(Neurone *n, int *ei, int nbEntrer) {
    int somme = 0;
    for (int i = 0; i < nbEntrer; i++) {
        somme += ei[i] * n->poids[i];
    }
    return somme + n->biais;  // Calcul de la sortie du neurone
}


int main() {
    srand(time(NULL));  // Initialisation du générateur de nombres aléatoires une seule fois

    // Exemple d'utilisation
    int nbPoids = 3;

    // Initialisation du neurone
    neurone n = InitNeurone(nbPoids);

    // Définition des entrées
    int entrees[] = {1, 0, 0}; // Entrée pour le neurone

    // Calcul de la sortie
    int sortie = OutNeurone(n, entrees, nbPoids);

    // Affichage du résultat
    printf("Sortie du neurone : %d\n", sortie);

    // Libération de la mémoire pour le neurone
    free(n->poids);
    free(n);

    // Initialisation d'une couche de neurones
    int nbNeurones = 5;
    couche c = InitCouche(nbNeurones, nbPoids);

    // Définition des entrées pour la couche
    int entreesCouche[] = {1, 0, 0}; // Entrée pour chaque neurone dans la couche

    // Calcul des sorties de la couche
    int *sorties = Outcouche(c, entreesCouche, nbNeurones);

    // Libération de la mémoire pour la couche
    free(sorties);  // Libérer les sorties
    freeCouche(c);  // Libérer la mémoire pour la couche de neurones

    return 0;
}
