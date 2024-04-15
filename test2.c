#include "lib_header.h"
int main()
{
    pid_t pidAtomo;
    pid_t pidAttivatore;
    createIPCS();

    if (set_sem(semShm, 0, 1) == -1) ERROR;
    attShm();

    creazione_atomi(20);
    dettShm();

 
       
    

    printf("\nSono fuori! \n");
    return 0;
}