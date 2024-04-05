#include <stdio.h>
#include <stdlib.h> // Per la funzione malloc
#include <sys/ipc.h>
#include <sys/shm.h>
#include "Oggetti.h"
#include <sched.h>


// Definizione della struttura dati condivisa

// Funzione per attaccare l'area di memoria condivisa
struct Var *attshm() {
    key_t KEY = ftok("cazzi.c", 'a');
    int shmid = shmget(KEY, sizeof(struct Var), IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    // Collegamento all'area di memoria condivisa
    struct Var *sharedVar = (struct Var *)shmat(shmid, NULL, 0);
    if (sharedVar == (void *)-1) {
        perror("shmat");
        exit(1);
    }

    return sharedVar;
}
struct Atomo crea_atomo() {
    printf("sto iniziando a creare un atomo\n");
    struct Atomo nuovo_atomo;
    nuovo_atomo.numero_atomico = (rand() % var->N_ATOM_MAX) + 1;
    printf("atomo creato\n");
    return nuovo_atomo;
    
}
void simulateFission(struct Atomo *padre) {
    // Verifica se il numero atomico è minore o uguale a MIN_N_ATOMICO
    if (padre->numero_atomico <= var->MIN_N_ATOMICO) {
       struct Var *sharedVar= attshm(); 
        sharedVar->scorie=sharedVar->scorie+1;
        shmdt(sharedVar);
        printf("Atomo con numero atomico minore o uguale a MIN_N_ATOMICO. Terminato e conteggiato nelle statistiche fra le scorie.\n");
        return;
    }

    // Fork per creare un nuovo atomo (processo figlio)
    pid_t pid = fork();

    if (pid == -1) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Processo figlio
        int numero_casuale = rand() % padre->numero_atomico + 1;
        printf("Processo padre  con numero atomico: %d\n", padre->numero_atomico);


        struct Atomo figlio = {(padre->numero_atomico)-numero_casuale};
        padre->numero_atomico =(padre->numero_atomico -(figlio.numero_atomico));
        printf("Processo figlio creato con numero atomico: %d\n", figlio.numero_atomico);
        
        // Simula la scissione
        //printf("Scissione avvenuta. Numero atomico figlio: %fd\n", figlio.numero_atomico);

        // Calcola l'energia liberata durante la scissione
        int releaseEnergy = energy(padre->numero_atomico, figlio.numero_atomico);
        struct Var *sharedVar= attshm(); 
        sharedVar->enrgia=sharedVar->enrgia+releaseEnergy;
        shmdt(sharedVar);

        



        printf("Energia liberata: %d\n", releaseEnergy);
        printf("dopo la scissione padre: %d figlio %d",padre->numero_atomico,figlio.numero_atomico);
        /*comunicare l'energia alla centrale*/

        exit(EXIT_SUCCESS);
    } else {
        // Processo padre
        wait(NULL);
        
    }
}
int energy(int n1, int n2) {
    return n1 * n2 - (n1 > n2 ? n1 : n2);
}


int main() {
    printf("Benvenuto in cazzi!\n");

    srand((unsigned int)time(NULL));
    
    printf("Benvenuto in cazzi2!\n");
    

    // Stacca l'area di memoria condivisa
   

    struct Atomo Iniziale =crea_atomo(); 
    printf("%d\n",Iniziale.numero_atomico);
    simulateFission(&Iniziale);



    printf("addio in cazzi!\n");

    return 0;
}

/*
**************************************************



int main() {
    pid_t pidMovimento; 
    pid_t pidGiornaliera;
    pid_t pidMaelstrom;
    int i;
    setbuf(stdout, NULL);
    srand(time(NULL));
 
    switch ((pidMovimento = fork())) {
        case -1:    
            ERROR;

        case  0:    
            execl("./Movimento", "./Movimento", NULL);
                printf("Movimento non avviato correttamente\n");                         
                ERROR;

        default:    
            break;
    }

    printf("------------------------------------\n");
    printf("     PROCESSO Maelstrom - Start     \n");
    printf("------------------------------------\n");

    switch ((pidMaelstrom = fork())) {
        case -1:    
            ERROR;

        case  0:    
            if(var->setOnMaelstrom == FALSE) exit(0);
                execl("./Maelstrom", "./Maelstrom", NULL); 
                printf("Maelstrom non avviato correttamente\n");                         
                ERROR;
                exit(0);

        default:    
            break;
    }
    
    printf("--------------------------------------\n");
    printf("     PROCESSO Giornaliera - Start     \n");
    printf("--------------------------------------\n");

    switch ((pidGiornaliera = fork())) {
        case -1:    
            ERROR;

        case  0:    
            execl("./Giornaliera", "./Giornaliera", NULL); 
            printf("Giornaliera non avviato correttamente\n");
            kill(pidMovimento, SIGTERM);
            ERROR;

        default:    
            waitpid(pidGiornaliera, NULL, 0);
    } 

    kill(pidMovimento, SIGTERM);
    kill(pidMaelstrom, SIGTERM);
    ++var->flagTerminazione; 

    for(i = 0;semctl(semProcessi, 0, GETVAL) != 0; ++i){
        sleep(1);
        printf("   PROCESSI - ancora attivi: %d\n", semctl(semProcessi, 0, GETVAL));
        if(i>5){
            printf("   ERRORE - TERMINAZIONE FORZATA\n");
            killpg(getpid(), SIGKILL);
        }
    }
    
    --var->flagTerminazione;
    attShm();{
        if (stampa(FINALE) == -1) ERROR;
    }
        detShm();

    deallocIPCs();

    printf("--------------------------------------\n");
    printf("     PROCESSO Master - Terminato      \n");
    printf("--------------------------------------\n");
        
    exit(0);
}
*/