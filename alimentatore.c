#include "lib_header.c"
#include "lib_alimentatore.c"

int main(){
    setbuf(stdout, NULL);
    loadIPCs();

    if ((atoms        = shmat(shm_atoms,       NULL, 0)) == (void*) -1) ERROR;
    if ((power_plant  = shmat(shm_power_plant, NULL, 0)) == (void*) -1) ERROR;

    setup_signal_handler(NULL);

    reserveSem(sem_var, 0);
    struct timespec req = {0, vars->STEP_ALIMENTAZIONE};

    while (vars->exit_flag != 1){
        if (create_atoms(vars->N_NUOVI_ATOMI) == -1) ERROR;
        nanosleep(&req, NULL);
    }
    releaseSem(sem_var, 0);
    exit_handler();
}