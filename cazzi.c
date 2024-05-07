#include "lib_header.h"

// Funzione per gestire il segnale SIGUSR1
void handle_signal_inibitore(int signum) {
    out_progetto = fopen("Progetto.out", "a");
    printf("\nciao.sono entrato in inibitore");
    // attShm();
    // out_progetto = fopen("Progetto.out", "a");
    // if (inibitore->active==1)
    // {
    //     fprintf(out_progetto, "\nINIBITORE è ATTIVO LO SPENGO \n");
    //     inibitore->active=0;
    // }else{
    //     fprintf(out_progetto, "\nINIBITORE è SPENTO LO ATTIVO \n");
    //     inibitore->active=1;
    // }
    // dettShm();
    }


int main() {
    printf("\033[35mBenvenuto in Inibitore!\033[0m\n");

    // Imposta la funzione 'gestore_segnale' come gestore del segnale SIGUSR1
    signal(SIGUSR1, handle_signal_inibitore);

    // Struttura per specificare il tempo di attesa
    struct timespec attesa;
    attesa.tv_sec = 0;
    attesa.tv_nsec = 500000000L; // 0.5 secondi

    // Il programma entra in un ciclo infinito
    while(1) {
        printf("In attesa di SIGUSR1...\n");
        nanosleep(&attesa, NULL);
    }

    return 0;
}