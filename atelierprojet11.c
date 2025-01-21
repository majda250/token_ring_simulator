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
         if (pid == 0) {
            TrameJeton jeton_recu;
            while (1) {
                read(canaux[i][0], &jeton_recu, sizeof(jeton_recu));
                printf("Noeud %d : Jeton recu de %d\n", i, jeton_recu.id_emetteur);
                if (!est_noeud_actif(i)) {
                    printf("Noeud %d est en panne. Passage du jeton.\n", i);
                }
                else {
                    if (rand() % 2) {
                        printf("Noeud %d : Envoi des donnees.\n", i);
                        sleep(1);
                    }
                    else {
                        printf("Noeud %d : Aucune donnee a transmettre.\n", i);
                    }
                }
                int noeud_suivant = (i + 1) % nb_noeuds;
                jeton_recu.id_emetteur = i;
                write(canaux[noeud_suivant][1], &jeton_recu, sizeof(jeton_recu));

                sleep(1);
            }
            exit(0);
        }
        else {
            pids[i] = pid;
        }
    }
    TrameJeton jeton = { {1, 0, 0}, -1 };
    printf("Demarrage de la simulation de l'anneau a jeton avec %d noeuds.\n", nb_noeuds);
    write(canaux[0][1], &jeton, sizeof(jeton));
    for (int i = 0; i < nb_noeuds; i++) {
        wait(NULL);
    }
}

int main() {
    int nb_noeuds;

    printf("Entrez le nombre de noeuds (max %d) : ", MAX_NOEUDS);
    scanf("%d", &nb_noeuds);

    if (nb_noeuds <= 0 || nb_noeuds > MAX_NOEUDS) {
        printf("Le nombre de noeuds doit etre entre 1 et %d.\n", MAX_NOEUDS);
        return 1;
    }
    srand(getpid());
    simulation_anneau_jeton(nb_noeuds);
    return 0;
}

