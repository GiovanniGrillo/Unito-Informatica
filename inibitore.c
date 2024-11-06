#include "lib_header.c"

int main() {
    loadIPCs();
    setup_signal_handler(handle_sig_inhibitor);

    struct timespec att = {0, vars->STEP_INHIBITOR};

    while (vars->exit_flag != 1)
        nanosleep(&att, NULL);

    unloadIPCs();
    return 0;
}