//Ogni STEP ALIMENTAZIONE nanosecondi, il processo alimentazione immette nuovo combustibile, ovvero crea N NUOVI ATOMI atomi.
#include "lib_header.h"
#include "lib_alimentatore.h"

#define N_NUOVI_ATOMI 10

int main() {
    setbuf(stdout, NULL);
    // loadIPCs();
    createIPCS();
    if (set_sem(semShm, 0, 1) == -1) ERROR;
    for(int giorno = 0; giorno < SIM_DURATION; ++giorno) {
        provasleep();
        printf("\n-------------------------------");
        printf("\n   RESOCONTO GIORNALIERO %3d ", giorno);
        printf("\n-------------------------------\n");
        printf("          -> GIORNO %d\n", giorno + 1);
        attShm(); {

            if (creazione_atomi(N_NUOVI_ATOMI)) ERROR; 
            printf("\ngli atomi creati fino ad adesso sono :%d\n", centrale->n_atomi);

        } dettShm();
        printf(" -> (DET)\n");
    }

   
    printf("--------------------------------------\n");
    printf("   PROCESSO Giornaliera - Terminato   \n");
    printf("--------------------------------------\n");
    exit(0);
    
}