#include "lib_header.h"
#include "lib_alimentatore.h"

int main(){
    pid_t pidAtomo; 
    pid_t pidAttivatore;
    createIPCS();

    if(set_sem(semShm, 0, 1) == -1) ERROR;
    
    switch ((pidAttivatore = fork())) {
        case -1:
            ERROR;

        case  0:
                execl("./attivatore", "./attivatore", NULL); 
                printf("Attivatore non avviato correttamente\n");
                ERROR;
                exit(0);

        default:
            break;
    }


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


    printf("provo a fare partire attivatore");
    printf("test ha finito le cose da fare \n");

}