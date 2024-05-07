#include "lib_atomo.h"

int main() {
    srand(time(NULL));
    printf("\n\033[1;34mBenvenuto in Atomo!\033[0m\n \n");
    loadIPCs();
    printf("\n\033[1;34mBenvenuto2 in Atomo!\033[0m\n \n");

    if(var->flagTerminazione != 0) endProcess();
    while ((var->fork_atomi > 0)) {

        if(var->flagTerminazione != 0) endProcess();
        if (msgrcv(msgPila, &message, sizeof(message) - sizeof(long), 1, 0) == -1) {
            continue;
        }

        ++numMessaggiRicevuti;
        attShm();
        
     
        if (centrale->n_atomi > 0)
        {
            Atomo a_PADRE = atomi[(centrale->n_atomi)];

        switch (a_PADRE.pidAtomo = newProcess()) {
            case -1:
                perror("MELTDOWN");
                exit(1);
                break;
            case 0:
                // if(inibitore->active==1){
                    
                //       // Genera un numero casuale
                //     if (a_PADRE.numero_atomico % 2 == 0) {
                //         fprintf(out_progetto,"\nHO ASSORBITO UNA SCISSIONE");
                //         ++inibitore->scissioni_negate;
                //         dettShm();  // Controlla se il numero casuale è pari
                //         endProcess();
                //     }
                // }
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