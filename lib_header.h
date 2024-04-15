#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <errno.h>
#include <time.h>
#include <math.h>

#include "Oggetti.h"

/*Da sistemare le define per le librerie opportune*/
#define atomi_da_scindere [10]
#define PERMISSIONS 0666
#define FTOK_FILE "attivatore.c"

#define ERROR                                                                                                                              \
    if (errno){                                                                                                                            \
    fprintf(stderr, "ERROR - line %d: file \"%s\" (pid %ld) - n %d - (%s)\n", __LINE__, __FILE__, (int)getpid(), errno, strerror(errno));  \
        exit(1);                                                                                                                           \
    }

void createIPCS() {
    //aggiungere il semaforo ipcs
    printf("eccomi");
    
    if ((shmVar  = shmget(ftok("attivatore.c", 'a'), sizeof(Var), IPC_CREAT | IPC_EXCL | PERMISSIONS)) == -1) ERROR;
    
    printf("allora funziona!");

    if ((var     = shmat(shmVar, NULL, 0)) == (void *) -1) ERROR;

    var->ENERGY_DEMAND = 100;
    var->N_ATOMI_INIT = 10;
    var->N_ATOM_MAX = 20;
    var->MIN_N_ATOMICO = 5;
    var->STEP_ALIMENTAZIONE = 2;
    var->ENERGY_EXPLODE_THRESHOLD = 50;
    var->flagTerminazione = 0;
    var->scorie=0;
    var->enrgia=0;
    var->STEP_ATTIVATORE=1;
    var->n_atomi=0;
    var->fork_atomi=0;

    if ((shmAtomi       = shmget(ftok(FTOK_FILE,"b"), sizeof(Atomo) * (var->N_ATOM_MAX + 1), IPC_CREAT | IPC_EXCL | PERMISSIONS)) == -1) ERROR;
    if ((semShm         = semget(ftok(FTOK_FILE, 'c'), 1, IPC_CREAT | IPC_EXCL | PERMISSIONS)) == -1) ERROR;
    if ((semProcessi    = semget(ftok(FTOK_FILE, 'd'), 1, IPC_CREAT | IPC_EXCL | PERMISSIONS)) == -1) ERROR;
    return;
}


void attShm() {
    reserveSem (semShm,0);
    if ((var = shmat(shmVar  , NULL, 0)) == (void*) -1) ERROR;
    if((atomi = shmat(shmAtomi ,NULL,0))==(void*)-1)    ERROR;
    return;
}


void loadIPCs() {
    if ((shmVar        = shmget(ftok("attivatore.c", 'z'), sizeof(Var), PERMISSIONS)) == -1)                                            ERROR;
    if ((var           = shmat (shmVar  , NULL, 0)) == (void*) -1)                                                                      ERROR;
    if ((shmAtomi      = shmget(ftok(FTOK_FILE,"b"), sizeof(Atomo) * (var->N_ATOM_MAX + 1), IPC_CREAT | IPC_EXCL | PERMISSIONS)) == -1) ERROR;
    if ((semProcessi   = semget(ftok(FTOK_FILE, 'd'), 1, PERMISSIONS)) == -1)                                                           ERROR;

    //set_sem(semProcessi, 0, 0);d
    return;
}

void dettShm() {
    if((shmdt(var)) == -1)   ERROR;
    if((shmdt(atomi)) == -1) ERROR;
    releaseSem(semShm,0);
    return;
}

void deallocIPC(){

    if (shmctl(shmVar,   IPC_RMID, 0) == -1)      { ERROR; }   else    printf("\n     shmVar        |   deallocati     \n");
    if (shmctl(shmAtomi, IPC_RMID, 0) == -1)      { ERROR; }   else    printf("     shmAtomi      |   deallocati     \n");
    if (semctl(semShm,   IPC_RMID, 0) == -1)      { ERROR; }   else    printf("     semShm        |   deallocati     \n");
    if (semctl(semProcessi,   IPC_RMID, 0) == -1) { ERROR; }   else    printf("     semProcessi   |   deallocati     \n");
    return;
}

int reserveSem(int id_sem, int n_sem) {
    struct sembuf s_ops;

    s_ops.sem_num = n_sem;
    s_ops.sem_op = -1;
    s_ops.sem_flg = 0;

    return semop(id_sem, &s_ops, 1);
}

union semun {
    int val;
    struct semid_ds *buf;
    short *array;
    struct seminfo *__buf;
    void *__pad;
};

int releaseSem(int id_sem, int n_sem) {
    struct sembuf s_ops;
    s_ops.sem_num = n_sem;
    s_ops.sem_op = 1;
    s_ops.sem_flg = 0;

    return semop(id_sem, &s_ops, 1);
}

int set_sem(int semID, int semNum, int val) {
    union semun arg;
    arg.val = val;
    return semctl(semID, semNum, SETVAL, arg);
}

pid_t newProcess() {
    //(releaseSem(semProcessi, 0);
    return fork();
}

void endProcess() {
    //reserveSem(semProcessi, 0);
    exit(0);
}

int creazione_atomi(int numero_atomi_da_creare)
{
    int i;

    // if ((pila = shmat(shmPila, NULL, 0)) == (int *)-1)
    //     ERROR;

    for (i = 0; i < numero_atomi_da_creare; ++i)
    {
        atomi[var->n_atomi].numero_atomico = (rand() % var->N_ATOM_MAX) + 1;
        //pila[i]         = i;
        var->n_atomi++;
        
    }
    printf("Il valore di var->n_atomi è %d ", var->n_atomi);
    //pila[var->n_atomi] = var->n_atomi;

   

    // if ((shmdt(pila)) == -1)
    //     ERROR;
    return 0;
}





