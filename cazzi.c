#include <stdio.h>
#include <stdlib.h> // Per la funzione malloc
#include <sys/ipc.h>
#include <sys/shm.h>
#include "Oggetti.h"


// Definizione della struttura dati condivisa


// Funzione per attaccare l'area di memoria condivisa
struct Var *attshm() {
    key_t KEY = 1234; // Chiave arbitraria
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
}
struct Atomo crea_atomo() {
    printf("sto iniziando a creare un atomo\n");
    struct Atomo nuovo_atomo;
    nuovo_atomo.numero_atomico = (Var.ENERGY_DEMAND);
    printf("atomo creato\n");
    return nuovo_atomo;
    
}

int main() {
    // Attacca l'area di memoria condivisa
    struct Var *sharedVar = attshm();

    // Inizializzazione dei valori
    sharedVar->ENERGY_DEMAND = 100;
    sharedVar->N_ATOMI_INIT = 10;
    sharedVar->N_ATOM_MAX = 20;
    sharedVar->MIN_N_ATOMICO = 5;
    sharedVar->STEP_ALIMENTAZIONE = 2;
    sharedVar->ENERGY_EXPLODE_THRESHOLD = 50;
    sharedVar->flagTerminazione = 0;



    struct Atomo Iniziale =crea_atomo(); 
    printf("%d\n",Iniziale.numero_atomico);



    printf("Valore : %d\n", sharedVar->ENERGY_DEMAND);
    

    // Stacca l'area di memoria condivisa
    shmdt(sharedVar);


    struct Var *sharedVar2 = attshm();
     sharedVar2->flagTerminazione=10;
     printf("valore :%d\n",sharedVar2->flagTerminazione);
    shmdt(sharedVar2);


    // Rimuovi completamente l'area di memoria condivisa (se necessario)
    // shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
