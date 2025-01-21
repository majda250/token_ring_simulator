#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define NOMBRE_NOEUDS 5  
#define JETON_INITIAL 1 
int main() {
    int canaux[NOMBRE_NOEUDS][2]; 
    int jeton = JETON_INITIAL;  
    pid_t pid;
    for (int i = 0; i < NOMBRE_NOEUDS; i++) {
        if (pipe(canaux[i]) == -1) {
            perror("Erreur lors de la création du canal");
            exit(1);
        }
    }
    for (int i = 0; i < NOMBRE_NOEUDS; i++) {
        pid = fork();
        if (pid < 0) {
            perror("Erreur lors du fork");
            exit(1);
        }
        if (pid == 0) {  
            int jeton_recu;
