#include "lib_header.h"

int numMessaggiRicevuti = 0;

int energy(int n1, int n2) {
    return n1 * n2 - (n1 > n2 ? n1 : n2);
}

void esegui_scissione(Atomo a_PADRE) {
    printf("\n\033[1;34mMessaggio ricevuto, msg n°%d  eseguo scissione\033[0m", numMessaggiRicevuti);
    if (inibitore->InibitoreSetup == true) {
        int random = rand() % 5;
        if (random == 0) {
            inibitore->scissioni_negate++;
            ++centrale->scorie;
            --centrale->n_atomi;
            --var->fork_atomi;
            dettShm();
            releaseSem(semFissione, 0);
            endProcess();
        }
    }

    // Controllo se è minore delle condizioni
    if (a_PADRE.numero_atomico < var->MIN_N_ATOMICO) {
        ++centrale->scorie;
        --centrale->n_atomi;
        --var->fork_atomi;
        dettShm();
        releaseSem(semFissione, 0);
        endProcess();
    } else {
        int numero_casuale = rand() % (a_PADRE.numero_atomico - 1) + 1;
        struct Atomo figlio;
        figlio.numero_atomico   = a_PADRE.numero_atomico - numero_casuale;
        a_PADRE.numero_atomico -= figlio.numero_atomico;
        int liberata = energy(a_PADRE.numero_atomico, figlio.numero_atomico);

        if (inibitore->InibitoreSetup == true) {
            int liberatasoft = (int)(liberata * 0.80);
            inibitore->absorbed_energy += (liberata - liberatasoft);
            liberata = liberatasoft;
        }

        if ((centrale->energia += liberata) > var->ENERGY_EXPLODE_THRESHOLD) {
            if (inibitore->InibitoreSetup == true) {
                printf("\nLa centrale stava esplodendo il processo inibitore è intervenuto\n");
                int energia_da_assorbire = (int)(centrale->energia * 0.80);
                inibitore->absorbed_energy += energia_da_assorbire;
                centrale->energia -= energia_da_assorbire;

                printf("\nTUTTO SALVO CI PENSA INIBITORE\n");
            } else {
                var->flagTerminazione = 1;
                printf("\ncentrale esplosa, troppa energia liberata\n");
                printf("il vero valore di ENERGYEXPLODETRESHOLD è: %d", var->ENERGY_EXPLODE_THRESHOLD);

                dettShm();
                deallocIPC();
                kill(pidAttivatore,   SIGTERM);
                kill(pidAtomo,        SIGTERM);
                kill(pidAlimentatore, SIGTERM);
                endProcess();
            }
        }

        printf("\033[0;35m");
        printf("energia presente nella centrale è: %d\n", centrale->energia);
        printf("\033[0m");
        printf("\n\033[1;34menergia liberata: %d \033[0m ", liberata);

        centrale->energia += liberata;
        --var->fork_atomi;
        ++centrale->n_atomi;
        atomi[centrale->n_atomi] = figlio;

        printf("\n\033[1;34m il valore di fork atomi è %d e abbiamo %d atomi nella centrale \033[0m ", var->fork_atomi, centrale->n_atomi);
        dettShm();
        releaseSem(semFissione, 0);
        endProcess();
    }
}