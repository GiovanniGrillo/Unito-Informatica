#include <stdio.h>
#define MIN_N_ATOMICO 3
#define NATOM_MAX 10

struct Atomo crea_atomo() {
    struct Atomo nuovo_atomo;
    nuovo_atomo.numero_atomico = (rand() % NATOM_MAX) + 1;
    return nuovo_atomo;
}

int energy(int n1, int n2) {
    return n1 * n2 - (n1 > n2 ? n1 : n2);
}
 
void simulateFission(struct Atomo *padre) {
    // Verifica se il numero atomico è minore o uguale a MIN_N_ATOMICO
    if (padre->numero_atomico <= MIN_N_ATOMICO) {
        printf("Atomo con numero atomico minore o uguale a MIN_N_ATOMICO. Terminato e conteggiato nelle statistiche fra le scorie.\n");
        return;
    }

    // Fork per creare un nuovo atomo (processo figlio)
    pid_t pid = fork();

    if (pid == -1) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Processo figlio
        int numero_casuale = rand() % padre->numero_atomico + 1;
        printf("Processo padre  con numero atomico: %d\n", padre->numero_atomico);


        struct Atomo figlio = {(padre->numero_atomico)-numero_casuale};
        padre->numero_atomico =(padre->numero_atomico -(figlio.numero_atomico));
        printf("Processo figlio creato con numero atomico: %d\n", figlio.numero_atomico);
        
        // Simula la scissione
        //printf("Scissione avvenuta. Numero atomico figlio: %d\n", figlio.numero_atomico);

        // Calcola l'energia liberata durante la scissione
        int releaseEnergy = energy(padre->numero_atomico, figlio.numero_atomico);
        printf("Energia liberata: %d\n", releaseEnergy);
        printf("dopo la scissione padre: %d figlio %d",padre->numero_atomico,figlio.numero_atomico);
        /*comunicare l'energia alla centrale*/

        exit(EXIT_SUCCESS);
    } else {
        // Processo padre
        wait(NULL);
        
    }
}