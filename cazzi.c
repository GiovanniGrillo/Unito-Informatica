#include "lib_header.h"

int main()
{
    createIPCS();
      if(set_sem(semShm,           0, 1) == -1) ERROR;
        if(set_sem(semAttivatore,    0, 1) == -1) ERROR;
        if(set_sem(semFissione,      0, 1) == -1) ERROR;
        if(set_sem(semProcessi,      0, 1) == -1) ERROR;
    pid_t pidAlimentatore;
   pidAlimentatore = fork();
        if (pidAlimentatore == -1) {
            ERROR;
        } else if (pidAlimentatore == 0) {
            execl("./alimentatore", "./alimentatore", NULL);
            printf("\nAlimentatore non avviato correttamente\n");
            ERROR;
            exit(0);
        }
    return 0;
}

  