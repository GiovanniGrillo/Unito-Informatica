#include "lib_header.h"
int main()
{
    pid_t pidAtomo;
    printf("Sono dentro! \n");
    createIPCS();
    printf("Setto il semaforo \n");
    printf("Finito di settare il semaforo\n");
    attShm();

    creazione_atomi(20);
    dettShm();

    switch ((pidAtomo=fork())) {
        case -1:    
            ERROR;

        case  0:    
            execl("./atomo", "./atomo", NULL);
            printf("Atomo non avviato correttamente\n");                         
            ERROR;

        default:    
            break;
    }
       
    deallocIPC();

    printf("\nSono fuori! \n");
    return 0;
}