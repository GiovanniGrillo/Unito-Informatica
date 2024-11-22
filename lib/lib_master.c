#include "lib_header.h"

union semun {
    int val;
    struct semid_ds *buf;
    short *array;
    struct seminfo *__buf;
    void *__pad;
};

char* get_config_file() {
    static char config_file[20];
    int valid_choice = 0;
    int choice;
    
    while (!valid_choice) {
        printf("**Select the configuration state:**\n");
        printf("1. timeout\n");
        printf("2. meltdown\n");
        printf("3. explode\n");
        printf("4. blackout\n");
        printf("**Enter your choice (1-4):** ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                strcpy(config_file, "conf/timeout.conf");
                valid_choice = 1;
                break;
            case 2:
                strcpy(config_file, "conf/meltdown.conf");
                valid_choice = 1;
                break;
            case 3:
                strcpy(config_file, "conf/explode.conf");
                valid_choice = 1;
                break;
            case 4:
                strcpy(config_file, "conf/blackout.conf");
                valid_choice = 1;
                break;
            default:
                printf("Scelta non valida. Riprova.\n");
                break;
        }
    }
    return config_file;
}

void createIPCS(char* file) {
    char temp[1000]; char boolean[6];

    sim_Input  = fopen(file, "r");
    sim_Output = fopen("sim.out", "w");
    setbuf(sim_Output, NULL);

    if ((shm_vars = shmget(ftok(FTOK_FILE, 'a'), sizeof(Var)*sizeof(int)*100, IPC_CREAT | IPC_EXCL | PERMISSIONS)) == -1) ERROR;
    if ((vars     = shmat(shm_vars, NULL, 0)) == (void*) -1)                                             ERROR;

    fprintf(sim_Output, "Starting execution of Operating Systems project\n");
    fprintf(sim_Output, "\nPower plant configuration:\n");


                                                                             fprintf(sim_Output, "%s %14d\n","SIM_DURATION:",       SIM_DURATION);
    fscanf(sim_Input, "%s %d\n", temp, &vars->ENERGY_DEMAND);                fprintf(sim_Output, "ENERGY_DEMAND: %14d\n",           vars->ENERGY_DEMAND);
    fscanf(sim_Input, "%s %d\n", temp, &vars->ENERGY_EXPLODE_THRESHOLD);     fprintf(sim_Output, "ENERGY_EXPLODE_THRESHOLD: %3d\n", vars->ENERGY_EXPLODE_THRESHOLD);
    fscanf(sim_Input, "%s %d\n", temp, &vars->N_ATOMI_INIT);                 fprintf(sim_Output, "N_ATOMI_INIT: %16d\n",            vars->N_ATOMI_INIT);
    fscanf(sim_Input, "%s %d\n", temp, &vars->N_ATOM_MAX);                   fprintf(sim_Output, "N_ATOM_MAX: %16d\n",              vars->N_ATOM_MAX);
    fscanf(sim_Input, "%s %d\n", temp, &vars->N_MSG);                        fprintf(sim_Output, "N_MSG: %22d\n",                   vars->N_MSG);
    fscanf(sim_Input, "%s %d\n", temp, &vars->N_NUOVI_ATOMI);                fprintf(sim_Output, "N_NUOVI_ATOMI: %14d\n",           vars->N_NUOVI_ATOMI);
    fscanf(sim_Input, "%s %d\n", temp, &vars->STEP_ALIMENTAZIONE);
    vars->STEP_ALIMENTAZIONE = convert_to_million(vars->STEP_ALIMENTAZIONE); fprintf(sim_Output, "STEP_ALIMENTAZIONE: %15d\n",      vars->STEP_ALIMENTAZIONE);
    fscanf(sim_Input, "%s %d\n", temp, &vars->STEP_ATTIVATORE);
    vars->STEP_ATTIVATORE    = convert_to_million(vars->STEP_ATTIVATORE);    fprintf(sim_Output, "STEP_ATTIVATORE: %18d\n",         vars->STEP_ATTIVATORE);
    fscanf(sim_Input, "\n");                                                 fprintf(sim_Output, "\n");
    vars->i =0;
    if ((msg_stack       = msgget(ftok(FTOK_FILE, 'b'),                                               IPC_CREAT | IPC_EXCL | PERMISSIONS)) == -1) ERROR;
    if ((inhibitor_stack = msgget(ftok(FTOK_FILE, 'c'),                                               IPC_CREAT | IPC_EXCL | PERMISSIONS)) == -1) ERROR;

    if ((sem_inhibitor   = semget(ftok(FTOK_FILE, 'd'), 1,                                            IPC_CREAT | IPC_EXCL | PERMISSIONS)) == -1) ERROR;
    if ((sem_power_plant = semget(ftok(FTOK_FILE, 'e'), 1,                                            IPC_CREAT | IPC_EXCL | PERMISSIONS)) == -1) ERROR;
    if ((sem_atom        = semget(ftok(FTOK_FILE, 'f'), 1,                                            IPC_CREAT | IPC_EXCL | PERMISSIONS)) == -1) ERROR;
    if ((sem_processes   = semget(ftok(FTOK_FILE, 'g'), 1,                                            IPC_CREAT | IPC_EXCL | PERMISSIONS)) == -1) ERROR;
    if ((sem_fission     = semget(ftok(FTOK_FILE, 'z'), 1,                                            IPC_CREAT | IPC_EXCL | PERMISSIONS)) == -1) ERROR;
    if ((sem_prova       = semget(ftok(FTOK_FILE, 'y'), 1,                                            IPC_CREAT | IPC_EXCL | PERMISSIONS)) == -1) ERROR;


    if ((shm_atoms       = shmget(ftok(FTOK_FILE, 'h'), sizeof(Atom) * (vars->N_MSG)*(SIM_DURATION)*20*(vars->N_NUOVI_ATOMI), IPC_CREAT | IPC_EXCL | PERMISSIONS)) == -1) ERROR;
    if ((shm_inhibitor   = shmget(ftok(FTOK_FILE, 'i'), sizeof(Inhibitor)*(sizeof(int)*10),                                   IPC_CREAT | IPC_EXCL | PERMISSIONS)) == -1) ERROR;
    if ((shm_power_plant = shmget(ftok(FTOK_FILE, 'j'), sizeof(PowerPlant)*(sizeof(int)*10),                                  IPC_CREAT | IPC_EXCL | PERMISSIONS)) == -1) ERROR;

    if ((inhibitor       = shmat(shm_inhibitor, NULL, 0)) == (void*) -1) ERROR;
    if ((power_plant     = shmat(shm_power_plant,NULL,0)) == (void*) -1) ERROR;

    if (fscanf(sim_Input, "%s %s", temp, boolean) != 2) {ERROR;fclose(sim_Input);return;}

    inhibitor->absorbed_energy = 0;
    inhibitor->denied_fission  = 0;
    inhibitor->done_fission    = 0;
    inhibitor->inhibitor_setup = (strcmp(boolean, "true") == 0);    fprintf(sim_Output, "inhibitor_setup= %s\n", inhibitor->inhibitor_setup ? "true" : "false");

    power_plant->energy        = vars->ENERGY_DEMAND;
    power_plant->atom_count    = 0;
    power_plant->waste_atoms   = 0;

    if((shmdt(inhibitor))   == -1) ERROR;
    if((shmdt(power_plant)) == -1) ERROR;

    fclose(sim_Input);
    fclose(sim_Output);
    sim_Output = fopen("sim.out", "a");
    setbuf(sim_Output, NULL);
    return;
}

