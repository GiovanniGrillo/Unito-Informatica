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

long int converti_in_milioni(int n) {
    return n * 100000000;
}

void createIPCS(char* file) { 
    char temp[99999];

    in_progetto  = fopen(file, "r");
    out_progetto=  fopen("Progetto.out", "w");
    setbuf(out_progetto, NULL);

    if ((shmVar  = shmget(ftok(FTOK_FILE, 'a'), sizeof(Var), IPC_CREAT | IPC_EXCL | PERMISSIONS)) == -1) ERROR;
    if ((var     = shmat(shmVar, NULL, 0)) == (void *) -1)                                               ERROR;
        
    fprintf(out_progetto, "╔═════════════════════════════════════════════════════════════╗\n");
    fprintf(out_progetto, "║ Inizio esecuzione progetto di Sistemi Operativi (2023/2024) ║\n");
    fprintf(out_progetto, "║                                di                           ║\n");
    fprintf(out_progetto, "║ GRILLO GIOVANNI , OLIVERO ALESSANDRO , SIVIERO FRANCESCO    ║\n");
    fprintf(out_progetto, "╠═════════════════════════════════════════════════════════════╝\n");
                                                                                    fprintf(out_progetto, "║%s %14d\n","SIM_DURATION:", SIM_DURATION);
    fscanf(in_progetto, "%s %d\n", temp, &var->ENERGY_DEMAND);                  fprintf(out_progetto, "║ENERGY_DEMAND: %14d\n", var->ENERGY_DEMAND);
    fscanf(in_progetto, "%s %d\n", temp, &var->ENERGY_EXPLODE_THRESHOLD);       fprintf(out_progetto, "║ENERGY_EXPLODE_THRESHOLD: %3d\n", var->ENERGY_EXPLODE_THRESHOLD);
    fscanf(in_progetto, "%s %d\n", temp, &var->flagTerminazione);               fprintf(out_progetto, "║flagTerminazione: %9d\n", var->flagTerminazione);
    fscanf(in_progetto, "%s %d\n", temp, &var->fork_atomi);                     fprintf(out_progetto, "║fork_atomi: %15d\n", var->fork_atomi);
    fscanf(in_progetto, "%s %d\n", temp, &var->MIN_N_ATOMICO);                  fprintf(out_progetto, "║MIN_N_ATOMICO: %12d\n", var->MIN_N_ATOMICO);
    fscanf(in_progetto, "%s %d\n", temp, &var->N_ATOMI_INIT);                   fprintf(out_progetto, "║N_ATOMI_INIT: %15d\n", var->N_ATOMI_INIT);
    fscanf(in_progetto, "%s %d\n", temp, &var->N_ATOM_MAX);                     fprintf(out_progetto, "║N_ATOM_MAX: %16d\n", var->N_ATOM_MAX);
    fscanf(in_progetto, "%s %d\n", temp, &var->N_MSG);                          fprintf(out_progetto, "║N_MSG: %22d\n", var->N_MSG);
    fscanf(in_progetto, "%s %d\n", temp, &var->N_NUOVI_ATOMI);                  fprintf(out_progetto, "║N_NUOVI_ATOMI: %14d\n", var->N_NUOVI_ATOMI);
    fscanf(in_progetto, "%s %d\n", temp, &var->STEP_ALIMENTAZIONE);
    var->STEP_ALIMENTAZIONE = converti_in_milioni(var->STEP_ALIMENTAZIONE);  fprintf(out_progetto, "║STEP_ALIMENTAZIONE: %15d\n", var->STEP_ALIMENTAZIONE);
    fscanf(in_progetto, "%s %d\n", temp, &var->STEP_ATTIVATORE);
    var->STEP_ATTIVATORE = converti_in_milioni(var->STEP_ATTIVATORE);        fprintf(out_progetto, "║STEP_ATTIVATORE: %18d\n", var->STEP_ATTIVATORE);
    printf("\nil vero valore di energy demand %d", var->ENERGY_DEMAND);
    printf("\nil vero valore di energy demand %d", var->ENERGY_EXPLODE_THRESHOLD);
    printf("\nil vero valore di energy demand %d", var->flagTerminazione);
    printf("\nil vero valore di energy demand %d", var->fork_atomi);
    printf("\nil vero valore di energy demand %d", var->MIN_N_ATOMICO);
    printf("\nil vero valore di energy demand %d", var->N_ATOMI_INIT);
    printf("\nil vero valore di energy demand %d", var->N_ATOM_MAX);
    printf("\nil vero valore di energy demand %d", var->N_MSG);
    printf("\nil vero valore di energy demand %d", var->STEP_ALIMENTAZIONE);
    printf("\nil vero valore di energy demand %d", var->STEP_ATTIVATORE);

    fclose(in_progetto);
    fclose(out_progetto);


    if ((shmAtomi       = shmget(ftok(FTOK_FILE, 'b'), sizeof(Atomo) * (var->N_MSG)*(SIM_DURATION)*3*(var->N_NUOVI_ATOMI), IPC_CREAT | IPC_EXCL | PERMISSIONS)) == -1) ERROR;
    if ((semShm         = semget(ftok(FTOK_FILE, 'c'), 10,                                            IPC_CREAT | IPC_EXCL | PERMISSIONS)) == -1) ERROR;
    if ((semProcessi    = semget(ftok(FTOK_FILE, 'd'), 10,                                            IPC_CREAT | IPC_EXCL | PERMISSIONS)) == -1) ERROR;
    if ((msgPila        = msgget(ftok(FTOK_FILE, 'e'),                                                IPC_CREAT | IPC_EXCL | PERMISSIONS)) == -1) ERROR;
    if ((semFissione    = semget(ftok(FTOK_FILE, 'f'), 10,                                            IPC_CREAT | IPC_EXCL | PERMISSIONS)) == -1) ERROR;
    if ((semAttivatore  = semget(ftok(FTOK_FILE, 'g'), 10,                                            IPC_CREAT | IPC_EXCL | PERMISSIONS)) == -1) ERROR;
    if ((semCentrale    = semget(ftok(FTOK_FILE, 'h'), 10,                                            IPC_CREAT | IPC_EXCL | PERMISSIONS)) == -1) ERROR;
    if ((shmCentrale    = shmget(ftok(FTOK_FILE, 'l'), sizeof(Centrale)*(sizeof(int)*3),              IPC_CREAT | IPC_EXCL | PERMISSIONS)) == -1) ERROR;
    if ((centrale       = shmat(shmCentrale,NULL,0))                                                                                       == -1) ERROR;
    if ((shmInibitore    = shmget(ftok(FTOK_FILE, 'm'), sizeof(Inibitore),              IPC_CREAT | IPC_EXCL | PERMISSIONS)) == -1) ERROR;
    if ((inibitore = shmat(shmInibitore, NULL, 0)) == (void*) -1) ERROR;
    inibitore->active=1;
    inibitore->absorbed_energy=0;
    inibitore->scissioni_negate=0;
   

    centrale->energia = var->ENERGY_DEMAND;
    centrale->n_atomi = 0;
    centrale->scorie  = 0;

    if((shmdt(centrale)) == -1) ERROR;
    if((shmdt(inibitore)) == -1) ERROR;

    out_progetto = fopen("Progetto.out", "a");
    setbuf(out_progetto, NULL);
    return;
}

