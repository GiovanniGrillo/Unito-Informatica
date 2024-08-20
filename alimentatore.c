#include "lib_header.h"

int main(){
    setbuf(stdout, NULL);
    loadIPCs();
    if (signal(SIGINT, handle_sigint) == SIG_ERR) ERROR;

    struct timespec req = {0, vars->STEP_ALIMENTAZIONE};

    while (vars->exit_flag != 1){

        reserveSem(sem_processes, 0);
        attShm();

            if (create_atoms(vars->N_NUOVI_ATOMI) == -1) ERROR;

        printf("\nPower supply created %d new atoms. Actual atoms count: %d \n", vars->N_NUOVI_ATOMI, power_plant->atom_count);

        dettShm();
        releaseSem(sem_processes, 0);
        nanosleep(&req, NULL);
    }
    unloadIPCs();
    exit(0);
}