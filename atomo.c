#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <math.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include "lib_atomo.h"



int main() {
    printf("Benvenuto in Atomo! \n");
        testcoda();


        // Simula la creazione di un atomo iniziale
        attShm();
        struct Atomo iniziale = crea_atomo();
        printf("Atomo iniziale creato con numero atomico: %d\n", iniziale.numero_atomico);

        // Simula la fissione dell'atomo iniziale
        
        simulateFission(&iniziale);
        dettShm();
    return 0;
    }


 






int testcoda() {
    key_t msg_key;
    msg_key = ftok("attivatore.c", 'z');
    int msgid = msgget(msg_key, IPC_CREAT | 0666);
    if (msgid == -1) {
        perror("msgget");
        exit(1);
    }

    // Attende un messaggio di tipo 1
    if (msgrcv(msgid, &message, sizeof(message), 1, 0) == -1) {
        perror("msgrcv");
        exit(1);
    }
    printf("Messaggio ricevuto dall'attivatore.\n");

    // Opzionale: Rimuovi la coda di messaggi dopo l'uso
    // msgctl(msgid, IPC_RMID, NULL);

    return 0;
}






