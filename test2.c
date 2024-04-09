#include "lib_header.h"
int main()
{
    printf("Sono dentro! \n");
    createIPCS();
    printf("Setto il semaforo \n");
    if(set_sem(semShm, 0, 1) == -1) ERROR;
    printf("Finito di settare il semaforo\n");
    attShm();
    
    creazione_atomi(20);
   


    dettShm();

    printf("\nSono fuori! \n");
    return 0;
}