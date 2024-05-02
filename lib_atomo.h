#include "lib_header.h"

/* --- Variabili locali --- */
int numMessaggiRicevuti = 0;
int exec = 0;
/* ------------------------ */

int energy(int n1, int n2) {
    return n1 * n2 - (n1 > n2 ? n1 : n2);
}
endall(){
    deallocIPC();
}


void esegui_scissione(Atomo a_PADRE) {
    printf("\n\033[1;34mMessaggio ricevuto, msg n°%d  eseguo scissione\033[0m", numMessaggiRicevuti);

    if(a_PADRE.numero_atomico < var->MIN_N_ATOMICO) {
        var->fork_atomi;
        --centrale->n_atomi;
        //printf("\n\033[1;34m il valore di fork atomi è %d, e abbiamo %d atomi nella centrale \033[0m ", var->fork_atomi, centrale->n_atomi);
        centrale->scorie++;
        dettShm();
        releaseSem(semFissione, 0);
        endProcess();
    } else {

        int numero_casuale = rand() % (a_PADRE.numero_atomico - 1) + 1;

        struct Atomo figlio;
        figlio.numero_atomico = a_PADRE.numero_atomico - numero_casuale;
        a_PADRE.numero_atomico -= figlio.numero_atomico;

        //printf("\n \033[1;34m atomo figlio creato con numero atomico: %d, il padre ha numero atomico post scissione :%d\n\033[0m", figlio.numero_atomico, a_PADRE.numero_atomico);
        int liberata = energy(a_PADRE.numero_atomico, figlio.numero_atomico);
        if((centrale->energia += liberata) > var->ENERGY_EXPLODE_THRESHOLD) {
            printf("\ncentrale esplosa, troppa energia liberata\n");
            printf("il vero valore di ENERGYEXPLODETRESHOLD è: %d", var->ENERGY_EXPLODE_THRESHOLD);
            var->flagTerminazione = 1;
            dettShm();
              var->flagTerminazione=1;

            kill(pidAttivatore,     SIGTERM);
            kill(pidAtomo,          SIGTERM);
            kill(pidAlimentatore,   SIGTERM);
            endProcess();
        }
        printf("\033[0;35m");         printf("energia presente nella centrale è: %d\n",centrale->energia);         printf("\033[0m");
        printf("\n\033[1;34menergia liberata: %d \033[0m ", liberata);
        centrale->energia += liberata;
        var->fork_atomi--;
        atomi[centrale->n_atomi] = figlio;
        
        printf("\n\033[1;34m il valore di fork atomi è %d e abbiamo %d atomi nella centrale \033[0m ", var->fork_atomi, centrale->n_atomi);
        dettShm();
        releaseSem(semFissione, 0);
        endProcess();
    }
}