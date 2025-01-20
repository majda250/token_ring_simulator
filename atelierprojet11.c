#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // Pour la fonction sleep()
#include <stdbool.h> // Pour utiliser le type bool
#include <time.h> // Pour générer des nombres aléatoires

// Fonction pour simuler une transmission aléatoire de données
bool has_data_to_transmit() {
    return rand() % 2; // Retourne true (1) ou false (0) de manière aléatoire
}

// Fonction pour simuler le réseau Token Ring
void token_ring_simulation(int num_nodes) {
    int current_token = 0;

    while (1) {
        printf("\nNode %d has the token.\n", current_token);

        // Vérifier si le nœud a des données à transmettre
        if (has_data_to_transmit()) {
            printf("Node %d is transmitting data...\n", current_token);
            sleep(1); // Simule le temps de transmission
            printf("Node %d has finished transmitting.\n", current_token);
        }
    }
}