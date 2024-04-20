#include "lib_atomo.h"

int main() {
    srand(time(NULL));
    printf("\n\033[1;34mBenvenuto in Atomo!\033[0m\n \n");

    /* --- Variabili locali --- */
    int exec = 0;

    /* --- Apertura IPC --- */
    loadIPCs();

    if(var -> flagTerminazione != 0) endProcess();
    while ((var->fork_atomi > 0) ) {
        if(var -> flagTerminazione != 0) endProcess();
        if (msgrcv(msgPila, &message, sizeof(message) - sizeof(long), 1, 0) == -1) {
            ERROR;
            continue; // Continua il ciclo in caso di errore
        }


        attShm();

        printf("\n\033[1;34mMessaggio ricevuto\033[0m");

        Atomo a_rand = atomi[rand() % (centrale->n_atomi)];
        //dettShm();

        switch (a_rand.pidAtomo = newProcess()) {
            case -1:
                perror("Errore nella creazione del processo figlio");
                break;
            case 0:
                // Codice eseguito nel processo figlio

                esegui_scissione(a_rand);

                endProcess();

                break;
            default:
                wait(NULL); // Il processo padre aspetta la fine del figlio
                break;
        }
        exec++;

    }
    unloadIPCs();
    return 0;
}

void esegui_scissione(Atomo a_rand) {
    printf("\nSTO ESEGUENDO SCISSIONE\n");

                printf("\n\033[1;34mNUMERO ATOMICO PADRE %d\033[0m", a_rand.numero_atomico);
                // attShm();
                int numero_casuale = rand() % a_rand.numero_atomico + 1;
                printf("\n%d numero casuale", numero_casuale);
                struct Atomo figlio;
                figlio.numero_atomico = a_rand.numero_atomico - numero_casuale;
                a_rand.numero_atomico -= figlio.numero_atomico;
                printf("\n \033[1;34m atomo figlio creato con numero atomico: %d, il padre ha numero atomico post scissione :%d\n\033[0m", figlio.numero_atomico,a_rand.numero_atomico);
           
                
                if (a_rand.numero_atomico > var->MIN_N_ATOMICO && figlio.numero_atomico > var->MIN_N_ATOMICO) {
                    int liberata = energy(a_rand.numero_atomico, figlio.numero_atomico);
                    if(liberata>var->ENERGY_EXPLODE_THRESHOLD){
                        printf("\ncentrale esplosa, troppa energia liberata\n");
                        var->flagTerminazione=1;
                        dettShm();
                        endProcess();
                    }
                    printf("\n\033[1;34menergia liberata: %d \033[0m ", liberata);
                    centrale->energia += liberata;
                } else {
                            printf("\n\033[1;34maumento scorie \033[0m \n");
                            var->fork_atomi--;
                            --centrale->n_atomi;
                            printf("\n\033[1;34m-----------------------------------------il valore di fork atomi è %d,e abbiamo %d atomi nella centrale \033[0m ",var->fork_atomi,centrale->n_atomi);
                            centrale->scorie += 2;
                            
                            dettShm();
                            releaseSem(semFissione,0);
                            endProcess();
                        }
                var->fork_atomi--;


                atomi[centrale->n_atomi] = figlio;
                centrale->n_atomi++;
                printf("\n\033[1;34m-----------------------------------------il valore di fork atomi è %d e abbiamo %d atomi nella centrale \033[0m ",var->fork_atomi,centrale->n_atomi);
                dettShm();
                releaseSem(semFissione,0);
                endProcess();
}
