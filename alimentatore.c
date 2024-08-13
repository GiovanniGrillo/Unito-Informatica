#include "lib_header.h"

int main(){
    printf("\n\033[1;32mBenvenuto in alimentatore!\033[0m\n");
    setbuf(stdout, NULL);
    loadIPCs();
    if (signal(SIGINT, handle_sigint) == SIG_ERR)
        ERROR;
    struct timespec req = {0, vars->STEP_ALIMENTAZIONE};

    while (vars->exit_flag != 1)
    {
        reserveSem(sem_processes, 0);
        attShm();
        
            if (create_atoms(vars->N_NUOVI_ATOMI) == -1)
                ERROR;
            printf("\n\033[1;32mHEY SONO ALIMENTATORE HO CREATO %d nuovi atoms fino ad adesso sono : %d---------\033[0m\n", vars->N_NUOVI_ATOMI, power_plant->atom_count);
        
        dettShm();
        releaseSem(sem_processes, 0);
        nanosleep(&req, NULL);
    }
    unloadIPCs();
    exit(0);
}