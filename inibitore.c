#include "lib_header.h"


int main() {
    printf("\033[35mBenvenuto in Inibitore!\033[0m\n");

    loadIPCs();

    struct timespec attesa;attesa.tv_sec = 0;attesa.tv_nsec = 500000000L;

        while (var->flagTerminazione != 1) {
            attShm();
            out_progetto = fopen("Progetto.out", "a");
            fprintf(out_progetto,"\n------------------------ciao.sono entrato in inibitore");
            dettShm();
            nanosleep(&attesa, NULL);
        }

}