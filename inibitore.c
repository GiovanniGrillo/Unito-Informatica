#include "lib/lib_header.c"
#include "lib/lib_inibitore.c"

int main() {
    loadIPCs();
    setup_signal_handler(handle_sig_inhibitor); //SIGINT
    setup_exit_handler(exit_handler); //SIGTERM
    setup_limit_handler(); //SIGUSR1

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