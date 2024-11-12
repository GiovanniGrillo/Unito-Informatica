#include "lib_header.c"
#include "lib_attivatore.c"

int main() {
    loadIPCs();
    setup_signal_handler(NULL);
    setup_exit_handler(exit_handler);

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
            ++vars->atom_Fork;
            ++i;
        }
        nanosleep(&req, NULL);
    }
    exit_handler();
}