#include "lib_atomo.h"

int numMessaggiRicevuti = 0;
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
        
        ++numMessaggiRicevuti;
        attShm();
        
        
        
        Atomo a_PADRE = atomi[rand() % (centrale->n_atomi)];
        //dettShm();
        
        switch (a_PADRE.pidAtomo = newProcess()) {
            case -1:
                perror("Errore nella creazione del processo figlio");
                break;
            case 0:
                // Codice eseguito nel processo figlio
                
                esegui_scissione(a_PADRE);
          
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

void esegui_scissione(Atomo a_PADRE) {
    printf("\n\033[1;34mMessaggio ricevuto, msg n°%d \033[0m", numMessaggiRicevuti);
    printf("\nSTO ESEGUENDO SCISSIONE\n");
    if(a_PADRE.numero_atomico<var->MIN_N_ATOMICO){

        printf("\n\033[1;34maumento scorie \033[0m ");
        var->fork_atomi;
        --centrale->n_atomi;
        printf("\n\033[1;34m-----------------------------------------il valore di fork atomi è %d,e abbiamo %d atomi nella centrale \033[0m ",var->fork_atomi,centrale->n_atomi);
        centrale->scorie++;                  
        dettShm();
        releaseSem(semFissione,0);
        endProcess();
    }else{

                 printf("\n\033[1;34mNUMERO ATOMICO PADRE %d\033[0m", a_PADRE.numero_atomico);
                // attShm();
                int numero_casuale = rand() % (a_PADRE.numero_atomico-1)+1;
                printf("\n%d numero casuale", numero_casuale);
                struct Atomo figlio;
                 figlio.numero_atomico = a_PADRE.numero_atomico - numero_casuale;
                a_PADRE.numero_atomico -= figlio.numero_atomico;
                
                printf("\n \033[1;34m atomo figlio creato con numero atomico: %d, il padre ha numero atomico post scissione :%d\n\033[0m", figlio.numero_atomico,a_PADRE.numero_atomico);
                int liberata = energy(a_PADRE.numero_atomico, figlio.numero_atomico);
                if((centrale->energia += liberata)>var->ENERGY_EXPLODE_THRESHOLD){
                   printf("\ncentrale esplosa, troppa energia liberata\n");
                        var->flagTerminazione=1;
                        dettShm();
                        endProcess();
                }
                printf("\n\033[1;34menergia liberata: %d \033[0m ", liberata);
                centrale->energia += liberata;
                var->fork_atomi--;
                atomi[centrale->n_atomi] = figlio;
                centrale->n_atomi++;
                printf("\n\033[1;34m-----------------------------------------il valore di fork atomi è %d e abbiamo %d atomi nella centrale \033[0m ",var->fork_atomi,centrale->n_atomi);
                dettShm();
                releaseSem(semFissione,0);
                endProcess();
                }
}