void attShm() {
    reserveSem (semShm,0);
    if ((inibitore = shmat(shmInibitore, NULL, 0)) == (void*) -1) ERROR;
    if ((centrale = shmat(shmCentrale, NULL, 0)) == (void*) -1) ERROR;
    if ((atomi    = shmat(shmAtomi,    NULL, 0)) == (void*) -1) ERROR;
    return;
}

void loadIPCs() {
    if ((shmVar         = shmget(ftok(FTOK_FILE, 'a'), sizeof(Var),                           PERMISSIONS)) == -1) ERROR;
    if ((var            = shmat (shmVar, NULL, 0)) == (void *) -1)                                                 ERROR;
    if ((shmAtomi       = shmget(ftok(FTOK_FILE, 'b'), sizeof(Atomo) * (var->N_MSG)*(SIM_DURATION)*3*(var->N_NUOVI_ATOMI), PERMISSIONS)) == -1) ERROR;
    if ((semShm         = semget(ftok(FTOK_FILE, 'c'), 10,                                    PERMISSIONS)) == -1) ERROR;
    if ((semProcessi    = semget(ftok(FTOK_FILE, 'd'), 10,                                    PERMISSIONS)) == -1) ERROR;
    if ((msgPila        = msgget(ftok(FTOK_FILE, 'e'),                                        PERMISSIONS)) == -1) ERROR;
    if ((semFissione    = semget(ftok(FTOK_FILE, 'f'), 10,                                    PERMISSIONS)) == -1) ERROR;
    if ((semAttivatore  = semget(ftok(FTOK_FILE, 'g'), 10,                                    PERMISSIONS)) == -1) ERROR;
    if ((semCentrale    = semget(ftok(FTOK_FILE, 'h'), 10,                                    PERMISSIONS)) == -1) ERROR;
    if ((shmCentrale    = shmget(ftok(FTOK_FILE, 'l'), sizeof(Centrale)*(sizeof(int)*3),      PERMISSIONS)) == -1) ERROR;
    if ((shmInibitore    = shmget(ftok(FTOK_FILE, 'm'), sizeof(Inibitore),                    PERMISSIONS)) == -1) ERROR;

    return;
}

