#include "lib_header.h"

int energy(int n1, int n2) {
    return n1 * n2 - (n1 > n2 ? n1 : n2);
}

void do_fission(Atom* atom_parent, pid_t child_pid) {
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
        return;
    }
    else if (atom_parent->atomic_number <= vars->MIN_N_ATOMICO) {
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
        reserveSem(sem_atom,0);
        child.atomic_number   = atom_parent->atomic_number / 2;
        atom_parent->atomic_number = atom_parent->atomic_number - child.atomic_number;
        atoms[power_plant->atom_count] = child;
        ++power_plant->atom_count;
        releaseSem(sem_atom,0);
        int liberata = 0;
        if(atom_parent->atomic_number == child.atomic_number)
            liberata = energy(atom_parent->atomic_number, child.atomic_number);

        if (inhibitor->inhibitor_setup == true) {
            float rand_num = (float)rand() / RAND_MAX * 0.5;
            inhibitor->absorbed_energy += (liberata * rand_num);
            liberata -= (liberata * rand_num);
        }
        reserveSem(sem_power_plant, 0);
        reserveSem(sem_inhibitor, 0);
        if ((power_plant->energy += liberata) > vars->ENERGY_EXPLODE_THRESHOLD) {
            if (inhibitor->inhibitor_setup == true) {
                int energia_da_assorbire = (power_plant->energy - vars->ENERGY_EXPLODE_THRESHOLD) * 2;
                inhibitor->absorbed_energy += energia_da_assorbire;
                power_plant->energy -= energia_da_assorbire;
            } else {
                vars->exit_flag = 1;
                printf("\nPower plant exploded, energy: %d > ENERGY_EXPLODE_THRESHOLD: %d\n", power_plant->energy, vars->ENERGY_EXPLODE_THRESHOLD);

                //deallocIPC();
                kill(Activator_pid,   SIGTERM);
                kill(Atom_pid,        SIGTERM);
                kill(Powersupply_pid, SIGTERM);
                releaseSem(sem_inhibitor, 0);
                exit_handler();
            }
        }
        power_plant->energy += liberata;
        releaseSem(sem_power_plant, 0);
        reserveSem(sem_var, 0);
        --vars->atom_Fork;
        releaseSem(sem_var, 0);
        ++inhibitor->done_fission;
        releaseSem(sem_inhibitor, 0);
    }
}

void exit_handler(){
    if ((shmdt(atoms))       == -1) ERROR;
    if ((shmdt(power_plant)) == -1) ERROR;
    if ((shmdt(inhibitor))   == -1) ERROR;
    exit(0);
}