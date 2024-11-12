#include "lib_header.c"
#include "lib_alimentatore.c"

int main(){
    setbuf(stdout, NULL);
    loadIPCs();
    setup_signal_handler(NULL);
    setup_exit_handler(exit_handler);

    if ((atoms        = shmat(shm_atoms,       NULL, 0)) == (void*) -1) ERROR;
    if ((power_plant  = shmat(shm_power_plant, NULL, 0)) == (void*) -1) ERROR;

    struct timespec req = {0, vars->STEP_ALIMENTAZIONE};


    while (vars->exit_flag != 1){
        create_atoms(vars->N_ATOMI_INIT);
        nanosleep(&req, NULL);
    }
    exit_handler();
}