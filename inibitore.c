#include "lib_header.h"

int main() {
    loadIPCs();
    setup_signal_handler(handle_sig_inhibitor);

    attShm();
    struct timespec att = {0, vars->STEP_INHIBITOR};
    dettShm();

    while (vars->exit_flag != 1) {
        reserveSem(sem_inhibitor, 0);
        releaseSem(sem_inhibitor, 0);
        nanosleep(&att, NULL);
    }
    unloadIPCs();
    return 0;
}