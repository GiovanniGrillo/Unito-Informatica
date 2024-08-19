#include "lib_header.h"

int main() {
    loadIPCs();

    if(signal(SIGINT, handle_sigint) == SIG_ERR) ERROR;
    struct timespec req = {0, vars->STEP_ATTIVATORE};
    message.msg_type = 1;

    while (vars->exit_flag != 1) {
        reserveSem(sem_activator, 0);
        int i = 0;
        while (i < vars->N_MSG) {
            if (vars->exit_flag == 1) {
                exit(0);
            }
            if (msgsnd(msg_stack, &message, sizeof(message) - sizeof(long), 0) == -1) {
                ERROR;
                exit(1);
            }
            attShm();
            ++vars->atom_Fork;
            //printf("[1;31mMessaggio inviato all'atomo. Messaggio n°%d \n", i+1);
            ++i;
            dettShm();
        }
        releaseSem(sem_activator, 0);
        nanosleep(&req, NULL);
    }
    unloadIPCs();
    return 0;
}