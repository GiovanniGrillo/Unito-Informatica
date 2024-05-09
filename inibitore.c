#include "lib_header.h"

void handle_sigusr2_inibitore(int sig) {
attShm();
    if (inibitore->active == 0) {
        inibitore->active = 1;
    } else {
        inibitore->active = 0;
    }
    printf("adesso vale %d", inibitore->active);
    fflush(stdout);
    dettShm();

}

int main() {
    printf("\033[33mBenvenuto in Inibitoreeeeeeeeeee!%d\033[0m\n",getpid());

    loadIPCs();
   
    signal(SIGINT, handle_sigusr2_inibitore);
    // signal(SIGUSR2, handle_sigusr2_inibitore);

    struct timespec attesa;attesa.tv_sec = 0;attesa.tv_nsec = 500000000L;

    // if (signal(SIGUSR1, handle_sigusr1_inibitore) == -1) ERROR;
        while (var->flagTerminazione != 1) {
            reserveSem(semInibitore,0);
           
     
            releaseSem(semInibitore,0);
            
            nanosleep(&attesa, NULL);
        }
}