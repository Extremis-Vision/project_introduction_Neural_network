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

// Fonction qui calcule la sortie du neurone
int OutNeurone(neurone n, int *ei) {
    int somme = 0,nbPoids = sizeof(ei);
    for (int i = 0; i < (nbPoids-1); i++) {
        somme += ei[i] * n->poids[i]; // Calcul de la somme pondérée
        printf("%d * %d", ei[i], n->poids[i]);
        if (i == (nbPoids - 2)) {
            printf(" = ");
        } else {
            printf(" + ");
        }
    }
    printf(" %d\n", somme);
    return somme >= n->biais ? 1 : 0; // Retourne 1 si la somme est positive
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

// Fonction qui calcule les sorties de la couche
int *Outcouche(couche coucheEntre, int *ei) {
    int *liste = (int *)malloc( sizeof(ei) * sizeof(int));  // Allocation de mémoire pour la liste
    int i = 0;

    if (liste == NULL) {
        printf("Erreur d'allocation de mémoire !\n");
        return NULL;  // Retourner NULL si l'allocation échoue
    }

    while (&coucheEntre->actuelle != NULL) {
        liste[i] = OutNeurone(&coucheEntre->actuelle, ei);
        i++;
        coucheEntre = coucheEntre->next;  // Passer au neurone suivant dans la couche
    }

    // Afficher les valeurs dans liste
    printf("Liste des sorties : ");
    for (int i = 0; i < sizeof(ei); i++) {
        printf("%d ", liste[i]);
    }
    printf("\n");

    return liste;  // Retourner la liste des sorties
}

int main() {
    srand(time(NULL));  // Initialisation du générateur de nombres aléatoires une seule fois

    // Exemple d'utilisation
    int nbPoids = 3;

    // Définition des entrées
    int entrees[] = {1, 0, 0}; // Entrée pour le neurone

    // Initialisation d'une couche de neurones
    int nbNeurones = 5;
    couche c = InitCouche(nbNeurones, nbPoids);

    // Calcul des sorties de la couche
    int *sorties = Outcouche(c, entrees);

    // Libération de la mémoire pour la couche
    free(sorties);  // Libérer les sorties
    freeCouche(c);  // Libérer la mémoire pour la couche de neurones

    return 0;
}
