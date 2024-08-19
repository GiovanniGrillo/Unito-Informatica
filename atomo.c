#include "lib_atomo.h"

int main() {
    srand(time(NULL));
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

            ++received_messages;
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
                //ogni received_messages multiplo di N_MSG/2 
                if(received_messages %((vars->N_MSG)/2) == 0){
                    printf("\nReceived messages: %d\n", received_messages);
                    sim_overview();
                }
            }
            else {
                printf("atoms are transferred to the power plant");
            }
        }
    }
    unloadIPCs();
    return 0;
}