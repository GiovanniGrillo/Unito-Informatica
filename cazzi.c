#include "lib_header.h"


int main()
{
    createIPCS();
    if (set_sem(semShm, 0, 1) == -1) ERROR;
    attShm();
    stampa();
    dettShm();
}