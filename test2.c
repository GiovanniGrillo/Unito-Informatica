#include "lib_header.h"

int main() {
    pid_t pidAtomo;
    pid_t pidAttivatore;
    pid_t pidAlimentatore;

    setbuf(stdout, NULL);
    srand(time(NULL));
    
    createIPCS();
    if (set_sem(semShm, 0, 1) == -1) ERROR;
    if(set_sem(semProcessi, 0, 1)==-1) ERROR;
    if(set_sem(semFissione,0,1)==-1) ERROR;
    attShm();
    creazione_atomi(var->N_ATOMI_INIT);
    dettShm();
   

    pidAttivatore = fork();
    if (pidAttivatore == -1) {
        ERROR;
    } else if (pidAttivatore == 0) {
        execl("./attivatore", "./attivatore", NULL);
        printf("\nAttivatore non avviato correttamente\n");
        ERROR;
        exit(0);
    }

    pidAtomo = fork();
    if (pidAtomo == -1) {
        ERROR;
    } else if (pidAtomo == 0) {
        execl("./atomo", "./atomo", NULL);
        printf("\nAtomo non avviato correttamente\n");
        ERROR;
        exit(0);
    }

    pidAlimentatore = fork();
    if (pidAlimentatore == -1) {
        ERROR;
    } else if (pidAlimentatore == 0) {
        execl("./alimentatore", "./alimentatore", NULL);
        printf("\nAlimentatore non avviato correttamente\n");
        ERROR;
        exit(0);
    }
    
    // Aspetta la terminazione di tutti e tre i processi
    waitpid(pidAttivatore, NULL, WNOHANG);
    waitpid(pidAtomo, NULL, 0);
    waitpid(pidAlimentatore, NULL,0);

    

    kill(pidAttivatore,     SIGTERM);
    kill(pidAtomo,          SIGTERM);
    kill(pidAlimentatore,   SIGTERM);
    var->flagTerminazione = 1;

    printf("\nSono fuori! \n");
    return 0;
}


