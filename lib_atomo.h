
#include "lib_header.h"


struct Atomo crea_atomo() {
    printf("sto iniziando a creare un atomo\n");
    struct Atomo nuovo_atomo;
    nuovo_atomo.numero_atomico = (rand() % var->N_ATOM_MAX) + 1;
    printf("atomo creato\n");
    return nuovo_atomo;
    
}

int energy(int n1, int n2) {
    return n1 * n2 - (n1 > n2 ? n1 : n2);
}

/*struct Var *attshm() {
    key_t KEY = ftok("cazzi.c", 'a');   
    int shmid = shmget(KEY, sizeof(struct Var), IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    // Collegamento all'area di memoria condivisa
    struct Var *sharedVar = (struct Var *)shmat(shmid, NULL, 0);
    if (sharedVar == (void *)-1) {
        perror("shmat");
        exit(1);
    }

    return sharedVar;
}*/
 
void simulateFission(struct Atomo *padre) {
    // Verifica se il numero atomico è minore o uguale a MIN_N_ATOMICO
    if (padre->numero_atomico <= var->MIN_N_ATOMICO) {
        
        var->scorie=var->scorie+1;
       
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
        //printf("Scissione avvenuta. Numero atomico figlio: %fd\n", figlio.numero_atomico);

        // Calcola l'energia liberata durante la scissione
        int releaseEnergy = energy(padre->numero_atomico, figlio.numero_atomico);
        
        var->enrgia=var->enrgia+releaseEnergy;
     

        



        printf("Energia liberata: %d\n", releaseEnergy);
        printf("dopo la scissione padre: %d figlio %d",padre->numero_atomico,figlio.numero_atomico);
        /*comunicare l'energia alla centrale*/

        exit(EXIT_SUCCESS);
    } else {
        // Processo padre
        wait(NULL);
        
    }

}
