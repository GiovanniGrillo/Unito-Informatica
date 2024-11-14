#include "lib_header.h"

int count_active_processes() {
    int count = 0;
    struct dirent *entry;
    DIR *proc_dir = opendir("/proc");

    if (proc_dir == NULL) {
        perror("Errore nell'aprire /proc");
        exit(EXIT_FAILURE);
    }

    while ((entry = readdir(proc_dir)) != NULL) {
        // Controlla se il nome della directory è un numero (PID di un processo)
        if (isdigit(entry->d_name[0])) {
            count++;
        }
    }

    closedir(proc_dir);
    return count;
}

long int convert_to_million(int n){
    return n * 100000000;
}

void loadIPCs(){
    if ((shm_vars = shmget(ftok(FTOK_FILE, 'a'), sizeof(Var), PERMISSIONS)) == -1) ERROR;
    if ((vars     = shmat(shm_vars, NULL, 0)) == (void *)-1)                       ERROR;

    if ((msg_stack       = msgget(ftok(FTOK_FILE, 'b'),                                        PERMISSIONS)) == -1) ERROR;
    if ((inhibitor_stack = msgget(ftok(FTOK_FILE, 'c'),                                        PERMISSIONS)) == -1) ERROR;


    if ((sem_inhibitor   = semget(ftok(FTOK_FILE, 'd'), 1,                                     PERMISSIONS)) == -1) ERROR;
    if ((sem_power_plant = semget(ftok(FTOK_FILE, 'e'), 1,                                     PERMISSIONS)) == -1) ERROR;
    if ((sem_atom        = semget(ftok(FTOK_FILE, 'f'), 1,                                     PERMISSIONS)) == -1) ERROR;
    if ((sem_processes   = semget(ftok(FTOK_FILE, 'g'), 1,                                     PERMISSIONS)) == -1) ERROR;

    if ((shm_atoms       = shmget(ftok(FTOK_FILE, 'h'), sizeof(Atom) * (vars->N_MSG)*(SIM_DURATION)*5*(vars->N_NUOVI_ATOMI), PERMISSIONS)) == -1) ERROR;
    if ((shm_inhibitor   = shmget(ftok(FTOK_FILE, 'i'), sizeof(Inhibitor)*(sizeof(int)*10),    PERMISSIONS)) == -1) ERROR;
    if ((shm_power_plant = shmget(ftok(FTOK_FILE, 'j'), sizeof(PowerPlant)*(sizeof(int)*10),   PERMISSIONS)) == -1) ERROR;
    return;
}

void unloadIPCs(){
    if ((shmdt(vars)) == -1)
        ERROR;
    return;
}

int reserveSem(int id_sem, int n_sem){
    struct sembuf s_ops;
    s_ops.sem_num = n_sem;
    s_ops.sem_op = -1;
    s_ops.sem_flg = 0;
    return semop(id_sem, &s_ops, 1);
}

int releaseSem(int id_sem, int n_sem){
    struct sembuf s_ops;
    s_ops.sem_num = n_sem;
    s_ops.sem_op = 1;
    s_ops.sem_flg = 0;
    return semop(id_sem, &s_ops, 1);
}

void create_atoms(int n_atoms) {
    pid_t pid;
    reserveSem(sem_atom, 0);
    reserveSem(sem_power_plant, 0);

    for (int i = 0; i < n_atoms; i++){
        atoms[power_plant->atom_count].atomic_number = (rand() % vars->N_ATOM_MAX) + 1;
        switch (pid = fork()){
        case -1:
            releaseSem(sem_atom, 0);
            releaseSem(sem_power_plant, 0);
            if(kill(vars->master_pid, SIGUSR2) == -1) ERROR;
            break;
        case 0:
            execl("./atomo", "./atomo", NULL);
            exit(1);
            break;
        default:
            reserveSem(sem_processes,0);
            atoms[power_plant->atom_count].Atom_pid = pid;
            ++power_plant->atom_count;
            break;
        }
    }
    releaseSem(sem_power_plant, 0);
    releaseSem(sem_atom, 0);
}

void setup_signal_handler(void (*handler)(int), int signum){
    struct sigaction sa;

    memset(&sa, 0, sizeof(sa));

    sa.sa_handler = (handler == NULL ? SIG_IGN : handler);

    sigemptyset(&sa.sa_mask);
    sigaddset(&sa.sa_mask, SIGTERM);
    sa.sa_flags = 0;

    if (sigaction(signum, &sa, NULL) == -1)
        ERROR;
}