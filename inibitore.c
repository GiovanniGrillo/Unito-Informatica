#include "lib/lib_header.c"
#include "lib/lib_inibitore.c"

int main() {
    loadIPCs();
    setup_signal_handler(active_inhibitor_handler, SIGQUIT);
    setup_signal_handler(exit_handler, SIGTERM);
    setup_signal_handler(exit_handler, SIGINT);


    if ((inhibitor = shmat(shm_inhibitor,   NULL, 0)) == (void*) -1) ERROR;

    releaseSem(sem_processes,0);

    while (true){
        if(inhibitor->inhibitor_setup){
            if(msgrcv(inhibitor_stack, &message, sizeof(message) - sizeof(long), 1, 0) == -1) continue;
            if(message.msg_op == 0)
                message.msg_op = limit_fission();
            else if (message.msg_op == 1)
                message.msg_absorb = absorb_energy(message.msg_absorb);
            else
                continue;

            message.msg_type = 2;
            if(msgsnd(inhibitor_stack, &message, sizeof(message) - sizeof(long), 0) == -1) continue;
        }
    }
    exit_handler();
}