#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include <time.h>
#include <math.h>
#include "resources.h"

#define PERMISSIONS  0666
#define FTOK_FILE    "attivatore.c"

#define ERROR                                                                                                                                     \
    {                                                                                                                                             \
        if (errno) {                                                                                                                              \
            fprintf(stderr, "ERROR - line %d: file \"%s\" (pid %d) - n %d - (%s)\n", __LINE__, __FILE__, getpid(), errno, strerror(errno));       \
            exit(1);                                                                                                                              \
        }                                                                                                                                         \
    }

long int convert_to_million(int n) {
    return n * 100000000;
}

void createIPCS(char* file) {
    char temp[1000]; char boolean[6];

    sim_Input  = fopen(file, "r");
    sim_Output = fopen("sim.out", "w");
    setbuf(sim_Output, NULL);

    if ((shm_vars = shmget(ftok(FTOK_FILE, 'a'), sizeof(Var), IPC_CREAT | IPC_EXCL | PERMISSIONS)) == -1) ERROR;
    if ((vars     = shmat(shm_vars, NULL, 0)) == (void*) -1)                                             ERROR;

    fprintf(sim_Output, "Starting execution of Operating Systems project\n");
    fprintf(sim_Output, "\nPower plant configuration:\n");


                                                                             fprintf(sim_Output, "%s %14d\n","SIM_DURATION:",       SIM_DURATION);
    fscanf(sim_Input, "%s %d\n", temp, &vars->ENERGY_DEMAND);                fprintf(sim_Output, "ENERGY_DEMAND: %14d\n",           vars->ENERGY_DEMAND);
    fscanf(sim_Input, "%s %d\n", temp, &vars->ENERGY_EXPLODE_THRESHOLD);     fprintf(sim_Output, "ENERGY_EXPLODE_THRESHOLD: %3d\n", vars->ENERGY_EXPLODE_THRESHOLD);
    fscanf(sim_Input, "%s %d\n", temp, &vars->exit_flag);                    fprintf(sim_Output, "exit_flag: %16d\n",               vars->exit_flag);
    fscanf(sim_Input, "%s %d\n", temp, &vars->atom_Fork);                    fprintf(sim_Output, "atomFork: %17d\n",                vars->atom_Fork);
    fscanf(sim_Input, "%s %d\n", temp, &vars->MIN_N_ATOMICO);                fprintf(sim_Output, "MIN_N_ATOMICO: %12d\n",           vars->MIN_N_ATOMICO);
    fscanf(sim_Input, "%s %d\n", temp, &vars->N_ATOMI_INIT);                 fprintf(sim_Output, "N_ATOMI_INIT: %16d\n",            vars->N_ATOMI_INIT);
    fscanf(sim_Input, "%s %d\n", temp, &vars->N_ATOM_MAX);                   fprintf(sim_Output, "N_ATOM_MAX: %16d\n",              vars->N_ATOM_MAX);
    fscanf(sim_Input, "%s %d\n", temp, &vars->N_MSG);                        fprintf(sim_Output, "N_MSG: %22d\n",                   vars->N_MSG);
    fscanf(sim_Input, "%s %d\n", temp, &vars->N_NUOVI_ATOMI);                fprintf(sim_Output, "N_NUOVI_ATOMI: %14d\n",           vars->N_NUOVI_ATOMI);
    fscanf(sim_Input, "%s %d\n", temp, &vars->STEP_ALIMENTAZIONE);
    vars->STEP_ALIMENTAZIONE = convert_to_million(vars->STEP_ALIMENTAZIONE); fprintf(sim_Output, "STEP_ALIMENTAZIONE: %15d\n",      vars->STEP_ALIMENTAZIONE);
    fscanf(sim_Input, "%s %d\n", temp, &vars->STEP_ATTIVATORE);
    vars->STEP_ATTIVATORE    = convert_to_million(vars->STEP_ATTIVATORE);    fprintf(sim_Output, "STEP_ATTIVATORE: %18d\n",         vars->STEP_ATTIVATORE);
    fscanf(sim_Input, "%s %d\n", temp, &vars->STEP_INHIBITOR);
    vars->STEP_INHIBITOR = convert_to_million(vars->STEP_INHIBITOR);         fprintf(sim_Output, "STEP_INHIBITOR: %19d\n",          vars->STEP_INHIBITOR);
    fscanf(sim_Input, "\n");                                                 fprintf(sim_Output, "\n");

    if ((shm_atoms       = shmget(ftok(FTOK_FILE, 'b'), sizeof(Atom) * (vars->N_MSG)*(SIM_DURATION)*5*(vars->N_NUOVI_ATOMI), IPC_CREAT | IPC_EXCL | PERMISSIONS)) == -1) ERROR;
    if ((sem_shm         = semget(ftok(FTOK_FILE, 'c'), 10,                                            IPC_CREAT | IPC_EXCL | PERMISSIONS)) == -1) ERROR;
    if ((sem_processes   = semget(ftok(FTOK_FILE, 'd'), 10,                                            IPC_CREAT | IPC_EXCL | PERMISSIONS)) == -1) ERROR;
    if ((sem_inhibitor   = semget(ftok(FTOK_FILE, 'i'), 10,                                            IPC_CREAT | IPC_EXCL | PERMISSIONS)) == -1) ERROR;
    if ((msg_stack       = msgget(ftok(FTOK_FILE, 'e'),                                                IPC_CREAT | IPC_EXCL | PERMISSIONS)) == -1) ERROR;
    if ((sem_fission     = semget(ftok(FTOK_FILE, 'f'), 10,                                            IPC_CREAT | IPC_EXCL | PERMISSIONS)) == -1) ERROR;
    if ((sem_activator   = semget(ftok(FTOK_FILE, 'g'), 10,                                            IPC_CREAT | IPC_EXCL | PERMISSIONS)) == -1) ERROR;
    if ((sem_power_plant = semget(ftok(FTOK_FILE, 'h'), 10,                                            IPC_CREAT | IPC_EXCL | PERMISSIONS)) == -1) ERROR;
    if ((shm_power_plant = shmget(ftok(FTOK_FILE, 'l'), sizeof(PowerPlant)*(sizeof(int)*10),            IPC_CREAT | IPC_EXCL | PERMISSIONS)) == -1) ERROR;
    if ((power_plant     = shmat(shm_power_plant,NULL,0)) == (void*) -1)                                                                           ERROR;
    if ((shm_inhibitor   = shmget(ftok(FTOK_FILE, 'm'), sizeof(Inhibitor)*(sizeof(int)*10),                             IPC_CREAT | IPC_EXCL | PERMISSIONS)) == -1) ERROR;
    if ((inhibitor       = shmat(shm_inhibitor, NULL, 0)) == (void*) -1)                                                                           ERROR;
    if (fscanf(sim_Input, "%s %s", temp, boolean) != 2) {ERROR;fclose(sim_Input);return;}

    inhibitor->inhibitor_setup = (strcmp(boolean, "true") == 0);    fprintf(sim_Output, "inhibitor_setup= %s\n", inhibitor->inhibitor_setup ? "true" : "false");
    inhibitor->absorbed_energy = 0;
    inhibitor->denied_fission  = 0;
    inhibitor->done_fission    = 0;

    power_plant->energy        = vars->ENERGY_DEMAND;
    power_plant->atom_count    = 0;
    power_plant->waste_atoms   = 0;

    if((shmdt(power_plant)) == -1) ERROR;
    if((shmdt(inhibitor))   == -1) ERROR;

    fclose(sim_Input);
    fclose(sim_Output);
    sim_Output = fopen("sim.out", "a");
    setbuf(sim_Output, NULL);
    return;
}