void deallocIPC(){
    if (shmctl(shm_vars,        IPC_RMID, 0) == -1)  ERROR;
    if (shmctl(shm_atoms,       IPC_RMID, 0) == -1)  ERROR;
    if (shmctl(shm_power_plant, IPC_RMID, 0) == -1)  ERROR;
    if (shmctl(shm_inhibitor,   IPC_RMID, 0) == -1)  ERROR;

    if (msgctl(msg_stack,       IPC_RMID, 0) == -1)  ERROR;
    if (msgctl(inhibitor_stack, IPC_RMID, 0) == -1)  ERROR;

    if (semctl(sem_atom,        IPC_RMID, 0) == -1)  ERROR;
    if (semctl(sem_inhibitor,   IPC_RMID, 0) == -1)  ERROR;
    if (semctl(sem_power_plant, IPC_RMID, 0) == -1)  ERROR;
    if (semctl(sem_processes,   IPC_RMID, 0) == -1)  ERROR;
    if (semctl(sem_fission,     IPC_RMID, 0) == -1)  ERROR;
    if (semctl(sem_prova,       IPC_RMID, 0) == -1)  ERROR;

    printf("\nAll IPC resources have been successfully deallocated.\n");
    return;
}

int set_sem(int sem_id, int sem_num, int val) {
    union semun arg;
    arg.val = val;
    return semctl(sem_id, sem_num, SETVAL, arg);
}

