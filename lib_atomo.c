#include "lib_header.h"

int energy(int n1, int n2) {
    return n1 * n2 - (n1 > n2 ? n1 : n2);
}

void do_fission(Atom atom_parent) {
    // printf("\n\033[1;34mMessaggio ricevuto, msg n°%d  eseguo scissione\033[0m", numMessaggiRicevuti);
    if (inhibitor->inhibitor_setup == true) {
        int random = rand() % 5;
        if (random == 0) {
            inhibitor->denied_fission++;
            ++power_plant->waste_atoms;
            --power_plant->atom_count;
            --vars->atom_Fork;
            exit_handler();
        }
    }

    // Controllo se è minore delle condizioni
    if (atom_parent.atomic_number <= vars->MIN_N_ATOMICO) {
        ++power_plant->waste_atoms;
        --power_plant->atom_count;
        --vars->atom_Fork;
        exit_handler();
    } else {
       // int numero_casuale = rand() % (a_PADRE.atomic_number - 1) + 1;
        struct Atom child;
        child.atomic_number   = atom_parent.atomic_number / 2;
        atom_parent.atomic_number = atom_parent.atomic_number - child.atomic_number;
        int liberata = 0;
        if(atom_parent.atomic_number == child.atomic_number)
            liberata = energy(atom_parent.atomic_number, child.atomic_number);

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
                printf("\nPower plant exploded, energy: %d > ENERGY_EXPLODE_THRESHOLD: %d\n", power_plant->energy, vars->ENERGY_EXPLODE_THRESHOLD);

                deallocIPC();
                kill(Activator_pid,   SIGTERM);
                kill(Atom_pid,        SIGTERM);
                kill(Powersupply_pid, SIGTERM);
                exit_handler();
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
        // printf("done_fission: %d \n", inhibitor->done_fission);

        atoms[power_plant->atom_count] = child;

        // printf("\n\033[1;34m il valore di fork atoms è %d e abbiamo %d atoms nella power_plant \033[0m ", vars->atomFork, power_plant->n_atomi);
        exit_handler();
    }
}

void sim_overview(int msg_received) {
    reserveSem(sem_power_plant, 0);
    reserveSem(sem_inhibitor, 0);
    
    printf("\n\033[1mREPORT:\033[0m");
    printf("\t\t[ Inib: %s ]\n", inhibitor->inhibitor_setup ? "\033[1;32mTRUE\033[0m" : "\033[1;31mFALSE\033[0m");
    printf("Received messages: %d\n", msg_received);
    printf("Atom count: %d\n", power_plant->atom_count);
    printf("Fissions completed: %d\n", inhibitor->done_fission);
    printf("Power plant energy: %d\n", power_plant->energy);

    if (inhibitor->inhibitor_setup == true) {
        printf("Fissions denied by inhibitor: %d\n", inhibitor->denied_fission);
        printf("Energy absorbed by inhibitor: %d\n", inhibitor->absorbed_energy);

    }
    releaseSem(sem_power_plant, 0);
    releaseSem(sem_inhibitor, 0);
    
}

void exit_handler(){
    dettShm();
    exit(0);
}
