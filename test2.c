    #include "lib_header.h"

    int main() {

        setbuf(stdout, NULL);
        srand(time(NULL));

        createIPCS("Progetto.conf");
       
        if(set_sem(semShm,           0, 1) == -1) ERROR;
        if(set_sem(semAttivatore,    0, 1) == -1) ERROR;
        if(set_sem(semFissione,      0, 1) == -1) ERROR;
        if(set_sem(semProcessi,      0, 1) == -1) ERROR;
        attShm();
        creazione_atomi(var->N_ATOMI_INIT);
        dettShm();
     
        
        // signal(SIGINT, handle_sigint);    
    printf("::::::::::::::::::::::::::::::::::::::::::\n");
    printf(":::  PROCESSO ATTIVATORE - Start       :::\n");
    printf("::::::::::::::::::::::::::::::::::::::\n::\n");



        pidAttivatore = fork();
        if (pidAttivatore == -1) {
            ERROR;
        } else if (pidAttivatore == 0) {
            execl("./attivatore", "./attivatore", NULL);
            printf("\nAttivatore non avviato correttamente\n");
            ERROR;
            exit(0);
        }
    printf("::::::::::::::::::::::::::::::::::::::::::\n");
    printf(":::  PROCESSO ALIMENTATORE - Start     :::\n");
    printf("::::::::::::::::::::::::::::::::::::::\n::\n");
        pidAlimentatore = fork();
        if (pidAlimentatore == -1) {
            ERROR;
        } else if (pidAlimentatore == 0) {
            execl("./alimentatore", "./alimentatore", NULL);
            printf("\nAlimentatore non avviato correttamente\n");
            ERROR;
            exit(0);
        }
    printf("::::::::::::::::::::::::::::::::::::::::::\n");
    printf(":::  PROCESSO ATOMO - Start            :::\n");
    printf("::::::::::::::::::::::::::::::::::::::\n::\n"); 
            pidAtomo = fork();
        if (pidAtomo == -1) {
            ERROR;
        } else if (pidAtomo == 0) {
            execl("./atomo", "./atomo", NULL);
            printf("\nAtomo non avviato correttamente\n");
            ERROR;
            exit(0);
        }

        // pidInibitore = fork();
        // if (pidInibitore == -1) {
        //     ERROR;
        // } else if (pidAtomo == 0) {
        //     execl("./inibitore", "./inibitore", NULL);
        //     printf("\n Inibitore non avviato correttamente\n");
        //     ERROR;
        //     exit(0);
        // }
        
        stampa();
       


        kill(pidAttivatore,     SIGTERM);
        kill(pidAlimentatore,   SIGTERM);


        printf("\nSono fuori!\n");

        deallocIPC();
        return 0;
    }