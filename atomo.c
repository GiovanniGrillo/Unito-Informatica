#include "lib_atomo.h"

int main() {
    srand(time(NULL));
    printf("\n\033[1;34mBenvenuto in Atomo!\033[0m\n \n");
    loadIPCs();

    if(var->flagTerminazione != 0) endProcess();
    while ((var->fork_atomi > 0)) {

        if(var->flagTerminazione != 0) endProcess();
        if (msgrcv(msgPila, &message, sizeof(message) - sizeof(long), 1, 0) == -1) {
            ERROR;
            continue;
        }

        ++numMessaggiRicevuti;
        attShm();

        Atomo a_PADRE = atomi[rand() % (centrale->n_atomi)];

        switch (a_PADRE.pidAtomo = newProcess()) {
            case -1:
                perror("Errore nella creazione del processo figlio");
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
    unloadIPCs();
    return 0;
}