void dettShm() {
    if((shmdt(atomi)) == -1)    ERROR;
    if((shmdt(centrale)) == -1) ERROR;
    if((shmdt(inibitore)) == -1) ERROR;
    releaseSem(semShm,0);
    return;
}

void deallocIPC(){
    if (shmctl(shmVar,       IPC_RMID, 0) == -1) { ERROR; }  else  printf("\n     shmVar      |   deallocati     \n");
    if (shmctl(shmAtomi,     IPC_RMID, 0) == -1) { ERROR; }  else  printf("     shmAtomi      |   deallocati     \n");
    if (shmctl(shmCentrale,  IPC_RMID, 0) == -1) { ERROR; }  else  printf("     shmCentrale   |   deallocata     \n");
    if (semctl(semShm,       IPC_RMID, 0) == -1) { ERROR; }  else  printf("     semShm        |   deallocati     \n");
    if (semctl(semProcessi,  IPC_RMID, 0) == -1) { ERROR; }  else  printf("     semProcessi   |   deallocati     \n");
    if (msgctl(msgPila,      IPC_RMID, 0) == -1) { ERROR; }  else  printf("     msgPila       |   deallocati     \n");
    if (semctl(semFissione,  IPC_RMID, 0) == -1) { ERROR; }  else  printf("     semFissione   |   deallocati     \n");
    if (semctl(semAttivatore,IPC_RMID, 0) == -1) { ERROR; }  else  printf("     semFissione   |   deallocati     \n");
    if (semctl(semCentrale,  IPC_RMID, 0) == -1) { ERROR; }  else  printf("     semFissione   |   deallocati     \n");
    if (shmctl(shmInibitore, IPC_RMID, 0) == -1) { ERROR; }  else  printf("    shmInibitore   |   deallocati     \n");
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
    int prev_n_atomi=0, prev_energia=0, prev_scorie=0, prev_energiaAssorbed=0, prev_scissioninegate=0;
    
    

    for(int giorno = 0; giorno < SIM_DURATION; ++giorno) {
        reserveSem(semAttivatore,0);
        reserveSem(semProcessi,  0);
       

        fprintf(out_progetto, "\n╔═════════════════════════════╗\n");
        fprintf(out_progetto,   "║          GIORNO %2d          ║\n", giorno + 1);
        fprintf(out_progetto,   "╠═════════════════════════════╝\n║\n");

        attShm(); {
            

            fprintf(out_progetto,"║ Numero atomi %d"    ,centrale->n_atomi);
            fprintf(out_progetto,"║ Numero nuovi atomi %d\n", centrale->n_atomi - prev_n_atomi);
        

            fprintf(out_progetto,"\n║ Energia prodotta %d",centrale->energia);
            fprintf(out_progetto,"\n║ Energia prodotta nuova %d\n", centrale->energia - prev_energia);
       

            fprintf(out_progetto,"\n║ Numero scorie %d"   ,centrale->scorie);
            fprintf(out_progetto,"\n║ Numero nuove scorie %d\n", centrale->scorie - prev_scorie);
            if(inibitore->active==1){
            fprintf(out_progetto,"\n║ Numero energia assorbita dall'inib %d"   ,inibitore->absorbed_energy);
            fprintf(out_progetto,"\n║ Numero energia assorbita dall'inib nuova %d"   ,inibitore->absorbed_energy-prev_energiaAssorbed);

            fprintf(out_progetto,"\n║ Numero scissioni negate dall'inib %d"   ,inibitore->scissioni_negate);
            fprintf(out_progetto,"\n║ Numero scissioni negate dall'inib %d"   ,inibitore->scissioni_negate-prev_scissioninegate);
            }else{
                fprintf(out_progetto,"\n║L'INIBITORE è SPENTO  Numero energia assorbita dall'inib fin ora  %d "   ,prev_energiaAssorbed);
                fprintf(out_progetto,"\n║L'INIBITORE è SPENTO Numero scissioni dall'inib fin ora %d   ",prev_scissioninegate);
            }

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
        prev_scissioninegate=inibitore->scissioni_negate;
        prev_energiaAssorbed=inibitore->absorbed_energy;
        prev_n_atomi = centrale->n_atomi;
        prev_energia = centrale->energia;
        prev_scorie  = centrale->scorie;
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


   void handle_sigint(int sig) 
                {               
    printf("\nRicevuto SIGINT! Passo il controllo all'inibitore.\n"); 
    kill(pidInibitore, SIGUSR1);  // Invia SIGUSR1 all'inibitore
                } 