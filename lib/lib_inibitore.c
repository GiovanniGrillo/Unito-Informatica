#include "lib_header.h"

int limit_fission(){
    return (rand() % 10);
}

int absorb_energy(int energy) {
    double reduction_factor = (rand() % 51) / 100.0;
    int absorbed = energy * reduction_factor;
    reserveSem(sem_inhibitor, 0);
    inhibitor->absorbed_energy += absorbed;
    releaseSem(sem_inhibitor, 0);
    return energy - absorbed;
}

void active_inhibitor_handler(){
    reserveSem(sem_inhibitor, 0);
    if (inhibitor->inhibitor_setup == false)
        inhibitor->inhibitor_setup = true;
    else
        inhibitor->inhibitor_setup = false;
    releaseSem(sem_inhibitor, 0);
}

void exit_handler(){
    if ((shmdt(inhibitor)) == -1) ERROR;
    unloadIPCs();
    exit(0);
}