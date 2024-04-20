#include "lib_header.h"

//attivatore
int main() {

    loadIPCs();
    
    printf("\n\n\033[1;31mBenvenuto in attivatore!\033[0m\n");
    message.msg_type = 1;
    int j=0;
    int i=0;

while (flagTerminazione != 1) {
    reserveSem(semAttivatore, 0);
    int i = 0; // Assicurati di inizializzare i all'interno del primo ciclo
    while (i < 100) {
        if(var->flagTerminazione==1){
            exit(0);
        }
        if (msgsnd(msgPila, &message, sizeof(message) - sizeof(long), 0) == -1) {
            perror("smsgsnd");
            exit(1);
        }
        attShm();
        ++var->fork_atomi;
        printf("\033[1;31mMessaggio inviato all'atomo. messaggio n°%d\033[0m\n", i + 1);
        i++;
        dettShm();
    }
    releaseSem(semAttivatore, 0);

    struct timespec req = {.tv_sec = 0, .tv_nsec = var->STEP_ATTIVATORE};
    nanosleep(&req, NULL);

}
unloadIPCs();

return 0;
}