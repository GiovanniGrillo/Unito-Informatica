#include "lib_header.h"

#define N_NUOVI_ATOMI 10

int main() {
    printf("\n\033[1;32mBenvenuto in alimentatore!\033[0m\n");
    setbuf(stdout, NULL);
    loadIPCs();
    struct timespec req = {0,var->STEP_ALIMENTAZIONE};

    while(var->flagTerminazione != 1) {
        reserveSem(semProcessi, 0);
        attShm();
        {
            if (creazione_atomi(N_NUOVI_ATOMI)) ERROR;
            printf("\n\033[1;32mHEY SONO ALIMENTATORE HO CREATO %d nuovi atomi fino ad adesso sono : %d ---------------------------------\033[0m\n",N_NUOVI_ATOMI, centrale->n_atomi);
        }
        dettShm();
        releaseSem(semProcessi, 0);
        nanosleep(&req, NULL);
    }
    unloadIPCs();
    exit(0);
}