void loadIPCs() {
    if ((shm_vars        = shmget(ftok(FTOK_FILE, 'a'), sizeof(Var),                           PERMISSIONS)) == -1) ERROR;
    if ((vars            = shmat (shm_vars, NULL, 0)) == (void *) -1)                                               ERROR;
    if ((shm_atoms       = shmget(ftok(FTOK_FILE, 'b'), sizeof(Atom) * (vars->N_MSG)*(SIM_DURATION)*5*(vars->N_NUOVI_ATOMI), PERMISSIONS)) == -1) ERROR;
    if ((sem_shm         = semget(ftok(FTOK_FILE, 'c'), 10,                                    PERMISSIONS)) == -1) ERROR;
    if ((sem_processes   = semget(ftok(FTOK_FILE, 'd'), 10,                                    PERMISSIONS)) == -1) ERROR;
    if ((sem_inhibitor   = semget(ftok(FTOK_FILE, 'i'), 10,                                    PERMISSIONS)) == -1) ERROR;
    if ((msg_stack       = msgget(ftok(FTOK_FILE, 'e'),                                        PERMISSIONS)) == -1) ERROR;
    if ((sem_fission     = semget(ftok(FTOK_FILE, 'f'), 10,                                    PERMISSIONS)) == -1) ERROR;
    if ((sem_activator   = semget(ftok(FTOK_FILE, 'g'), 10,                                    PERMISSIONS)) == -1) ERROR;
    if ((sem_power_plant = semget(ftok(FTOK_FILE, 'h'), 10,                                    PERMISSIONS)) == -1) ERROR;
    if ((shm_power_plant = shmget(ftok(FTOK_FILE, 'l'), sizeof(PowerPlant)*(sizeof(int)*10),    PERMISSIONS)) == -1) ERROR;
    if ((shm_inhibitor   = shmget(ftok(FTOK_FILE, 'm'), sizeof(Inhibitor)*(sizeof(int)*10),                     PERMISSIONS)) == -1) ERROR;
    return;
}


