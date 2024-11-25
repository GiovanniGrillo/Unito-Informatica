#include "lib/lib_header.c"
#include "lib/lib_alimentatore.c"

int main(){
    setbuf(stdout, NULL);
    loadIPCs();

    setup_signal_handler(NULL, SIGQUIT);
    setup_signal_handler(exit_handler, SIGTERM);
    setup_signal_handler(exit_handler, SIGINT);

    if ((atoms        = shmat(shm_atoms,       NULL, 0)) == (void*) -1) ERROR;
    if ((power_plant  = shmat(shm_power_plant, NULL, 0)) == (void*) -1) ERROR;

    releaseSem(sem_processes,0);

    struct timespec req = {0, vars->STEP_ALIMENTAZIONE};

    while (true){
        create_atoms(vars->N_NUOVI_ATOMI);
        nanosleep(&req, NULL);
    }

    exit_handler();
}