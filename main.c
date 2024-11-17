#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Déclaration de la structure


typedef struct {
    int *poids;
    int biais;
}Neurone;

// fonction qui initilise le neuronne
Neurone InitNeurone (int nbPoids) {
    Neurone neurone;

    // allocation mémoire du neuronne
    neurone.poids = (int*)malloc(nbPoids * sizeof(int));
    if (neurone.poids == NULL) {
        perror("Erreur d'allocation mémoire");
        exit(EXIT_FAILURE);
    }

    // début de l'allocation aléatoire des poids et biais
    srand(time(NULL));
    for (int i = 0; i < nbPoids; i++) {
        neurone.poids[i] = rand() % 10; 
    }
    neurone.biais = rand() % 10;


    return neurone;

    
};

int  OutNeurone (Neurone neurone, int *ei, int nbPoids) {
    int somme = 0;

for (int i = 0; i < nbPoids; i++) {
    if (ei[i] == 1){
          return 1;
        }else {
             somme += ei[i] * neurone.poids[i]; // Calcul de la somme pondérée
        }   
    }
    return somme;
};

int main() {

}
