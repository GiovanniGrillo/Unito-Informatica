#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "lib_header.h"

// Funzione per gestire il segnale SIGUSR1
void handle_signal_inibitore(int signum) {
    attShm();
    if (inibitore->active==1)
    {
        fprintf(out_progetto, "\nINIBITORE è ATTIVO LO SPENGO \n");
        inibitore->active=0;
    }else{
        fprintf(out_progetto, "\nINIBITORE è SPENTO LO ATTIVO \n");
        inibitore->active=1;
    }
    dettShm();

    
    
    }


int main() {
    // createIPCS("Progetto.conf");
    // if(set_sem(semShm,           0, 1) == -1) ERROR;
    // if(set_sem(semAttivatore,    0, 1) == -1) ERROR;
    // if(set_sem(semFissione,      0, 1) == -1) ERROR;
    // if(set_sem(semProcessi,      0, 1) == -1) ERROR;

    //  attShm();
    //     creazione_atomi(var->N_ATOMI_INIT);
    //     dettShm();
    printf("\033[1;37mTesto bianco\033[0m");
    loadIPCs();
    printf("\033[1;37mTesto bianco2\033[0m");
      if (signal(SIGUSR1, handle_signal_inibitore) == SIG_ERR) {
        perror("Impossibile impostare il gestore per SIGUSR1");
        return 1;
    }
     while (var->flagTerminazione!=1 ) {
        printf("hey sto aspettando ");
       sleep(1);
    
    }
   

    
   

    return 0;
}