/*void createIPCs(char* file) {
    char temp[20];
    char boolean[6];
    int i;
    // una volta che Var sarà inizializzata si potrà usare sizeof(Var)
    if ((shmAtomi = shmget(ftok("atomo.c", "a"), 2, IPC_CREAT | IPC_EXCL | PERMISSIONS)) == -1) ERROR;
    if ((var = shmat(shmAtomi, NULL, 0)) == (void *) -1) ERROR;
    
    /*out_progetto = fopen("Progetto.out", "b");
    in_progetto  = fopen(file, "c");
        setbuf(out_progetto, NULL);
        printf(out_progetto, "------------------------------------------------------------------------------\n");
        printf(out_progetto, "       Inizio esecuzione progetto di Sistemi Operativi (2023/2024)       \n");
        printf(out_progetto, "                                    di                                    \n");
        printf(out_progetto, "        Alessndro, Siviero Francesco, Grillo Giovanni            \n");
        printf(out_progetto, "------------------------------------------------------------------------------\n");

                                                                             fprintf(out_progetto, "-  %s %d\n","STEP_ATTIVATORE:", STEP_ATTIVATORE);
                                                                                fprintf(out_progetto, "-  %s %d\n","SIM_DURATION:", SIM_DURATION);

        fscanf(in_progetto, "%s %d\n",temp, &var->ENERGY_DEMAND);               fprintf(out_progetto, "-  %s %d\n",temp, var->ENERGY_DEMAND);
        fscanf(in_progetto, "%s %d\n",temp, &var->N_ATOMI_INIT);                fprintf(out_progetto, "-  %s %d\n",temp, var->N_ATOMI_INIT);
        fscanf(in_progetto, "%s %d\n",temp, &var->STEP_ALIMENTAZIONE);          fprintf(out_progetto, "-  %s %d\n",temp, var->STEP_ALIMENTAZIONE);
        fscanf(in_progetto, "%s %d\n",temp, &var->ENERGY_EXPLODE_THRESHOLD);    fprintf(out_progetto, "-  %s %d\n",temp, var->ENERGY_EXPLODE_THRESHOLD);
        fprintf(out_progetto, "------------------------------------------------------------------------------\n\n");

    fclose(in_progetto);
    fclose(out_progetto);


    //printf("%d \n", ftok("prova.c", "z"));
    //printf("%d \n", shmget(ftok("prova.c", 'q'), 5   , IPC_CREAT | IPC_EXCL | 744));

    if ((shmAtomi     = shmget(ftok("Movimento.c", 'd'), 10  , IPC_CREAT | IPC_EXCL | PERMISSIONS)) == -1) ERROR;
    if ((semShm        = semget(ftok("Master.c", 'e'), 10                                 , IPC_CREAT | IPC_EXCL | PERMISSIONS)) == -1) ERROR;
    if ((msgPila       = msgget(ftok("Giornaliera.c", 'f'),                                     IPC_CREAT | IPC_EXCL | PERMISSIONS)) == -1) ERROR;
    if ((semProcessi   = semget(ftok("/Makefile", 'g'), 10                                 , IPC_CREAT | IPC_EXCL | PERMISSIONS)) == -1) ERROR;

    //out_progetto = fopen("Progetto.out", "a");
    //setbuf(out_progetto, NULL);

    return;
}

void deallocIPCs() {
    int i;
    reserveSem(semShm, 0);
                                                                printf("--------------------------------------\n");
    if (shmctl(shmAtomi      , IPC_RMID, 0) == -1) { ERROR; } else printf("     shmAtomi      |   deallocati     \n");
    if (semctl(semShm        , IPC_RMID, 0) == -1) { ERROR; } else printf("     semShm        |   deallocati     \n");
    if (msgctl(msgPila       , IPC_RMID, 0) == -1) { ERROR; } else printf("     msgPila       |   deallocati     \n");
    if (semctl(semProcessi   , IPC_RMID, 0) == -1) { ERROR; } else printf("     semProcessi   |   deallocati     \n");
                                                                printf("--------------------------------------\n");
    return;
}

void loadIPCs() {
    if ((shmVar        = shmget(ftok(FTOK_FILE, 'i'), sizeof(Var)                         , PERMISSIONS)) == -1) ERROR;
    if ((var = shmat(shmVar  , NULL, 0)) == (void*) -1) ERROR;
    if ((shmPila       = shmget(ftok(FTOK_FILE, 'j'), sizeof(int)   * (var -> N_ATOM_MAX) , PERMISSIONS)) == -1) ERROR;
    if ((msgPila       = msgget(ftok(FTOK_FILE, 'k')                                      , PERMISSIONS)) == -1) ERROR;
    if ((semPila       = semget(ftok(FTOK_FILE, 'l'), 2                                   , PERMISSIONS)) == -1) ERROR;
    if ((semShm        = semget(ftok(FTOK_FILE, 'm'), 1                                   , PERMISSIONS)) == -1) ERROR;
    if ((semProcessi   = semget(ftok(FTOK_FILE, 'n'), 1                                   , PERMISSIONS)) == -1) ERROR;

    //out_progetto = fopen("Progetto.out", "a");
    //setbuf(out_progetto, NULL);
    //set_sem(semProcessi, 0, 0);
    
    return;
}
void unloadIPCs() {
    if((shmdt(var)) == -1) ERROR;
    return;
}
*/