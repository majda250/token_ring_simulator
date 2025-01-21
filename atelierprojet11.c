#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NOEUDS 10
#define JETON_INIT 1
typedef struct {
    char jeton[3];
    int id_emetteur;
} TrameJeton;
bool est_noeud_actif(int id_noeud) {
    return id_noeud != 2;
}
void simulation_anneau_jeton(int nb_noeuds) {
    int canaux[MAX_NOEUDS][2];
    pid_t pids[MAX_NOEUDS];
    for (int i = 0; i < nb_noeuds; i++) {
        if (pipe(canaux[i]) == -1) {
            perror("Erreur lors de la creation du canal");
            exit(1);
        }
    }
    for (int i = 0; i < nb_noeuds; i++) {
        pid_t pid = fork();
        if (pid < 0) {
            perror("Erreur lors du fork");
            exit(1);
        }
 
