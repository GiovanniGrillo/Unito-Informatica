#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "libreia2.h"

struct Configurazione *attshm(key_t chiave) {
    int id_memoria_condivisa = shmget(chiave, sizeof(struct Configurazione), IPC_CREAT | 0666);
    if (id_memoria_condivisa == -1) {
        perror("Errore nella creazione della memoria condivisa");
        exit(EXIT_FAILURE);
    }

    struct Configurazione *configurazione = (struct Configurazione *)shmat(id_memoria_condivisa, NULL, 0);
    if (configurazione == (void *)-1) {
        perror("Errore nell'associazione del segmento di memoria condivisa");
        exit(EXIT_FAILURE);
    }

    return configurazione;
}

void detshm(struct Configurazione *configurazione) {
    int id_memoria_condivisa = shmget(IPC_PRIVATE, sizeof(struct Configurazione), IPC_CREAT | 0666);
    shmdt(configurazione);
    shmctl(id_memoria_condivisa, IPC_RMID, NULL);
}




int main() {
    key_t chiave_memoria_condivisa = ftok(".", 'R');
    if (chiave_memoria_condivisa == -1) {
        perror("Errore nella generazione della chiave per la memoria condivisa");
        exit(EXIT_FAILURE);
    }

    int id_memoria_condivisa = shmget(chiave_memoria_condivisa, sizeof(struct Configurazione), IPC_CREAT | 0666);
    if (id_memoria_condivisa == -1) {
        perror("Errore nella creazione della memoria condivisa");
        exit(EXIT_FAILURE);
    }

    struct Configurazione *configurazione = (struct Configurazione *)shmat(id_memoria_condivisa, NULL, 0);
    if (configurazione == (void *)-1) {
        perror("Errore nell'associazione del segmento di memoria condivisa");
        exit(EXIT_FAILURE);
    }

    // Legge i valori dal file di configurazione e li scrive nella memoria condivisa
    creaIPCS(configurazione);

    // Utilizza le variabili della configurazione nel tuo programma
    printf("ENERGY_DEMAND: %d\n", configurazione->ENERGY_DEMAND);
    printf("N_ATOMI_INIT: %d\n", configurazione->N_ATOMI_INIT);
    printf("N_ATOM_MAX: %d\n", configurazione->N_ATOM_MAX);
    printf("MIN_N_ATOMICO: %d\n", configurazione->MIN_N_ATOMICO);
    printf("STEP_ATTIVATORE: %d\n", configurazione->STEP_ATTIVATORE);
    printf("STEP_ALIMENTAZIONE: %d\n", configurazione->STEP_ALIMENTAZIONE);
    printf("SIM_DURATION: %d\n", configurazione->SIM_DURATION);
    printf("ENERGY_EXPLODE_THRESHOLD: %d\n", configurazione->ENERGY_EXPLODE_THRESHOLD);

    // Rimuove la memoria condivisa alla fine del programma
    shmdt(configurazione);
    shmctl(id_memoria_condivisa, IPC_RMID, NULL);

    struct Atomo atomo_padre = crea_atomo();
    struct Atomo atomo_figlio = crea_atomo();

    printf("Atomo padre: Numero atomico = %d, Energia = %d\n", atomo_padre.numero_atomico, atomo_padre.energia);
    printf("Atomo figlio: Numero atomico = %d, Energia = %d\n", atomo_figlio.numero_atomico, atomo_figlio.energia);

    esegui_scissione(&atomo_padre, &atomo_figlio);

    printf("Atomo padre dopo la scissione: Numero atomico = %d, Energia = %d\n", atomo_padre.numero_atomico, atomo_padre.energia);
    printf("Atomo figlio dopo la scissione: Numero atomico = %d, Energia = %d\n", atomo_figlio.numero_atomico, atomo_figlio.energia);

    return 0;
}
