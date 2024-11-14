#include "lib/lib_header.c"
#include "lib/lib_master.c"

int main() {
    setbuf(stdout, NULL);
    srand(time(NULL));
    setup_signal_handler(NULL, SIGINT); //SIGINT
    setup_signal_handler(exit_handler, SIGTERM); //SIGTERM
    setup_signal_handler(explode_handler, SIGUSR2); //SIGUSR2
    //char *config_file = get_config_file(); //passa in char uno dei 4 file .conf
    createIPCS("conf/sim.conf");

    vars->master_pid = getpid();

    if (set_sem(sem_inhibitor,   0, 1) == -1) ERROR;
    if (set_sem(sem_atom,        0, 1) == -1) ERROR;
    if (set_sem(sem_power_plant, 0, 1) == -1) ERROR;
    if (set_sem(sem_processes,     0, 1) == -1) ERROR;

    if ((power_plant = shmat(shm_power_plant, NULL,0)) == (void*) -1) ERROR;
    if ((atoms       = shmat(shm_atoms,       NULL,0)) == (void*) -1) ERROR;
    if ((inhibitor   = shmat(shm_inhibitor,   NULL,0)) == (void*) -1) ERROR;


    pid_t temp = 0;

    printf("attivatore.c    -run\n");
    switch ((Activator_pid = fork())) {
        case -1:
            ERROR;

        case 0:
            execl("./attivatore", "./attivatore", NULL);
            printf("activator not started correctly\n");
            ERROR;

        default:
            reserveSem(sem_processes,0);
            break;
    }

    printf("alimentatore.c  -run\n");

    switch ((Powersupply_pid = fork())) {
        case -1:
            ERROR;

        case 0:
            execl("./alimentatore", "./alimentatore", NULL);
            printf("power supply not started correctly\n");
            ERROR;

        default:
            reserveSem(sem_processes,0);
            break;
    }
    
    printf("inibitore.c     -run\n");
    switch ((temp = fork())) {
        case -1:
            ERROR;
        case 0:
            execl("./inibitore", "./inibitore", NULL);
            printf("Inhibitor not started correctly\n");
            ERROR;
        default:
            inhibitor->Inhibitor_pid = temp;
            reserveSem(sem_processes,0);
            break;
    }

    create_atoms(vars->N_ATOMI_INIT);


    daily_log();

    printf("\n\t\t\033[1mEND\033[0m\n");
    terminate();
}