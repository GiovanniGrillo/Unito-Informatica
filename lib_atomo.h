#include <stdio.h>
#include <sched.h>


struct Atomo crea_atomo() {
    printf("sto iniziando a creare un atomo");
    struct Atomo nuovo_atomo;
    nuovo_atomo.numero_atomico = (rand() % Var.N_ATOM_MAX) + 1;
    return nuovo_atomo;
    printf("atomo creato");
}

int energy(int n1, int n2) {
    return n1 * n2 - (n1 > n2 ? n1 : n2);
}
 
void simulateFission(struct Atomo *padre) {
    // Verifica se il numero atomico è minore o uguale a MIN_N_ATOMICO
    if (padre->numero_atomico <= Var.MIN_N_ATOMICO) {
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
        printf("Processo padre  con numero atomico: %f\n", padre->numero_atomico);


        struct Atomo figlio = {(padre->numero_atomico)-numero_casuale};
        padre->numero_atomico =(padre->numero_atomico -(figlio.numero_atomico));
        printf("Processo figlio creato con numero atomico: %f\n", figlio.numero_atomico);
        
        // Simula la scissione
        //printf("Scissione avvenuta. Numero atomico figlio: %fd\n", figlio.numero_atomico);

        // Calcola l'energia liberata durante la scissione
        int releaseEnergy = energy(padre->numero_atomico, figlio.numero_atomico);
        printf("Energia liberata: %f\n", releaseEnergy);
        printf("dopo la scissione padre: %f figlio %f",padre->numero_atomico,figlio.numero_atomico);
        /*comunicare l'energia alla centrale*/

        exit(EXIT_SUCCESS);
    } else {
        // Processo padre
        wait(NULL);
        
    }
}