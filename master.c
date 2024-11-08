#include "lib_header.c"
#include "lib_master.c"

int main() {
    setbuf(stdout, NULL);
    srand(time(NULL));
    setup_signal_handler(NULL);
    // char *config_file = get_config_file();
    createIPCS("sim.conf");

    if (set_sem(sem_inhibitor,   0, 1) == -1) ERROR;
    if (set_sem(sem_atom,        0, 1) == -1) ERROR;
    if (set_sem(sem_power_plant, 0, 1) == -1) ERROR;
    if (set_sem(sem_var,         0, 1) == -1) ERROR;

    create_atoms(vars->N_ATOMI_INIT);

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

    /*printf("atomo.c         -run\n");
    switch ((Atom_pid = fork())) {
        case -1:
            ERROR;

        case 0:
            execl("./atomo", "./atomo", NULL);
            printf("atom not started correctly\n");
            ERROR;

        default:
            break;
    } */

   for(;;sleep(2))
    sim_overview();

    daily_log();

    printf("\n\t\t\033[1mEND\033[0m\n");
    exit_handler();
    deallocIPC();
    return 0;
}