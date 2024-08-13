#include "lib_header.h"

int numMessaggiRicevuti = 0;

int energy(int n1, int n2) {
    return n1 * n2 - (n1 > n2 ? n1 : n2);
}

void do_fission(Atom a_PADRE) {
    // printf("\n\033[1;34mMessaggio ricevuto, msg n°%d  eseguo scissione\033[0m", numMessaggiRicevuti);
    if (inhibitor->inhibitor_setup == true) {
        int random = rand() % 5;
        if (random == 0) {
            inhibitor->denied_fission++;
            ++power_plant->waste_atoms;
            --power_plant->atom_count;
            --vars->atom_Fork;
            dettShm();
            releaseSem(sem_fission, 0);
            endProcess();
        }
    }

    // Controllo se è minore delle condizioni
    if (a_PADRE.atomic_number <= vars->MIN_N_ATOMICO) {
        ++power_plant->waste_atoms;
        --power_plant->atom_count;
        --vars->atom_Fork;
        dettShm();
        releaseSem(sem_fission, 0);
        endProcess();
    } else {
       // int numero_casuale = rand() % (a_PADRE.atomic_number - 1) + 1;
        struct Atom figlio;
        //GUARDA QUI
        figlio.atomic_number   = a_PADRE.atomic_number / 2;
        a_PADRE.atomic_number = a_PADRE.atomic_number - figlio.atomic_number;
        int liberata = 0;
        if(a_PADRE.atomic_number == figlio.atomic_number)
            liberata = energy(a_PADRE.atomic_number, figlio.atomic_number);

        if (inhibitor->inhibitor_setup == true) {
            float rand_num = (float)rand() / RAND_MAX * 0.5;
            inhibitor->absorbed_energy += (liberata * rand_num);
            liberata -= (liberata * rand_num);
        }

        if ((power_plant->energy += liberata) > vars->ENERGY_EXPLODE_THRESHOLD) {
            if (inhibitor->inhibitor_setup == true) {
                // printf("\nLa power_plant stava esplodendo il processo inhibitor è intervenuto\n");
                //GUARDA QUI
                int energia_da_assorbire = (power_plant->energy - vars->ENERGY_EXPLODE_THRESHOLD) * 2;
                inhibitor->absorbed_energy += energia_da_assorbire;
                power_plant->energy -= energia_da_assorbire;
                // printf("\nTUTTO SALVO CI PENSA INIBITORE\n");
            } else {
                vars->exit_flag = 1;
                printf("\ncentrale esplosa, troppa energy liberata\n");
                printf("il vero valore di ENERGYEXPLODETRESHOLD è: %d", vars->ENERGY_EXPLODE_THRESHOLD);


                dettShm();
                deallocIPC();
                kill(Activator_pid,   SIGTERM);
                kill(atom_pid,        SIGTERM);
                kill(Powersupply_pid, SIGTERM);
                endProcess();
            }
        }

        // printf("\033[0;35m");
        // printf("energy presente nella power_plant è: %d\n", power_plant->energy);
        // printf("\033[0m");
        // printf("\n\033[;34menergia liberata: %d \033[0m ", liberata);

        power_plant->energy += liberata;
        --vars->atom_Fork;
        ++power_plant->atom_count;
        ++inhibitor->done_fission;
        printf("\033scissioni effettuate dopo %d!\033[0m\n", inhibitor->done_fission);

        atoms[power_plant->atom_count] = figlio;

        // printf("\n\033[1;34m il valore di fork atoms è %d e abbiamo %d atoms nella power_plant \033[0m ", vars->atomFork, power_plant->n_atomi);
        dettShm();
        releaseSem(sem_fission, 0);
        endProcess();
    }
}