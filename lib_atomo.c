#include "lib_header.h"

int energy(int n1, int n2) {
    return n1 * n2 - (n1 > n2 ? n1 : n2);
}

void do_fission(Atom* atom_parent, pid_t child_pid) {

    reserveSem(sem_inhibitor, 0);
    if (inhibitor->inhibitor_setup && (rand() % 5) == 0) {
        if (kill(child_pid, SIGKILL) == 0) {
            reserveSem(sem_power_plant, 0);
            reserveSem(sem_var,0);
            --power_plant->atom_count;
            --vars->atom_Fork;
            ++power_plant->waste_atoms;
            inhibitor->denied_fission++;
            releaseSem(sem_power_plant, 0);
            releaseSem(sem_var, 0);
        } else
            ERROR;
        releaseSem(sem_inhibitor, 0);
        return;
    }
    else if (atom_parent.atomic_number <= vars->MIN_N_ATOMICO) {
        if (kill(child_pid, SIGKILL) == 0) {
            reserveSem(sem_power_plant, 0);
            reserveSem(sem_var,0);
            ++power_plant->waste_atoms;
            --power_plant->atom_count;
            --vars->atom_Fork;
            releaseSem(sem_power_plant, 0);
            releaseSem(sem_var, 0);
        } else
            ERROR;
        return;
    } else {
        struct Atom child;
        child.Atom_pid = child_pid;
        child.atomic_number   = atom_parent.atomic_number / 2;
        atom_parent.atomic_number = atom_parent.atomic_number - child.atomic_number;
        int liberata = 0;
        if(atom_parent.atomic_number == child.atomic_number)
            liberata = energy(atom_parent.atomic_number, child.atomic_number);

        //reserveSem(sem_inhibitor, 0);
        if (inhibitor->inhibitor_setup == true) {
            float rand_num = (float)rand() / RAND_MAX * 0.5;
            inhibitor->absorbed_energy += (liberata * rand_num);
            liberata -= (liberata * rand_num);
        }

        //reserveSem(sem_power_plant, 0);
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
                //releaseSem(sem_var,0);
                //releaseSem(sem_inhibitor, 0);
                //releaseSem(sem_power_plant, 0);
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
        //releaseSem(sem_inhibitor, 0);

        //reserveSem(sem_atom, 0);
        atoms[power_plant->atom_count] = child;
        //releaseSem(sem_atom, 0);

        //releaseSem(sem_power_plant, 0);
        //releaseSem(sem_var, 0);
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
    if ((shmdt(atoms))       == -1) ERROR;
    if ((shmdt(power_plant)) == -1) ERROR;
    if ((shmdt(inhibitor))   == -1) ERROR;
    unloadIPCs();
}