void deallocIPC(){
    if (shmctl(shm_vars,       IPC_RMID, 0) == -1)    ERROR;
    if (shmctl(shm_atoms,     IPC_RMID, 0) == -1)     ERROR;
    if (shmctl(shm_power_plant,  IPC_RMID, 0) == -1)  ERROR;
    if (semctl(sem_shm,       IPC_RMID, 0) == -1)     ERROR;
    if (semctl(sem_processes,  IPC_RMID, 0) == -1)    ERROR;
    if (msgctl(msg_stack,      IPC_RMID, 0) == -1)    ERROR;
    if (semctl(sem_fission,  IPC_RMID, 0) == -1)      ERROR;
    if (semctl(sem_activator,IPC_RMID, 0) == -1)      ERROR;
    if (semctl(sem_inhibitor, IPC_RMID, 0) == -1)     ERROR;
    if (semctl(sem_power_plant,  IPC_RMID, 0) == -1)  ERROR;
    if (shmctl(shm_inhibitor, IPC_RMID, 0) == -1)     ERROR;
    printf("\n\nAll IPC resources have been successfully deallocated.\n");
    return;
}

void unloadIPCs() {
    if((shmdt(vars)) == -1) ERROR;
    return;
}

int reserveSem(int id_sem, int n_sem) {
    struct sembuf s_ops;
    s_ops.sem_num = n_sem;
    s_ops.sem_op  = -1;
    s_ops.sem_flg = 0;
    return semop(id_sem, &s_ops, 1);
}

int releaseSem(int id_sem, int n_sem) {
    struct sembuf s_ops;
    s_ops.sem_num = n_sem;
    s_ops.sem_op  = 1;
    s_ops.sem_flg = 0;
    return semop(id_sem, &s_ops, 1);
}

void attShm() {
    reserveSem (sem_shm,0);
    if ((atoms        = shmat(shm_atoms,       NULL, 0)) == (void*) -1) ERROR;
    if ((power_plant  = shmat(shm_power_plant, NULL, 0)) == (void*) -1) ERROR;
    if ((inhibitor    = shmat(shm_inhibitor,   NULL, 0)) == (void*) -1) ERROR;
    return;
}

void dettShm() {
    if((shmdt(atoms))       == -1) ERROR;
    if((shmdt(power_plant)) == -1) ERROR;
    if((shmdt(inhibitor))   == -1) ERROR;
    releaseSem(sem_shm,0);
    return;
}

union semun {
    int val;
    struct semid_ds *buf;
    short *array;
    struct seminfo *__buf;
    void *__pad;
};


int set_sem(int sem_id, int sem_num, int val) {
    union semun arg;
    arg.val = val;
    return semctl(sem_id, sem_num, SETVAL, arg);
}

pid_t newProcess() {
    reserveSem(sem_fission,0);
    return fork();
}

void endProcess() {
    exit(0);
}

int create_atoms(int number_atoms) {
    int i = 0;
    // printf("ehy power_plant n_atomi è uguale a %d", power_plant->atom_count);
    while (i < number_atoms) {
        atoms[power_plant->atom_count].atomic_number = (rand() % vars->N_ATOM_MAX) + 1;
        atoms[power_plant->atom_count].Atom_pid = (0);
        ++power_plant->atom_count;
        ++i;
    }
    return 0;
}

void handle_sigint(int sig) { }

void handle_sig_inhibitor(int sig) {
    attShm();
    if (inhibitor->inhibitor_setup == false) {
        inhibitor->inhibitor_setup = true;
    } else {
        inhibitor->inhibitor_setup = false;
    }
    printf("Inhibitor status: %d", inhibitor->inhibitor_setup);
    dettShm();
}

