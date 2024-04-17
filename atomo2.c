#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <math.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include "lib_atomo.h"


int main() {
    srand(time(NULL));
    printf("Benvenuto in Atomo! \n");
    /* --- Variabili locali --- */
    int exec = 0;

   /* --- Apertura IPC --- */
    // createIPCS();
    // if (set_sem(semShm, 0, 1) == -1) ERROR;
    loadIPCs();
    attShm();
    creazione_atomi(20);
    printf("\noraoroaoraora");
    
    dettShm();

   //if (set_sem(semShm, 0, 1) == -1) ERROR;
  
     
    /* --- Possibili semafori extra --- */
    printf("\nciao!");
    for (; exec < 3; ++exec) {
    // Selezione di un atomo
    
    printf("\exec%d", exec);
        // int prova_msg = msgrcv(msgPila, &message, (sizeof(message)-sizeof(long)), 0, 0);
        // printf("Messaggio: %d", prova_msg);
      

        attShm();
        Atomo a_rand = atomi[rand() % (centrale->n_atomi)];
        dettShm();
        
        switch (a_rand.pidAtomo = newProcess()) {
            case -1: 
                printf("Errore pidMovimento (exec = %d)\n", exec); 
                break;
            case 0: {
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
                            centrale->scorie += 2;
                            --centrale->n_atomi;
                            dettShm();
                            exit(0);
                        }

                atomi[centrale->n_atomi] = figlio;
                centrale->n_atomi++;
                dettShm();
                exit(0);
            }
            default:
                break;
        }
    }

 
 return 0;

}