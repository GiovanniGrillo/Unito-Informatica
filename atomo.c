#include "lib_atomo.h"

int main() {
    srand(time(NULL));
    printf("Benvenuto in Atomo! \n");

    /* --- Variabili locali --- */
    int exec = 0;
    printf("sto per loaddare \n");
    /* --- Apertura IPC --- */
    loadIPCs();

    while (( var->fork_atomi > 0) ) {
        if (msgrcv(msgPila, &message, sizeof(message) - sizeof(long), 1, 0) == -1) {
            ERROR;
            continue; // Continua il ciclo in caso di errore
        }
        printf("\nMessaggio ricevuto: avvia scissione\n");

        attShm();
        Atomo a_rand = atomi[rand() % (centrale->n_atomi)];
        printf("Numero atomico prima della scissione: %d\n", a_rand.numero_atomico);
        int numero_casuale = rand() % a_rand.numero_atomico + 1;
        dettShm();
        
        switch (a_rand.pidAtomo = newProcess()) {
            case -1:
                perror("Errore nella creazione del processo figlio");
                break;
            case 0:
                // Codice eseguito nel processo figlio
                esegui_scissione(a_rand);
                exit(0);
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
                    printf("\nenergia liberata: %d", liberata);
                    centrale->energia += liberata;
                } else {
                            printf("\naumento scorie\n");
                            var->fork_atomi--;
                            printf("-----------------------------------------il valore di fork atomi è %d",var->fork_atomi);
                            centrale->scorie += 2;
                            --centrale->n_atomi;
                            dettShm();
                            exit(0);
                        }
                var->fork_atomi--;
                printf("-----------------------------------------il valore di fork atomi è %d",var->fork_atomi);

                atomi[centrale->n_atomi] = figlio;
                centrale->n_atomi++;
                dettShm();
                exit(0);
}
