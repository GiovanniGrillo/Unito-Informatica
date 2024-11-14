#include "lib_header.h"
void limit_fission_handler(){
    int random_number = rand() % 10;

    message.msg_type = 1;
    message.msg_op = random_number;

    if (msgsnd(inhibitor_stack, &message, sizeof(message) - sizeof(long), 0) == -1) {
        perror("Errore nell'invio del messaggio");
        ERROR;
    }
}

int absorb_energy(int energy) {
    double reduction_factor = (rand() % 51) / 100.0;
    int absorbed = energy * reduction_factor;
    inhibitor->absorbed_energy += absorbed;
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

/*void setup_limit_handler(){
    srand(time(NULL));
    
    struct sigaction sa;

    memset(&sa, 0, sizeof(sa));

    sigemptyset(&sa.sa_mask);
    sa.sa_handler = limit_fission_handler;
    sa.sa_flags = 0;

    if (sigaction(SIGUSR1, &sa, NULL) == -1) ERROR;
} */

void exit_handler(){
    if ((shmdt(inhibitor)) == -1) ERROR;
    unloadIPCs();
    exit(0);
}