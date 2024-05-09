#include "lib_atomo.h"

int main() {
    srand(time(NULL));
     printf("\n\033[1;34mBenvenuto in Atomo!\033[0m\n \n");
    loadIPCs();
    signal(SIGINT, handle_sigint);

    while(var->flagTerminazione != 1){
        while ((var->fork_atomi > 0)) {
            signal(SIGINT, handle_sigint);
            
            if(var->flagTerminazione != 0) endProcess();
            if (msgrcv(msgPila, &message, sizeof(message) - sizeof(long), 1, 0) == -1) {
                continue;
            }

            ++numMessaggiRicevuti;
            attShm();

            if (centrale->n_atomi > 0)
            {
                int numero_casuale = rand() % (centrale->n_atomi - 1) + 1;
          
                Atomo a_PADRE = atomi[(numero_casuale)];

            switch (a_PADRE.pidAtomo = newProcess()) {
                case -1:
                    perror("MELTDOWN");
                    exit(1);
                    break;
                case 0:
                    esegui_scissione(a_PADRE);
                    endProcess();
                    break;
                default:
                    wait(NULL);
                    break;
                }
            }
            else{printf("Atomo finiti nella centrale");}
        }
    }
    unloadIPCs();
    return 0;
}