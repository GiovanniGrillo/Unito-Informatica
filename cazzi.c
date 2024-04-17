#include "lib_header.h"


int main()
{
    createIPCS();

    pid_t pippolo;
    switch (pippolo=fork())
    {
    case -1 /* constant-expression */:
        ERROR;
        break;
    case 0:
        execl("./atomo", "./atomo", NULL);
        printf("Atomo non avviato correttamente\n");
        ERROR;
    default:
        break;
    }
    return 0;
}
