#include "lib_header.h"

int main(int argc, char const *argv[]) {
    
    /*PROVA*/
     key_t key = 1234;
    int msgid = msgget(key, IPC_CREAT | 0666);
    /*PROVA*/

    createIPCS();
    if (set_sem(semShm, 0, 1) == -1) {
        ERROR;
    }
    // loadIPCs();
    printf("benvenuto in attivatore");
  
    message.msg_type = 1;
    //int msgid = msgget(ftok("attivatore.c", 'm'), IPC_CREAT | 0666);
    if (msgid == -1) {
        perror("msgget");
        exit(1);
    }
    printf("sto per entrare nel while");
    int i =0;
    while (i<5) {
        sleep(var->STEP_ATTIVATORE);
        if (msgsnd(msgid, &message, sizeof(message)-sizeof(long), 0) == -1) {
            perror("msgsnd");
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

