#include "lib/lib_header.c"
#include "lib/lib_master.c"

int main() {
    setbuf(stdout, NULL);
    srand(time(NULL));

    setup_signal_handler(NULL, SIGQUIT);
    setup_signal_handler(exit_handler, SIGTERM);
    setup_signal_handler(exit_handler, SIGINT);

    setup_signal_handler(explode_handler, SIGUSR1);
    setup_signal_handler(meltdown_handler, SIGUSR2);

    char *config_file = get_config_file();
    createIPCS(config_file);

    vars->master_pid = getpid();

    if (set_sem(sem_inhibitor,     0, 1) == -1) ERROR;
    if (set_sem(sem_atom,          0, 1) == -1) ERROR;
    if (set_sem(sem_power_plant,   0, 1) == -1) ERROR;
    if (set_sem(sem_processes,     0, 1) == -1) ERROR;
    if (set_sem(sem_fission,       0, 1) == -1) ERROR;
    if (set_sem(sem_removal,       0, 1) == -1) ERROR;

    if ((power_plant = shmat(shm_power_plant, NULL,0)) == (void*) -1) ERROR;
    if ((atoms       = shmat(shm_atoms,       NULL,0)) == (void*) -1) ERROR;
    if ((inhibitor   = shmat(shm_inhibitor,   NULL,0)) == (void*) -1) ERROR;

    pid_t temp_pid = 0;

    printf("attivatore.c    -run\n");
    switch (temp_pid = fork()) {
        case -1:
            if(kill(vars->master_pid, SIGUSR2) == -1) ERROR;
        case 0:
            execl("bin/attivatore", "bin/attivatore", NULL);
            printf("activator not started correctly\n");
            ERROR;
            break;
        default:
            vars->Activator_pid = temp_pid;
            reserveSem(sem_processes,0);
            break;
    }

    printf("alimentatore.c  -run\n");
    switch (temp_pid = fork()) {
        case -1:
            if(kill(vars->master_pid, SIGUSR2) == -1) ERROR;
            break;
        case 0:
            execl("bin/alimentatore", "bin/alimentatore", NULL);
            printf("power supply not started correctly\n");
            ERROR;
            break;
        default:
            vars->Powersupply_pid = temp_pid;
            reserveSem(sem_processes,0);
            break;
    }

    printf("inibitore.c     -run\n");
    switch ((temp_pid = fork())) {
        case -1:
            if(kill(vars->master_pid, SIGUSR2) == -1) ERROR;
            break;
        case 0:
            execl("bin/inibitore", "bin/inibitore", NULL);
            printf("Inhibitor not started correctly\n");
            ERROR;
            break;
        default:
            inhibitor->Inhibitor_pid = temp_pid;
            reserveSem(sem_processes,0);
            break;
    }

    create_atoms(vars->N_ATOMI_INIT);

    daily_log();
    printf("\n\t\t\033[1mEND\033[0m\n");
    terminate();
}