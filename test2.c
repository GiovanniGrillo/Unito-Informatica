#include "lib_header.h"

int main() {
    pid_t pidAtomo;
    pid_t pidAttivatore;
    createIPCS();
    if (set_sem(semShm, 0, 1) == -1) ERROR;
    attShm();
    creazione_atomi(20);
    dettShm();



    switch ((pidAttivatore = fork())) {
        case -1:    
            ERROR;
        case 0:    
            execl("./attivatore", "./attivatore", NULL);
            printf("\nAttivatore non avviato correttamente\n");                         
            ERROR;
            exit(0);
            break;
        default:
            wait(NULL);    
            break;
    }

    switch ((pidAtomo = fork())) {
        case -1:    
            ERROR;
        case 0:    
            execl("./atomo", "./atomo", NULL);
            printf("\nAtomo2 non avviato correttamente\n");                         
            ERROR;
            exit(0);
            break;
        default:   
              wait(NULL); 
            break;
    }



    printf("\nSono fuori! \n");
    return 0;
}
