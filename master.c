#include "lib_header.h"

int main() {
    setbuf(stdout, NULL);
    srand(time(NULL));

    createIPCS("sim.conf");

    if (set_sem(sem_shm,       0, 1) == -1) ERROR;
    if (set_sem(sem_activator, 0, 1) == -1) ERROR;
    if (set_sem(sem_fission,   0, 1) == -1) ERROR;
    if (set_sem(sem_processes, 0, 1) == -1) ERROR;
    if (set_sem(sem_inhibitor, 0, 1) == -1) ERROR;

    attShm();
    create_atoms(vars->N_ATOMI_INIT);
    dettShm();


    if(signal(SIGINT, handle_sigint) == SIG_ERR) ERROR;


    printf("attivatore.c    -run\n");
    switch ((Activator_pid = fork())) {
        case -1:
            ERROR;

        case 0:
            execl("./attivatore", "./attivatore", NULL);
            printf("activator not started correctly\n");
            ERROR;

        default:
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
            break;
    }

    printf("inibitore.c     -run\n");
    switch ((Inhibitor_pid = fork())) {
        case -1:
            ERROR;

        case 0:
            execl("./inibitore", "./inibitore", NULL);
            printf("Inhibitor not started correctly\n");
            ERROR;

        default:
            break;
    }

    printf("atomo.c         -run\n");
    switch ((Atom_pid = fork())) {
        case -1:
            ERROR;

        case 0:
            execl("./atomo", "./atomo", NULL);
            printf("atom not started correctly\n");
            ERROR;

        default:
            break;
    }

    daily_Log();

    printf("\nEnd\n");
    deallocIPC();
    return 0;
}