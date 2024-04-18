#include "lib_atomo.h"

int main() {
    srand(time(NULL));
    printf("\nBenvenuto in Atomo! \n");

    /* --- Variabili locali --- */
    int exec = 0;
    printf("sto per loaddare \n");
    /* --- Apertura IPC --- */
    loadIPCs();
    set_sem(semProcessi, 0, 0);
    if(var -> flagTerminazione != 0) endProcess();
    while ((var->fork_atomi > 0) ) {
        if(var -> flagTerminazione != 0) endProcess();
        if (msgrcv(msgPila, &message, sizeof(message) - sizeof(long), 1, 0) == -1) {
            ERROR;
            continue; // Continua il ciclo in caso di errore
        }
        printf("\nMessaggio ricevuto: avvia scissione\n");

        attShm();
        Atomo a_rand = atomi[rand() % (centrale->n_atomi)];
        printf("Numero atomico prima della scissione: %d\n", a_rand.numero_atomico);
        dettShm();
        
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
    printf("\nSTO ENTRANDO NEL FIGLIO\n");
                printf("\nNUMERO ATOMICO PADRE %d", a_rand.numero_atomico);
                attShm();
                int numero_casuale = rand() % a_rand.numero_atomico + 1;
                printf("\n%d numero casuale", numero_casuale);
                struct Atomo figlio;
                figlio.numero_atomico = a_rand.numero_atomico - numero_casuale;
                a_rand.numero_atomico -= figlio.numero_atomico;
                printf("\nProcesso figlio creato con numero atomico: %d\n", figlio.numero_atomico);
                printf("\nNUMERO ATOMICO PADRE dopo la scissione %d", a_rand.numero_atomico);
                
                if (a_rand.numero_atomico > var->MIN_N_ATOMICO && figlio.numero_atomico > var->MIN_N_ATOMICO) {
                    int liberata = energy(a_rand.numero_atomico, figlio.numero_atomico);
                    if(liberata>var->ENERGY_EXPLODE_THRESHOLD){
                        printf("\ncentrale esplosa, troppa energia liberata\n");
                        var->flagTerminazione=1;
                        dettShm();
                        endProcess();
                    }
                    printf("\nenergia liberata: %d", liberata);
                    centrale->energia += liberata;
                } else {
                            printf("\naumento scorie\n");
                            var->fork_atomi--;
                            --centrale->n_atomi;
                            printf("-----------------------------------------il valore di fork atomi è %d,e abbiamo %d atomi nella centrale",var->fork_atomi,centrale->n_atomi);
                            centrale->scorie += 2;
                            
                            dettShm();
                            endProcess();
                        }
                var->fork_atomi--;
                

                atomi[centrale->n_atomi] = figlio;
                centrale->n_atomi++;
                printf("-----------------------------------------il valore di fork atomi è %d e abbiamo %d atomi nella centrale",var->fork_atomi,centrale->n_atomi);
                dettShm();
                endProcess();
}
