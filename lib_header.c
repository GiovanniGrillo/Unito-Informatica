#include "lib_header.h"
#include "resources.h"

long int convert_to_million(int n) {
    return n * 100000000;
}

void loadIPCs() {
    if ((shm_vars        = shmget(ftok(FTOK_FILE, 'a'), sizeof(Var),                           PERMISSIONS)) == -1) ERROR;
    if ((vars            = shmat (shm_vars, NULL, 0)) == (void *) -1)                                               ERROR;
    
    if ((shm_atoms       = shmget(ftok(FTOK_FILE, 'b'), sizeof(Atom) * (vars->N_MSG)*(SIM_DURATION)*5*(vars->N_NUOVI_ATOMI), PERMISSIONS)) == -1) ERROR;
    if ((sem_inhibitor   = semget(ftok(FTOK_FILE, 'i'), 1,                                     PERMISSIONS)) == -1) ERROR;
    if ((sem_atom        = semget(ftok(FTOK_FILE, 'd'), 1,                                     PERMISSIONS)) == -1) ERROR;
    if ((sem_var         = semget(ftok(FTOK_FILE, 'z'), 1,                                     PERMISSIONS)) == -1) ERROR;


    if ((msg_stack       = msgget(ftok(FTOK_FILE, 'e'),                                        PERMISSIONS)) == -1) ERROR;
    if ((sem_power_plant = semget(ftok(FTOK_FILE, 'h'), 1,                                     PERMISSIONS)) == -1) ERROR;
    if ((shm_power_plant = shmget(ftok(FTOK_FILE, 'l'), sizeof(PowerPlant)*(sizeof(int)*10),   PERMISSIONS)) == -1) ERROR;
    if ((shm_inhibitor   = shmget(ftok(FTOK_FILE, 'm'), sizeof(Inhibitor)*(sizeof(int)*10),    PERMISSIONS)) == -1) ERROR;
    return;
}

void deallocIPC(){
    if (shmctl(shm_vars,        IPC_RMID, 0) == -1)  ERROR;
    if (shmctl(shm_atoms,       IPC_RMID, 0) == -1)  ERROR;
    if (shmctl(shm_power_plant, IPC_RMID, 0) == -1)  ERROR;
    if (shmctl(shm_inhibitor,   IPC_RMID, 0) == -1)  ERROR;

    if (msgctl(msg_stack,       IPC_RMID, 0) == -1)  ERROR;

    if (semctl(sem_atom,        IPC_RMID, 0) == -1)  ERROR;
    if (semctl(sem_inhibitor,   IPC_RMID, 0) == -1)  ERROR;
    if (semctl(sem_power_plant, IPC_RMID, 0) == -1)  ERROR;
    if (semctl(sem_var,         IPC_RMID, 0) == -1)  ERROR;

    printf("\nAll IPC resources have been successfully deallocated.\n");
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
    if ((atoms        = shmat(shm_atoms,       NULL, 0)) == (void*) -1) ERROR;
    if ((power_plant  = shmat(shm_power_plant, NULL, 0)) == (void*) -1) ERROR;
    if ((inhibitor    = shmat(shm_inhibitor,   NULL, 0)) == (void*) -1) ERROR;
    return;
}


 void dettShm() {
     if ((shmdt(atoms))       == -1) ERROR;
     if ((shmdt(power_plant)) == -1) ERROR;
     if ((shmdt(inhibitor))   == -1) ERROR;
     return;
 }

void unloadIPCs() {
    if((shmdt(vars)) == -1) ERROR;
    return;
}
void handle_sig_inhibitor() {
    reserveSem(sem_inhibitor, 0);
    attShm();
    if (inhibitor->inhibitor_setup == false) {
        inhibitor->inhibitor_setup = true;
        printf("inhibitor_setup= %s\n", inhibitor->inhibitor_setup ? "true" : "false");
    } else {
        inhibitor->inhibitor_setup = false;
    }
    dettShm();
    releaseSem(sem_inhibitor, 0);
}

void setup_signal_handler(void (*handler)(int)) {
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));

    sa.sa_handler = (handler == NULL ? SIG_IGN : handler);

    sigemptyset(&sa.sa_mask);
    sigaddset(&sa.sa_mask, SIGTERM);
    sa.sa_flags = 0;

    if (sigaction(SIGINT, &sa, NULL) == -1) ERROR;
}