#include "lib_header.h"

int main() {
    //createIPCS();
    loadIPCs();
    
    printf("\n\n\033[1;31mBenvenuto in attivatore!\033[0m\n");
    message.msg_type = 1;
    int i=0;
    while (i<30) {
        reserveSem(semProcessi,0);
        
        if (msgsnd(msgPila, &message, sizeof(message)-sizeof(long), 0) == -1) {
            ERROR;
            exit(1);
        }
        attShm();
        ++var->fork_atomi;
        
        printf("\033[1;31mMessaggio inviato all'atomo.\033[0m\n");
        i++;
        dettShm();
        releaseSem(semProcessi, 0);
        sleep(0.3);

    }
    unloadIPCs();
    return 0;
}

