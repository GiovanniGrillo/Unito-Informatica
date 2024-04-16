#include "lib_header.h"

int main() {
    pid_t pidAtomo;
    pid_t pidAttivatore;
    createIPCS();

    if (set_sem(semShm, 0, 1) == -1) ERROR;
    attShm();
    printf("\nvaolre di centrale energia %d", centrale->energia);
    printf("\nvaolre di centrale scorie %d", centrale->scorie);
    printf("\nvaolre di centrale atomi %d", centrale->n_atomi);

    creazione_atomi(20);

    printf("\nvaolre di centrale atomi dopo la funzione %d\n", centrale->n_atomi);
    dettShm();

    printf("\nSono fuori! \n");
    return 0;
}
