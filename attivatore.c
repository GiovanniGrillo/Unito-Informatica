#include "lib_header.h"

int main() {
    printf("\n\n\033[1;31mBenvenuto in attivatore!\033[0m\n");
    loadIPCs();

    if(signal(SIGINT, handle_sigint) == SIG_ERR) ERROR;
    struct timespec req = {0, var->STEP_ATTIVATORE};
    message.msg_type = 1;

    while (flagTerminazione != 1) {
        reserveSem(semAttivatore, 0);
        int i = 0;
        while (i < var->N_MSG) {
            if (var->flagTerminazione == 1) {
                exit(0);
            }
            if (msgsnd(msgPila, &message, sizeof(message) - sizeof(long), 0) == -1) {
                ERROR;
                exit(1);
            }
            attShm();
            ++var->fork_atomi;
            printf("\033[1;31mMessaggio inviato all'atomo. Messaggio n°%d\033[0m\n", i+1);
            fflush(stdout);
            ++i;
            dettShm();
        }
        releaseSem(semAttivatore, 0);
        nanosleep(&req, NULL);
    }
    unloadIPCs();
    return 0;
}