void daily_log() {
    int prev_n_atoms = 0, prev_energy = 0, prev_waste = 0, prev_absorbed_energy = 0, prev_denied_fissions = 0;

    for (int day = 1; day <= SIM_DURATION; day++) {
        sim_overview(day);
        reserveSem(sem_power_plant, 0);
        fprintf(sim_Output, "\n\n*********************\n");
        fprintf(sim_Output, "*      DAY %2d       *\n", day);
        fprintf(sim_Output, "*********************\n");

        fprintf(sim_Output, "*\n");
        fprintf(sim_Output, "*Number of atoms: %d\n", power_plant->atom_count);
        fprintf(sim_Output, "*Number of new atoms: %d\n", power_plant->atom_count - prev_n_atoms);

        fprintf(sim_Output, "*Energy produced: %d\n", power_plant->energy);
        fprintf(sim_Output, "*New energy produced: %d\n", power_plant->energy - prev_energy);

        fprintf(sim_Output, "*Number of waste atoms: %d\n", power_plant->waste_atoms);
        fprintf(sim_Output, "*Number of new waste atoms: %d\n", power_plant->waste_atoms - prev_waste);
        releaseSem(sem_power_plant, 0);


        reserveSem(sem_inhibitor, 0);
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
        reserveSem(sem_power_plant, 0);
        fprintf(sim_Output, "*Fetching energy for the power plant\n");
        if (vars->ENERGY_DEMAND > power_plant->energy) {
            if (inhibitor->inhibitor_setup == true && vars->ENERGY_DEMAND <= inhibitor->absorbed_energy) {
                    inhibitor->absorbed_energy -= vars->ENERGY_DEMAND;
                    fprintf(sim_Output, "\n*** THE INHIBITOR PREVENTED THE POWER PLANT FROM GOING INTO BLACKOUT ***\n");
            }
            else {
                fprintf(sim_Output, "\n*** POWER PLANT BLACKOUT ***\n");
                printf("\n*** POWER PLANT BLACKOUT ***\n");
                releaseSem(sem_inhibitor, 0);
                releaseSem(sem_power_plant, 0);
                terminate();
            }
        } else
            power_plant->energy = power_plant->energy - vars->ENERGY_DEMAND; //prelievo giornaliero dell'energy

        prev_denied_fissions = inhibitor->denied_fission;
        prev_absorbed_energy = inhibitor->absorbed_energy;
        prev_n_atoms         = power_plant->atom_count;
        prev_energy          = power_plant->energy;
        prev_waste           = power_plant->waste_atoms;
        releaseSem(sem_inhibitor, 0);
        releaseSem(sem_power_plant, 0);

        if (day == SIM_DURATION)
            terminate();
        sleep(1);
    }
    fprintf(sim_Output,"Made by: Grillo Giovanni, Olivero Alessandro, Corrao Mario");
    return;
}

void sim_overview(int day) {
    reserveSem(sem_power_plant, 0);
    reserveSem(sem_inhibitor, 0);
    printf("\n\033[1mREPORT DAY %d:\033[0m", day);
    printf("\t\t[ Inib: %s ]\n", inhibitor->inhibitor_setup ? "\033[1;32mTRUE\033[0m" : "\033[1;31mFALSE\033[0m");
    printf("Atom count: %d\n", power_plant->atom_count);
    printf("Fissions completed: %d\n", inhibitor->done_fission);
    printf("Power plant energy: %d\n", power_plant->energy);

    if (inhibitor->inhibitor_setup == true) {
        printf("Fissions denied by inhibitor: %d\n", inhibitor->denied_fission);
        printf("Energy absorbed by inhibitor: %d\n", inhibitor->absorbed_energy);

    }
    releaseSem(sem_inhibitor, 0);
    releaseSem(sem_power_plant, 0);
}

void explode_handler(){ //SIGUSR1
    struct sigaction sa;
    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sigaddset(&sa.sa_mask, SIGTERM);
    sa.sa_flags = 0;

    if (sigaction(SIGUSR1, &sa, NULL) == -1)
        exit(1);

    fprintf(sim_Output, "\nPOWER PLANT EXPLODED!!");
    printf("\nPOWER PLANT EXPLODED!!");
    terminate();
}

void meltdown_handler() { // SIGUSR2
    struct sigaction sa;
    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sigaddset(&sa.sa_mask, SIGTERM);
    sa.sa_flags = 0;

    if (sigaction(SIGUSR2, &sa, NULL) == -1)
        exit(1);
    if(!inhibitor->inhibitor_setup){
        fprintf(sim_Output, "\nMELTDOWN!!");
        printf("\nMELTDOWN!!");
        terminate();
    } else{
        signal(SIGCHLD, SIG_IGN);
        reserveSem(sem_power_plant, 0);
        reserveSem(sem_atom, 0);
        for(int i = 0; i < (power_plant->atom_count * 0.5); ++i){
            if(kill(atoms[i].Atom_pid, SIGTERM) == 0){
                if(errno == ESRCH)
                    continue;
                else
                    ERROR;
            }
        }
        releaseSem(sem_atom, 0);
        releaseSem(sem_power_plant, 0);
        signal(SIGCHLD, SIG_DFL);
        setup_signal_handler(meltdown_handler, SIGUSR2);
    }
    
}

void terminate(){
    if(killpg(getpgrp(), SIGTERM) == -1) ERROR;
    return;
}

void exit_handler(){
    pid_t child_pid;
    while ((child_pid = waitpid(-1, NULL, 0)) > 0);
    if ((shmdt(atoms))       == -1) ERROR;
    if ((shmdt(power_plant)) == -1) ERROR;
    if ((shmdt(inhibitor))   == -1) ERROR;
    unloadIPCs();
    deallocIPC();
    printf("STO TERMINANDO, SONO IL MASTER\n");
    exit(0);
}