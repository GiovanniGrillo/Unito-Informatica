//Ogni STEP ALIMENTAZIONE nanosecondi, il processo alimentazione immette nuovo combustibile, ovvero crea N NUOVI ATOMI atomi.
#include "lib_header.h"
#include "lib_alimentatore.h"

#define N_NUOVI_ATOMI 10
//alimentatore
int main() {
    printf("\n\033[1;32mBenvenuto in alimentatore!\033[0m\n");
    setbuf(stdout, NULL);
    loadIPCs();
    while(var->flagTerminazione!=1) {


        reserveSem(semProcessi,0);
        attShm(); {
            if (creazione_atomi(N_NUOVI_ATOMI)) ERROR;
            printf("\n\033[1;32mHEY SONO ALIMENTATORE HO CREATO %d nuovi atomi fino ad adesso sono : %d ---------------------------------\033[0m\n",N_NUOVI_ATOMI, centrale->n_atomi);

        } dettShm();
        releaseSem(semProcessi,0);

    struct timespec req = {.tv_sec = 0, .tv_nsec = var->STEP_ALIMENTAZIONE};
    nanosleep(&req, NULL);

    }
    unloadIPCs();
    exit(0);

}