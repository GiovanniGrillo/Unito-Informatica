#include "lib_header.h"
int main()
{
    printf("Sono dentro! \n");
    createIPCS();
    printf("valoreIniziale :%d\n",var->ENERGY_DEMAND);

    attShm();
    
    printf("valore DOpo gli ipc :%d\n",var->ENERGY_DEMAND);


    dettShm();
    deallocIPC();
    printf("Sono fuori! \n");
    return 0;
}