void sim_overview() {
    attShm();
    printf("Atom count: %d\n", power_plant->atom_count);
    printf("Fissions completed: %d\n", inhibitor->done_fission);
    printf("Power plant energy: %d\n", power_plant->energy);

    if (inhibitor->inhibitor_setup == true) {
        printf("\nFissions denied by inhibitor: %d\n", inhibitor->denied_fission);
        printf("Energy absorbed by inhibitor: %d\n", inhibitor->absorbed_energy);
    }
    dettShm();
}


void daily_Log() {
    int prev_n_atoms = 0, prev_energy = 0, prev_waste = 0, prev_absorbed_energy = 0, prev_denied_fissions = 0;

    for (int day = 0; day < SIM_DURATION; ++day) {
        reserveSem(sem_activator, 0);
        reserveSem(sem_processes, 0);
        reserveSem(sem_inhibitor, 0);

        fprintf(sim_Output, "\n\n*********************\n");
        fprintf(sim_Output, "*      DAY %2d       *\n", day + 1);
        fprintf(sim_Output, "*********************\n");


        attShm(); {
            fprintf(sim_Output, "*\n");
            fprintf(sim_Output, "*Number of atoms: %d\n", power_plant->atom_count);
            fprintf(sim_Output, "*Number of new atoms: %d\n", power_plant->atom_count - prev_n_atoms);

            fprintf(sim_Output, "*Energy produced: %d\n", power_plant->energy);
            fprintf(sim_Output, "*New energy produced: %d\n", power_plant->energy - prev_energy);

            fprintf(sim_Output, "*Number of waste atoms: %d\n", power_plant->waste_atoms);
            fprintf(sim_Output, "*Number of new waste atoms: %d\n", power_plant->waste_atoms - prev_waste);

            fprintf(sim_Output, "*Number of fissions performed by inhibitor: %d\n", inhibitor->done_fission);

            if (inhibitor->inhibitor_setup == true) {
            fprintf(sim_Output, "*Energy absorbed by inhibitor: %d\n", inhibitor->absorbed_energy);
            fprintf(sim_Output, "*New energy absorbed by inhibitor: %d\n", inhibitor->absorbed_energy - prev_absorbed_energy);

            fprintf(sim_Output, "*Number of fissions denied by inhibitor: %d\n", inhibitor->denied_fission);
            fprintf(sim_Output, "*New fissions denied by inhibitor: %d\n", inhibitor->denied_fission - prev_denied_fissions);
            } else {
                fprintf(sim_Output, "*INHIBITOR OFF - Energy absorbed by inhibitor so far: %d\n", prev_absorbed_energy);
                fprintf(sim_Output, "*INHIBITOR OFF - Fissions denied by inhibitor so far: %d\n", prev_denied_fissions);
            }

                fprintf(sim_Output, "*Fetching energy for the power plant\n");
            if ((power_plant->energy) - (vars->ENERGY_DEMAND) < 0) {
                if (inhibitor->inhibitor_setup == true) {
                    if (inhibitor->absorbed_energy - vars->ENERGY_DEMAND) {
                        vars->exit_flag = 1;
                        fprintf(sim_Output, "\n*** POWER PLANT BLACKOUT ***\n");
                        dettShm();
                        endProcess();
                    } else {
                        inhibitor->absorbed_energy -= vars->ENERGY_DEMAND;
                        fprintf(sim_Output, "\n*** THE INHIBITOR PREVENTED THE POWER PLANT FROM GOING INTO BLACKOUT ***\n");
                    }
                } else {
                    vars->exit_flag = 1;
                    fprintf(sim_Output, "\n*** POWER PLANT BLACKOUT ***\n");
                    dettShm();
                    endProcess();
                }
            }
            //prelievo giornaliero dell'energy
            power_plant->energy = power_plant->energy - vars->ENERGY_DEMAND;
        }
        prev_denied_fissions = inhibitor->denied_fission;
        prev_absorbed_energy = inhibitor->absorbed_energy;
        prev_n_atoms         = power_plant->atom_count;
        prev_energy          = power_plant->energy;
        prev_waste           = power_plant->waste_atoms;

        dettShm();
        if (day == SIM_DURATION - 1) {
            vars->exit_flag = 1;
        }
        releaseSem(sem_activator, 0);
        releaseSem(sem_processes, 0);
        releaseSem(sem_inhibitor, 0);

        sleep(1);
    }

    fprintf(sim_Output, "\nexit_flag:%d, Stop Simulation.\n", vars->exit_flag);
    fprintf(sim_Output,"Made by: Grillo Giovanni, Olivero Alessandro, Corrao Mario");
    return;
}