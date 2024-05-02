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

#define PERMISSIONS  0666
#define FTOK_FILE    "attivatore.c"

#define ERROR                                                                                                                              \
    if (errno){                                                                                                                            \
    fprintf(stderr, "ERROR - line %d: file \"%s\" (pid %ld) - n %d - (%s)\n", __LINE__, __FILE__, (int)getpid(), errno, strerror(errno));  \
        exit(1);                                                                                                                           \
    }

void createIPCS() {
    if ((shmVar  = shmget(ftok(FTOK_FILE, 'a'), sizeof(Var), IPC_CREAT | IPC_EXCL | PERMISSIONS)) == -1) ERROR;
    if ((var     = shmat(shmVar, NULL, 0)) == (void *) -1)                                               ERROR;
    char temp[100];
    out_progetto= fopen("Progetto.out", "w");
    setbuf(out_progetto, NULL);
    var->ENERGY_DEMAND            = 100;
    var->ENERGY_EXPLODE_THRESHOLD = 500000;
    var->flagTerminazione         = 0;
    var->fork_atomi               = 0;
    var->MIN_N_ATOMICO            = 5;
    var->N_ATOMI_INIT             = 1000;
    var->N_ATOM_MAX               = 40;   
    var->STEP_ALIMENTAZIONE       = 700000000; //0.7s
    var->STEP_ATTIVATORE          = 900000000; //0.9s

    if ((shmAtomi       = shmget(ftok(FTOK_FILE, 'b'), sizeof(Atomo) * 50000, IPC_CREAT | IPC_EXCL | PERMISSIONS)) == -1) ERROR;
    if ((semShm         = semget(ftok(FTOK_FILE, 'c'), 10, IPC_CREAT | IPC_EXCL | PERMISSIONS)) == -1) ERROR;
    if ((semProcessi    = semget(ftok(FTOK_FILE, 'd'), 10, IPC_CREAT | IPC_EXCL | PERMISSIONS)) == -1) ERROR;
    if ((msgPila        = msgget(ftok(FTOK_FILE, 'e'),     IPC_CREAT | IPC_EXCL | PERMISSIONS)) == -1) ERROR;
    if ((semFissione    = semget(ftok(FTOK_FILE, 'f'), 10, IPC_CREAT | IPC_EXCL | PERMISSIONS)) == -1) ERROR;
    if ((semAttivatore  = semget(ftok(FTOK_FILE, 'g'), 10, IPC_CREAT | IPC_EXCL | PERMISSIONS)) == -1) ERROR;
    if ((semCentrale    = semget(ftok(FTOK_FILE, 'h'), 10, IPC_CREAT | IPC_EXCL | PERMISSIONS)) == -1) ERROR;
    if ((shmCentrale    = shmget(ftok(FTOK_FILE, 'l'), sizeof(Centrale) * (var->ENERGY_DEMAND), IPC_CREAT | IPC_EXCL | PERMISSIONS)) == -1) ERROR;
    if ((centrale       = shmat(shmCentrale,NULL,0))                                            == -1) ERROR;
   

    centrale->energia = var->ENERGY_DEMAND;
    centrale->n_atomi = 0;
    centrale->scorie  = 0;

    if((shmdt(centrale)) == -1) ERROR;

    return;
}

void attShm() {
    reserveSem (semShm,0);
    if ((centrale = shmat(shmCentrale, NULL, 0)) == (void*) -1) ERROR;
    if ((atomi    = shmat(shmAtomi,    NULL, 0)) == (void*) -1) ERROR;
    return;
}

void loadIPCs() {
    if ((shmVar         = shmget(ftok(FTOK_FILE, 'a'), sizeof(Var),                           PERMISSIONS)) == -1) ERROR;
    if ((var            = shmat (shmVar, NULL, 0)) == (void *) -1)                                                 ERROR;
    if ((shmAtomi       = shmget(ftok(FTOK_FILE, 'b'), sizeof(Atomo) * (var->ENERGY_DEMAND), PERMISSIONS)) == -1) ERROR;
    if ((semShm         = semget(ftok(FTOK_FILE, 'c'), 10,                                    PERMISSIONS)) == -1) ERROR;
    if ((semProcessi    = semget(ftok(FTOK_FILE, 'd'), 10,                                    PERMISSIONS)) == -1) ERROR;
    if ((msgPila        = msgget(ftok(FTOK_FILE, 'e'),                                        PERMISSIONS)) == -1) ERROR;
    if ((semFissione    = semget(ftok(FTOK_FILE, 'f'), 10,                                    PERMISSIONS)) == -1) ERROR;
    if ((semAttivatore  = semget(ftok(FTOK_FILE, 'g'), 10,                                    PERMISSIONS)) == -1) ERROR;
    if ((semCentrale    = semget(ftok(FTOK_FILE, 'h'), 10,                                    PERMISSIONS)) == -1) ERROR;
    if ((shmCentrale    = shmget(ftok(FTOK_FILE, 'l'), sizeof(Centrale) * (var->ENERGY_DEMAND),  PERMISSIONS)) == -1) ERROR;

    return;
}

