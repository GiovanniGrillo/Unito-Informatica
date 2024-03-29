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
#define STEP_ATTIVATORE 1
#define atomi_da_scindere [10] 
#define MAX_ATOMI 10 // per ora li faccio runnare in locale


#define PERMISSIONS 0744
#define FTOK_FILE "Master.c"
key_t ciao;
key_t ciao1;

#define ERROR                                                                                                                              \
    if (errno){                                                                                                                            \
    fprintf(stderr, "ERROR - line %d: file \"%s\" (pid %ld) - n %d - (%s)\n", __LINE__, __FILE__, (int)getpid(), errno, strerror(errno));  \
        exit(1);                                                                                                                           \
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
    releaseSem(semProcessi, 0);
    return fork();
}
double easynanosleep(double time) {
    sleep(time/1000);
    return (double)0;
}

void endProcess() {
    reserveSem(semProcessi, 0);
    exit(0);
}


void attShm() {
    reserveSem(semShm, 0);
    if(flagTerminazione == 0) {
        if((atomi = shmat(shmAtomi, NULL, 0)) == ( Atomo* ) -1) ERROR;
   
    } 
    else endProcess();
    return;
}

void detShm() {
    if(var -> flagTerminazione == 0) {
        if((shmdt(atomi)) == -1) ERROR;
    }
    releaseSem(semShm, 0);
    return;
}

void createIPCs(char* file) {
    char temp[20];
    char boolean[6];
    int i;
    
    if ((shmAtomi = shmget(ciao, sizeof(Var), IPC_CREAT | IPC_EXCL | PERMISSIONS)) == -1) ERROR;
    if ((var = shmat(shmAtomi, NULL, 0)) == (void *) -1) ERROR;
    
    out_progetto = fopen("Progetto.out", "w");
    in_progetto  = fopen(file, "r");
        setbuf(out_progetto, NULL);
        fprintf(out_progetto, "------------------------------------------------------------------------------\n");
        fprintf(out_progetto, "       Inizio esecuzione progetto di Sistemi Operativi (2023/2024)       \n");
        fprintf(out_progetto, "                                    di                                    \n");
        fprintf(out_progetto, "        Alessndro, Siviero Francesco, Grillo Giovanni            \n");
        fprintf(out_progetto, "------------------------------------------------------------------------------\n");

                                                                                fprintf(out_progetto, "-  %s %d\n","STEP_ATTIVATORE:", STEP_ATTIVATORE);
                                                                                fprintf(out_progetto, "-  %s %d\n","SIM_DURATION:", SIM_DURATION);

        fscanf(in_progetto, "%s %d\n",temp, &var->ENERGY_DEMAND);               fprintf(out_progetto, "-  %s %d\n",temp, var->ENERGY_DEMAND);
        fscanf(in_progetto, "%s %d\n",temp, &var->N_ATOMI_INIT);                fprintf(out_progetto, "-  %s %d\n",temp, var->N_ATOMI_INIT);
        fscanf(in_progetto, "%s %d\n",temp, &var->STEP_ALIMENTAZIONE);          fprintf(out_progetto, "-  %s %d\n",temp, var->STEP_ALIMENTAZIONE);
        fscanf(in_progetto, "%s %d\n",temp, &var->ENERGY_EXPLODE_THRESHOLD);    fprintf(out_progetto, "-  %s %d\n",temp, var->ENERGY_EXPLODE_THRESHOLD);
        fprintf(out_progetto, "------------------------------------------------------------------------------\n\n");

    fclose(in_progetto);
    fclose(out_progetto);

    if ((shmAtomi     = shmget(ftok(ciao1, 'p'), sizeof(Atomo) * var->N_ATOM_MAX   , IPC_CREAT | IPC_EXCL | PERMISSIONS)) == -1) ERROR;
    if ((semShm        = semget(ftok(ciao, 'a'), 1                                 , IPC_CREAT | IPC_EXCL | PERMISSIONS)) == -1) ERROR;
    if ((msgPila       = msgget(ftok(ciao, 'g'),                                     IPC_CREAT | IPC_EXCL | PERMISSIONS)) == -1) ERROR;
    if ((semProcessi   = semget(ftok(ciao, 't'), 1                                 , IPC_CREAT | IPC_EXCL | PERMISSIONS)) == -1) ERROR;

    out_progetto = fopen("Progetto.out", "a");
    setbuf(out_progetto, NULL);

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
    if ((shmVar        = shmget(ftok(FTOK_FILE, 'v'), sizeof(Var)                         , PERMISSIONS)) == -1) ERROR;
    if ((var = shmat(shmVar  , NULL, 0)) == (void*) -1) ERROR;
    if ((shmPila       = shmget(ftok(FTOK_FILE, 'i'), sizeof(int)   * (var -> N_ATOM_MAX) , PERMISSIONS)) == -1) ERROR;
    if ((msgPila       = msgget(ftok(FTOK_FILE, 'g')                                      , PERMISSIONS)) == -1) ERROR;
    if ((semPila       = semget(ftok(FTOK_FILE, 's'), 2                                   , PERMISSIONS)) == -1) ERROR;
    if ((semShm        = semget(ftok(FTOK_FILE, 'a'), 1                                   , PERMISSIONS)) == -1) ERROR;
    if ((semProcessi   = semget(ftok(FTOK_FILE, 't'), 1                                   , PERMISSIONS)) == -1) ERROR;

    out_progetto = fopen("Progetto.out", "a");
    setbuf(out_progetto, NULL);
    set_sem(semProcessi, 0, 0);
    
    return;
}

void unloadIPCs() {
    if((shmdt(var)) == -1) ERROR;
    return;
}