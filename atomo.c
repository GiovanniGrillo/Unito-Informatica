#include "lib_atomo.h"

int main() {
    srand(time(NULL));
    // printf("\n\033[1;34mBenvenuto in Atomo!\033[0m\n \n");
    loadIPCs();
    if(signal(SIGINT, handle_sigint) == SIG_ERR) ERROR;

    while(vars->exit_flag != 1) {
        while ((vars->atom_Fork > 0)) {
            if(signal(SIGINT, handle_sigint) == SIG_ERR) ERROR;

            if(vars->exit_flag != 0)
                endProcess();
            if (msgrcv(msg_stack, &message, sizeof(message) - sizeof(long), 1, 0) == -1) {
                continue;
            }

            ++numMessaggiRicevuti;
            attShm();

            if (power_plant->atom_count > 0) {
                int numero_casuale = rand() % (power_plant->atom_count - 1) + 1;
                Atom a_PADRE = atoms[(numero_casuale)];
    
                switch (a_PADRE.Atom_pid = newProcess()) {
                    case -1:
                        perror("MELTDOWN");
                        exit(1);
                        break;
                    case 0:
                        do_fission(a_PADRE);
                        endProcess();
                        break;
                    default:
                        break;
                }
            } else {
                printf("Atomo finiti nella power_plant");
            }
        }
    }
    unloadIPCs();
    return 0;
}