#include "lib_header.h"

int energy(int n1, int n2) {
    return n1 * n2 - (n1 > n2 ? n1 : n2);
}

void do_fission(Atom* atom_parent, int child_pid) {
    if (inhibitor->inhibitor_setup) {
        message.msg_op = 0;
        reserveSem(sem_fission, 0);
        if (msgsnd(inhibitor_stack, &message, sizeof(message) - sizeof(long), 0)    == -1) ERROR;
        if (msgrcv(inhibitor_stack, &message, sizeof(message) - sizeof(long), 2, 0) == -1) ERROR;
        releaseSem(sem_fission,0);

        if (message.msg_op == 0) { // denied fission
            if (kill(child_pid, SIGTERM) != 0) ERROR;
            reserveSem(sem_inhibitor, 0);
            ++inhibitor->denied_fission;
            releaseSem(sem_inhibitor, 0);
            return;
        }
        else if (message.msg_op == 1) { // wasted atom
            if (kill(child_pid, SIGTERM) != 0) ERROR;
            reserveSem(sem_power_plant, 0);
            ++power_plant->waste_atoms;
            releaseSem(sem_power_plant, 0);
            return;
        }
    }
    struct Atom child;
    reserveSem(sem_atom, 0);
    child.Atom_pid = child_pid;
    child.atomic_number = (atom_parent->atomic_number) / 2;
    atom_parent->atomic_number = atom_parent->atomic_number - child.atomic_number;
    reserveSem(sem_power_plant, 0);
    atoms[power_plant->atom_count].Atom_pid = child.Atom_pid;
    atoms[power_plant->atom_count].atomic_number = child.atomic_number;
    ++power_plant->atom_count;
    releaseSem(sem_power_plant, 0);
    releaseSem(sem_atom, 0);

    int liberata = 0;
    if (atom_parent->atomic_number == child.atomic_number) {
        liberata = energy(atom_parent->atomic_number, child.atomic_number);

        if (inhibitor->inhibitor_setup && liberata != 0) {
            message.msg_absorb = liberata;
            message.msg_op = 1;
            message.msg_type = 1;
            reserveSem(sem_fission, 0);
            if (msgsnd(inhibitor_stack, &message, sizeof(message) - sizeof(long), 0)    == -1) ERROR;
            if (msgrcv(inhibitor_stack, &message, sizeof(message) - sizeof(long), 2, 0) == -1) ERROR;
            releaseSem(sem_fission,0);
            liberata = message.msg_absorb;
        }
    }

    reserveSem(sem_power_plant, 0);
    reserveSem(sem_inhibitor, 0);

    if ((power_plant->energy += liberata) > vars->ENERGY_EXPLODE_THRESHOLD) {
        if (inhibitor->inhibitor_setup == true) {
            int energia_da_assorbire = (power_plant->energy - vars->ENERGY_EXPLODE_THRESHOLD) * 5;
            inhibitor->absorbed_energy += energia_da_assorbire;
            power_plant->energy -= energia_da_assorbire;
        } else {
            releaseSem(sem_inhibitor, 0);
            releaseSem(sem_power_plant, 0);
            if (kill(vars->master_pid, SIGUSR1) != 0) ERROR;
            return;
        }
    }

    power_plant->energy += liberata;
    releaseSem(sem_power_plant, 0);
    ++inhibitor->done_fission;
    releaseSem(sem_inhibitor, 0);

    return;
}


void exit_handler() {
    reserveSem(sem_removal, 0);
    for (int i = 0; i < power_plant->atom_count; i++) {
        if (atoms[i].Atom_pid == getpid()) {
            atoms[i] = atoms[power_plant->atom_count - 1];
            power_plant->atom_count--;
            break;
        }
    }
    releaseSem(sem_removal, 0);

    if ((shmdt(atoms))       == -1) ERROR;
    if ((shmdt(power_plant)) == -1) ERROR;
    if ((shmdt(inhibitor))   == -1) ERROR;

    unloadIPCs();
    exit(0);
}
