#include "lib/lib_header.c"
#include "lib/lib_attivatore.c"

int main() {
    loadIPCs();
    setup_signal_handler(NULL, SIGQUIT);
    setup_signal_handler(exit_handler, SIGTERM);
    setup_signal_handler(exit_handler, SIGINT);


    releaseSem(sem_processes,0);

    struct timespec req = {0, vars->STEP_ATTIVATORE};
    message.msg_type = 1;

    while (true) {
        int i = 0;
        while (i < vars->N_MSG) {
            if (msgsnd(msg_stack, &message, sizeof(message) - sizeof(long), 0) == -1) {
                ERROR;
                exit(1);
            }
            ++i;
        }
        nanosleep(&req, NULL);
    }
    exit_handler();
}