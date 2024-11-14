#include "lib/lib_header.c"
#include "lib/lib_inibitore.c"

int main() {
    loadIPCs();
    setup_signal_handler(active_inhibitor_handler, SIGINT); //SIGINT
    setup_signal_handler(exit_handler, SIGTERM); //SIGTERM
    setup_signal_handler(limit_fission_handler, SIGUSR1); //SIGUSR1

    if ((inhibitor = shmat(shm_inhibitor,   NULL, 0)) == (void*) -1) ERROR;

    releaseSem(sem_processes,0);

    struct timespec att = {0, vars->STEP_INHIBITOR};

    while (true){
        if (msgrcv(inhibitor_stack, &message, sizeof(message) - sizeof(long), 1, 0) == -1)
                continue;
            message.msg_absorb = absorb_energy(message.msg_absorb);
            if(msgsnd(inhibitor_stack, &message, sizeof(message) - sizeof(long), 0) == -1) ERROR;

        nanosleep(&att, NULL);
    }
    exit_handler();
}