#include "lib_header.h"


int main(){
    pid_t pidAtomo; 
    pid_t pidAttivatore;
    createIPCS();
    
    

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
    deallocIPC();
     printf("test ha finito le cose da fare \n");
  

}



