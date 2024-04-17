#include "lib_header.h"

int main() {
    pid_t pidAtomo;
    // pid_t pidAttivatore;
    createIPCS();

    if (set_sem(semShm, 0, 1) == -1) ERROR;
    switch ((pidAtomo = fork())) {
        case -1:    
            ERROR;
        case 0:    
            execl("./atomo2", "./atomo2", NULL);
            printf("\nAtomo2 non avviato correttamente\n");                         
            ERROR;
        default:    
            break;
    }

    printf("\nSono fuori! \n");
    return 0;
}
