#include "lib_header.h"

int main() {
    //cccc
    loadIPCs();
    setup_signal_handler(NULL);

    struct timespec req = {0, vars->STEP_ATTIVATORE};
    message.msg_type = 1;

    while (vars->exit_flag != 1) {
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
            ++i;
            dettShm();
        }
        nanosleep(&req, NULL);
    }
    unloadIPCs();
    return 0;
}