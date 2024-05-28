#include "lib_header.h"

int main() {
    setbuf(stdout, NULL);
    srand(time(NULL));

    createIPCS("Progetto.conf");

    if (set_sem(semShm,        0, 1) == -1) ERROR;
    if (set_sem(semAttivatore, 0, 1) == -1) ERROR;
    if (set_sem(semFissione,   0, 1) == -1) ERROR;
    if (set_sem(semProcessi,   0, 1) == -1) ERROR;
    if (set_sem(semInibitore,  0, 1) == -1) ERROR;

    attShm();
    creazione_atomi(var->N_ATOMI_INIT);
    dettShm();


    if(signal(SIGINT, handle_sigint) == SIG_ERR) ERROR;


    printf("\n══════════════════════════════════\n");
    printf("══ PROCESSO ATTIVATORE    -Start ═\n");
    printf("══════════════════════════════════\n");
    switch ((pidAttivatore = fork())) {
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
    switch ((pidAlimentatore = fork())) {
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
    switch ((pidInibitore = fork())) {
        case -1:
            ERROR;

        case 0:
            execl("./inibitore", "./inibitore", NULL);
            printf("inibitore non avviato correttamente\n");
            ERROR;

        default:
            break;
    }

    printf("══════════════════════════════════\n");
    printf("══ PROCESSO ATOMO         -Start ═\n");
    printf("══════════════════════════════════\n\n");
    switch ((pidAtomo = fork())) {
        case -1:
            ERROR;

        case 0:
            execl("./atomo", "./atomo", NULL);
            printf("atomo non avviato correttamente\n");
            ERROR;

        default:
            break;
    }

    stampa();

    printf("\nSono fuori!\n");
    deallocIPC();
    return 0;
}