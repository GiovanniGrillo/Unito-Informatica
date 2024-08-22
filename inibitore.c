#include "lib_header.h"

int main() {
    loadIPCs();
    attShm();
    struct timespec att = {0, vars->STEP_INHIBITOR};
    dettShm();

    setup_signal_inhibitor();

    while (vars->exit_flag != 1) {
        reserveSem(sem_inhibitor, 0);
        releaseSem(sem_inhibitor, 0);
        nanosleep(&att, NULL);
    }
    unloadIPCs();
    return 0;
}