#include "lib_header.h"

int main() {
    setbuf(stdout, NULL);
    srand(time(NULL));

    createIPCS("Progetto.conf");

    if (set_sem(sem_shm,        0, 1) == -1) ERROR;
    if (set_sem(sem_activator, 0, 1) == -1) ERROR;
    if (set_sem(sem_fission,   0, 1) == -1) ERROR;
    if (set_sem(sem_processes,   0, 1) == -1) ERROR;
    if (set_sem(sem_inhibitor,  0, 1) == -1) ERROR;

    attShm();
    create_atoms(vars->N_ATOMI_INIT);
    dettShm();


    if(signal(SIGINT, handle_sigint) == SIG_ERR) ERROR;


    printf("\n══════════════════════════════════\n");
    printf("══ PROCESSO ATTIVATORE    -Start ═\n");
    printf("══════════════════════════════════\n");
    switch ((Activator_pid = fork())) {
        case -1:
            ERROR;

        case 0:
            execl("./attivatore", "./attivatore", NULL);
            printf("attivatore non avviato correttamente\n");
            ERROR;

        default:
            break;
    }

    printf("══════════════════════════════════\n");
    printf("══ PROCESSO ALIMENTATORE  -Start ═\n");
    printf("══════════════════════════════════\n");
    switch ((Powersupply_pid = fork())) {
        case -1:
            ERROR;

        case 0:
            execl("./alimentatore", "./alimentatore", NULL);
            printf("alimentatore non avviato correttamente\n");
            ERROR;

        default:
            break;
    }

    printf("══════════════════════════════════\n");
    printf("══ PROCESSO INIBITORE     -Start ═\n");
    printf("══════════════════════════════════\n");
    switch ((Inhibitor_pid = fork())) {
        case -1:
            ERROR;

        case 0:
            execl("./inhibitor", "./inhibitor", NULL);
            printf("inhibitor non avviato correttamente\n");
            ERROR;

        default:
            break;
    }

    printf("══════════════════════════════════\n");
    printf("══ PROCESSO ATOMO         -Start ═\n");
    printf("══════════════════════════════════\n\n");
    switch ((atom_pid = fork())) {
        case -1:
            ERROR;

        case 0:
            execl("./atomo", "./atomo", NULL);
            printf("atomo non avviato correttamente\n");
            ERROR;

        default:
            break;
    }

    daily_Log();

    printf("\nSono fuori!\n");
    deallocIPC();
    return 0;
}