#include "lib_header.h"

int main() {
    printf("\033[33mBenvenuto in Inibitore!%d\033[0m\n", getpid());
    struct timespec att = {0, 500000000L};

    loadIPCs();

    if(signal(SIGINT, handle_sig_inibitore) == SIG_ERR) ERROR;

    while (var->exitFlag != 1) {
        reserveSem(semInibitore, 0);
        releaseSem(semInibitore, 0);
        nanosleep(&att, NULL);
    }
    unloadIPCs();
    return 0;
}