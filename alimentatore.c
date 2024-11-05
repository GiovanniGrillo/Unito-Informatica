#include "lib_header.h"

int main(){
    setbuf(stdout, NULL);
    loadIPCs();
    setup_signal_handler(NULL);

    struct timespec req = {0, vars->STEP_ALIMENTAZIONE};

    while (vars->exit_flag != 1){
        attShm();

        if (create_atoms(vars->N_NUOVI_ATOMI) == -1) ERROR;

        dettShm();
        nanosleep(&req, NULL);
    }
    unloadIPCs();
    exit(0);
}