//Ogni STEP ALIMENTAZIONE nanosecondi, il processo alimentazione immette nuovo combustibile, ovvero crea N NUOVI ATOMI atomi.
#include "lib_header.h"

#define N_NUOVI_ATOMI 10

int main(int argc, char* argv[]) {
    setbuf(stdout, NULL);
    int ret;
    loadIPCs();
    
    for(int giorno = 0; giorno < SIM_DURATION; ++giorno) {
        sleep(1);
        printf("-------------------------------\n");
        printf("  RESOCONTO GIORNALIERO %3d   \n", giorno);
        printf("-------------------------------\n");
        printf("           -> GIORNO %d\n", giorno + 1);
        attShm(); {                                     
          
            if (creazione_atomi(N_NUOVI_ATOMI)) ERROR; 

        } detShm();                                     
        printf(" -> (DET)\n");
    }

    unloadIPCs();
    
    printf("--------------------------------------\n");
    printf("   PROCESSO Giornaliera - Terminato   \n");
    printf("--------------------------------------\n");
    exit(0);
    
}