void dettShm() {
    if((shmdt(atomi)) == -1)    ERROR;
    if((shmdt(centrale)) == -1) ERROR;
    releaseSem(semShm,0);
    return;
}

void deallocIPC(){
    if (shmctl(shmVar,       IPC_RMID, 0) == -1) { ERROR; }  else  printf("\n     shmVar        |   deallocati     \n");
    if (shmctl(shmAtomi,     IPC_RMID, 0) == -1) { ERROR; }  else  printf("     shmAtomi      |   deallocati     \n");
    if (shmctl(shmCentrale,  IPC_RMID, 0) == -1) { ERROR; }  else  printf("     shmCentrale   |   deallocata     \n");
    if (semctl(semShm,       IPC_RMID, 0) == -1) { ERROR; }  else  printf("     semShm        |   deallocati     \n");
    if (semctl(semProcessi,  IPC_RMID, 0) == -1) { ERROR; }  else  printf("     semProcessi   |   deallocati     \n");
    if (msgctl(msgPila,      IPC_RMID, 0) == -1) { ERROR; }  else  printf("     msgPila       |   deallocati     \n");
    if (semctl(semFissione,  IPC_RMID, 0) == -1) { ERROR; }  else  printf("     semFissione   |   deallocati     \n");
    if (semctl(semAttivatore,IPC_RMID, 0) == -1) { ERROR; }  else  printf("     semFissione   |   deallocati     \n");
    if (semctl(semCentrale,IPC_RMID, 0) == -1) { ERROR; }  else  printf("     semFissione   |   deallocati     \n");
    return;
}

void unloadIPCs() {
    if((shmdt(var)) == -1) ERROR;
    return;
}


int reserveSem(int id_sem, int n_sem) {
    struct sembuf s_ops;
    s_ops.sem_num = n_sem;
    s_ops.sem_op  = -1;
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
    s_ops.sem_op  = 1;
    s_ops.sem_flg = 0;
    return semop(id_sem, &s_ops, 1);
}

int set_sem(int semID, int semNum, int val) {
    union semun arg;
    arg.val = val;
    return semctl(semID, semNum, SETVAL, arg);
}

pid_t newProcess() {
    reserveSem(semFissione,0);
  //releaseSem(semProcessi, 0);
    return fork();
}

void endProcess() {
  
    exit(0);
}

int creazione_atomi(int numero_atomi_da_creare)
{
    int i = 0;
    printf("ehy centrale n_atomi è uguale a %d", centrale->n_atomi);
    while(i<numero_atomi_da_creare)
    {
    
        atomi[centrale->n_atomi].numero_atomico = (rand() % var->N_ATOM_MAX) + 1;
        atomi[centrale->n_atomi].pidAtomo = (0) ;
        ++centrale->n_atomi;
        ++i;
        
    }
    printf("\n(funzione creazione atomi)Il valore di var->n_atomi è %d ", centrale->n_atomi);

    return 0;
}

void stampa() {
    for(int giorno = 0; giorno < SIM_DURATION; ++giorno) {
        reserveSem(semAttivatore,0);
        reserveSem(semProcessi,  0);

        fprintf(out_progetto, "\n╔═════════════════════════════╗\n");
        fprintf(out_progetto,   "║          GIORNO %2d          ║\n", giorno + 1);
        fprintf(out_progetto,   "╠═════════════════════════════╝\n║\n");

        attShm(); {

            fprintf(out_progetto,"║ Numero atomi %d"    ,centrale->n_atomi);
            fprintf(out_progetto,"\n║ Energia prodotta %d",centrale->energia);
            fprintf(out_progetto,"\n║ Numero scorie %d"   ,centrale->scorie);
            fprintf(out_progetto,"\n║ Prelevo energia per la centrale\n");
            if ((centrale->energia)-(var->ENERGY_DEMAND)<0)
             {
                 var->flagTerminazione=1;
                 fprintf(out_progetto,"\n██══█══█══█══█BLACKOUT DELLA CENTRALE█══█══█══█══██");
                 dettShm();
                 endProcess();
             }
             //prelievo giornaliero dell'energia
            centrale->energia=centrale->energia-var->ENERGY_DEMAND;}
        dettShm();
        if(giorno==SIM_DURATION-1){
            var->flagTerminazione=1;
        }
        releaseSem(semAttivatore,0);
        releaseSem(semProcessi,0);

        sleep(1);
    }

    fprintf(out_progetto,"\nIl valore di flagTerminazione è %d\n", var->flagTerminazione);
    fprintf(out_progetto,"╔═════════════════════════════╗\n");
    fprintf(out_progetto,"║          Terminato          ║\n");
    fprintf(out_progetto,"╠═════════════════════════════╢\n\n");
    return;
}