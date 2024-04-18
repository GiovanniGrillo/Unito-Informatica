//Ogni STEP ALIMENTAZIONE nanosecondi, il processo alimentazione immette nuovo combustibile, ovvero crea N NUOVI ATOMI atomi.
#include "lib_header.h"
#include "lib_alimentatore.h"

#define N_NUOVI_ATOMI 10

int main() {
    printf("\nBenvenuto in alimentatore!\n");
    setbuf(stdout, NULL);
    loadIPCs();
    for(int i=0;i<2;i++) {
        if(var->flagTerminazione==1){
            unloadIPCs();
            endProcess();
        }
        
        attShm(); {
            if (creazione_atomi(N_NUOVI_ATOMI)) ERROR; 
            printf("\nHEY SONO ALIMENTATORE HO CREATO %d nuovi atomi fino ad adesso sono : %d ---------------------------------\n",N_NUOVI_ATOMI, centrale->n_atomi);

        } dettShm();
        sleep(1);
    }
    

    unloadIPCs();
    exit(0);

}