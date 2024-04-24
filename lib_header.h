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

long int convert_to_nanoseconds(int n) {
    return n * 100000000;
}

void createIPCS(char* file) {
    char temp[100];
    out_progetto= fopen("Progetto.out", "w");
    in_progetto  = fopen(file, "r");
    setbuf(out_progetto, NULL);

    if ((shmVar  = shmget(ftok(FTOK_FILE, 'a'), sizeof(Var), IPC_CREAT | IPC_EXCL | PERMISSIONS)) == -1) ERROR;
    if ((var     = shmat(shmVar, NULL, 0)) == (void *) -1)                                               ERROR;
    
    fprintf(out_progetto, "╔═════════════════════════════════════════════════════════════╗\n");
    fprintf(out_progetto, "║ Inizio esecuzione progetto di Sistemi Operativi (2023/2024) ║\n");
    fprintf(out_progetto, "║                                di                           ║\n");
    fprintf(out_progetto, "║  Grillo Giovanni,                                           ║\n");
    fprintf(out_progetto, "╠═════════════════════════════════════════════════════════════╝\n");
                                                                                fprintf(out_progetto, "║ %s %20d\n","SIM_DURATION:", SIM_DURATION);
    fscanf(in_progetto, "%s %d\n", temp, &var->ENERGY_DEMAND);                  fprintf(out_progetto, "║ %s %20d\n", temp, var->ENERGY_DEMAND);
    fscanf(in_progetto, "%s %d\n", temp, &var->ENERGY_EXPLODE_THRESHOLD);       fprintf(out_progetto, "║ %s %13d\n", temp, var->ENERGY_EXPLODE_THRESHOLD);
    fscanf(in_progetto, "%s %d\n", temp, &var->flagTerminazione);               fprintf(out_progetto, "║ %s %15d\n", temp, var->flagTerminazione);
    fscanf(in_progetto, "%s %d\n", temp, &var->fork_atomi);                     fprintf(out_progetto, "║ %s %21d\n", temp, var->fork_atomi);
    fscanf(in_progetto, "%s %d\n", temp, &var->MIN_N_ATOMICO);                  fprintf(out_progetto, "║ %s %18d\n", temp, var->MIN_N_ATOMICO);
    fscanf(in_progetto, "%s %d\n", temp, &var->N_ATOMI_INIT);                   fprintf(out_progetto, "║ %s %20d\n", temp, var->N_ATOMI_INIT);
    fscanf(in_progetto, "%s %d\n", temp, &var->N_ATOM_MAX);                     fprintf(out_progetto, "║ %s %22d\n", temp, var->N_ATOM_MAX);
    fscanf(in_progetto, "%s %d\n", temp, &var->STEP_ALIMENTAZIONE);
    var->STEP_ALIMENTAZIONE = convert_to_nanoseconds(var->STEP_ALIMENTAZIONE);  fprintf(out_progetto, "║ %s %19d\n", temp, var->STEP_ALIMENTAZIONE);
    fscanf(in_progetto, "%s %d\n", temp, &var->STEP_ATTIVATORE);
    var->STEP_ATTIVATORE = convert_to_nanoseconds(var->STEP_ATTIVATORE);        fprintf(out_progetto, "║ %s %22d\n", temp, var->STEP_ATTIVATORE);

    fclose(in_progetto);
    fclose(out_progetto);

    if ((shmAtomi       = shmget(ftok(FTOK_FILE, 'b'), sizeof(Atomo) * (var->N_ATOM_MAX + 1), IPC_CREAT | IPC_EXCL | PERMISSIONS)) == -1) ERROR;
    if ((semShm         = semget(ftok(FTOK_FILE, 'c'), 10, IPC_CREAT | IPC_EXCL | PERMISSIONS)) == -1) ERROR;
    if ((semProcessi    = semget(ftok(FTOK_FILE, 'd'), 10, IPC_CREAT | IPC_EXCL | PERMISSIONS)) == -1) ERROR;
    if ((msgPila        = msgget(ftok(FTOK_FILE, 'e'),     IPC_CREAT | IPC_EXCL | PERMISSIONS)) == -1) ERROR;
    if ((semFissione    = semget(ftok(FTOK_FILE, 'f'), 10, IPC_CREAT | IPC_EXCL | PERMISSIONS)) == -1) ERROR;
    if ((semAttivatore  = semget(ftok(FTOK_FILE, 'g'), 10, IPC_CREAT | IPC_EXCL | PERMISSIONS)) == -1) ERROR;
    if ((semCentrale    = semget(ftok(FTOK_FILE, 'h'), 10, IPC_CREAT | IPC_EXCL | PERMISSIONS)) == -1) ERROR;
    if ((shmCentrale    = shmget(ftok(FTOK_FILE, 'l'), 10, IPC_CREAT | IPC_EXCL | PERMISSIONS)) == -1) ERROR;
    if ((centrale       = shmat(shmCentrale,NULL,0))                                            == -1) ERROR;

    centrale->energia = var->ENERGY_DEMAND;
    centrale->n_atomi = 0;
    centrale->scorie  = 0;

    out_progetto = fopen("Progetto.out", "a");
    setbuf(out_progetto, NULL);
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
    if ((shmAtomi       = shmget(ftok(FTOK_FILE, 'b'), sizeof(Atomo) * (var->N_ATOM_MAX + 1), PERMISSIONS)) == -1) ERROR;
    if ((semShm         = semget(ftok(FTOK_FILE, 'c'), 10,                                    PERMISSIONS)) == -1) ERROR;
    if ((semProcessi    = semget(ftok(FTOK_FILE, 'd'), 10,                                    PERMISSIONS)) == -1) ERROR;
    if ((msgPila        = msgget(ftok(FTOK_FILE, 'e'),                                        PERMISSIONS)) == -1) ERROR;
    if ((semFissione    = semget(ftok(FTOK_FILE, 'f'), 10,                                    PERMISSIONS)) == -1) ERROR;
    if ((semAttivatore  = semget(ftok(FTOK_FILE, 'g'), 10,                                    PERMISSIONS)) == -1) ERROR;
    if ((semCentrale    = semget(ftok(FTOK_FILE, 'h'), 10,                                    PERMISSIONS)) == -1) ERROR;
    if ((shmCentrale    = shmget(ftok(FTOK_FILE, 'l'), 10,                                    PERMISSIONS)) == -1) ERROR;

    out_progetto = fopen("Progetto.out", "a");
    setbuf(out_progetto, NULL);

    return;
}

void dettShm() {
    //if((shmdt(var)) == -1)    ERROR;
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
        atomi[centrale->n_atomi].numero_atomico = (rand() % var->N_ATOM_MAX) + 1;
        //pila[i]         = i;
        centrale->n_atomi++;
        
    }
    printf("\n(funzione creazione atomi)Il valore di var->n_atomi è %d ", centrale->n_atomi);
    //pila[var->n_atomi] = var->n_atomi;

   

    // if ((shmdt(pila)) == -1)
    //     ERROR;
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