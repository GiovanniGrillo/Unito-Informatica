#include "lib_atomo.h"

int main() {
    srand(time(NULL));
    printf("\n\033[1;34mBenvenuto in Atomo!\033[0m\n \n");
    loadIPCs();

    if(var->flagTerminazione != 0) endProcess();
    while ((var->fork_atomi > 0)) {

        if(var->flagTerminazione != 0) endProcess();
        if (msgrcv(msgPila, &message, sizeof(message) - sizeof(long), 1, 0) == -1) {
            continue;
        }

        ++numMessaggiRicevuti;
        attShm();
        if(inibitore->active==1){
            int casuale = rand()%2;
            if(casuale==1){ 
                inibitore->scissioni_negate++;
                endProcess();
            }

        }
        if (centrale->n_atomi > 0)
        {
            Atomo a_PADRE = atomi[(centrale->n_atomi)];

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
        else{ printf("Atomo finiti nella centrale");    }
    }
    unloadIPCs();
    return 0;
}