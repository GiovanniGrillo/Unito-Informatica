#include "lib_header.h"

int main(int argc, char const *argv[]) {
    //createIPCS();
     loadIPCs();
    
    printf("benvenuto in attivatore");
    message.msg_type = 1;

    printf("sto per entrare nel while");
    int i=0;
    while (i<5) {
        sleep(var->STEP_ATTIVATORE);
        if (msgsnd(msgPila, &message, sizeof(message)-sizeof(long), 0) == -1) {
            ERROR;
            exit(1);
        }
        attShm();
        ++var->fork_atomi;
        dettShm();
        printf("Messaggio inviato all'atomo.\n");

        ++i;
    }
    return 0;
}

