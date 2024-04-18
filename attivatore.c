#include "lib_header.h"

int main() {
    //createIPCS();
    loadIPCs();
    
    printf("\n\nBenvenuto in attivatore!\n");
    message.msg_type = 1;
    int i=0;
    while (i<50) {
        
        if (msgsnd(msgPila, &message, sizeof(message)-sizeof(long), 0) == -1) {
            ERROR;
            exit(1);
        }
        attShm();
        ++var->fork_atomi;
        dettShm();
        printf("Messaggio inviato all'atomo.\n");
        i++;
        sleep(0.3);

    }
    unloadIPCs();
    return 0;
}

