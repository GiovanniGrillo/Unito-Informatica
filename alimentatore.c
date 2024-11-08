#include "lib_header.c"
#include "lib_alimentatore.c"

int main(){
    setbuf(stdout, NULL);
    loadIPCs();

    if ((atoms        = shmat(shm_atoms,       NULL, 0)) == (void*) -1) ERROR;
    if ((power_plant  = shmat(shm_power_plant, NULL, 0)) == (void*) -1) ERROR;

    setup_signal_handler(NULL);

    struct timespec req = {0, vars->STEP_ALIMENTAZIONE};

    while (vars->exit_flag != 1){
        create_atoms(vars->N_NUOVI_ATOMI);
        nanosleep(&req, NULL);
    }
    exit_handler();
}