#include "lib_header.h"
//ATTIVATORE NON CREA ATOMI MA COMUNICA LA NECESSITà DI EFFETTUARE LA SCISSION

int main(int argc, char const *argv[]){
    struct msg_buffer {
    long msg_type;
} message;
    message.msg_type = 1; // Imposta il tipo di messaggio

    // Invia il messaggio all'Atomo


        
    int msgid = msgget(ftok("attivatore.c", 'z'), IPC_CREAT | 0666);
    if (msgid == -1) {
        perror("msgget");
        exit(1);
    }
    if (msgsnd(msgid, &message, sizeof(message), 0) == -1) {
        perror("msgsnd");
        exit(1);
    }
    printf("Messaggio inviato all'atomo.\n");

    

    return 0;
}
