#include <stdio.h>
#include <stdlib.h> // Per la funzione malloc
#include <sys/ipc.h>
#include <sys/shm.h>

// Definizione della struttura dati condivisa
struct Var {
    int ENERGY_DEMAND;
    int N_ATOMI_INIT;
    int N_ATOM_MAX;
    int MIN_N_ATOMICO;
    int STEP_ALIMENTAZIONE;
    int ENERGY_EXPLODE_THRESHOLD;
    int flagTerminazione;
};

int main() {
    key_t KEY = 1234; // Chiave arbitraria
    int shmid = shmget(KEY, sizeof(struct Var), IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        return 1;
    }

    // Collegamento all'area di memoria condivisa
    struct Var *sharedVar = (struct Var *)shmat(shmid, 0, 0);
    if (sharedVar == (void *)-1) {
        perror("shmat");
        return 1;
    }

    // Inizializzazione dei valori
    sharedVar->ENERGY_DEMAND = 100;
    sharedVar->N_ATOMI_INIT = 10;
    sharedVar->N_ATOM_MAX = 20;
    sharedVar->MIN_N_ATOMICO = 5;
    sharedVar->STEP_ALIMENTAZIONE = 2;
    sharedVar->ENERGY_EXPLODE_THRESHOLD = 50;
    sharedVar->flagTerminazione = 0;

    // Ora puoi utilizzare l'area di memoria condivisa come necessario

    // Stacca l'area di memoria condivisa
    shmdt(sharedVar);

    // Rimuovi completamente l'area di memoria condivisa (se necessario)
    // shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
