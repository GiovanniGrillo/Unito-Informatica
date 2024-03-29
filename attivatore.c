#include "lib_header.h"
#define STEP_ATTIVATORE 1
#define atomi_da_scindere [10] 
#define MAX_ATOMI 10 // per ora li faccio runnare in locale

void processo_attivatore() {
    while (1) {
        sleep(STEP_ATTIVATORE); // Attende STEP_ATTIVATORE unità di tempo
        
        // Seleziona atomi per la scissione (implementazione a discrezione)
        int[] atomi_da_scindere = seleziona_atomi(); 
        //TODO COMUNICAZIONE CON ATOMO: ATTIVA SCISSIONE
        // Comunica agli atomi selezionati di scindersi
        for (int i = 0; i < sizeof(atomi_da_scindere)/sizeof(atomi_da_scindere[0]); i++) {
            comunica_scissione(atomi_da_scindere[i]);
        }
    }
}
int main(int argc, char const *argv[])
{
    processo_attivatore();
    return 0;
}


/*                     Prova gestione memoria condivisa                         */

struct SharedMemory {
    struct Atomo atomi[MAX_ATOMI];
    int count; // Numero attuale di atomi
};

int crea_memoria_condivisa() {
    key_t key = ftok("Progetto.conf", 'R'); // Utilizza il file di configurazione come base per la chiave IPC
    int shmId = shmget(key, sizeof(struct SharedMemory), PERMISSIONS | IPC_CREAT);
    if (shmId < 0) {
        ERROR; // Utilizza la macro ERROR per gestire l'errore
    }
    return shmId;
}

struct SharedMemory *accesso_memoria_condivisa(int shmId) {
    struct SharedMemory *shmPtr = (struct SharedMemory *)shmat(shmId, NULL, 0);
    if (shmPtr == (void *)-1) {
        ERROR; // Utilizza la macro ERROR per gestire l'errore
    }
    return shmPtr;
}

void termina_memoria_condivisa(int shmId, struct SharedMemory *shmPtr) {
    // Stacca la memoria condivisa
    if (shmdt(shmPtr) == -1) {
        ERROR; // Utilizza la macro ERROR per gestire l'errore
    }
    
    // Rimuove il segmento di memoria condivisa
    if (shmctl(shmId, IPC_RMID, NULL) == -1) {
        ERROR; // Utilizza la macro ERROR per gestire l'errore
    }
}

