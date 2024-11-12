#include "lib_header.h"

int energy(int n1, int n2) {
    return n1 * n2 - (n1 > n2 ? n1 : n2);
}

void do_fission(Atom* atom_parent, int child_pid) {
    if (inhibitor->inhibitor_setup){
        if (kill(inhibitor->Inhibitor_pid, SIGUSR1) == 0) {
            if (msgrcv(inhibitor_stack, &message, sizeof(message) - sizeof(long), 1, 0) == -1) {} 

            if(message.msg_op == 0){ //scissione negata
                if (kill(child_pid, SIGKILL) == -1) ERROR;
                reserveSem(sem_inhibitor,0);
                ++inhibitor->denied_fission;
                releaseSem(sem_inhibitor, 0);
                return;
            }
            else if (message.msg_op == 1) { // atomo trasformato in scoria
            if (kill(child_pid, SIGKILL) == -1) ERROR;
            reserveSem(sem_power_plant, 0);
            ++power_plant->waste_atoms;
            releaseSem(sem_power_plant, 0);
            return;
            }
        } ERROR;
    }
    if (atom_parent->atomic_number <= vars->MIN_N_ATOMICO) {
        if (kill(child_pid, SIGKILL) == -1) ERROR;
        reserveSem(sem_power_plant, 0);
        ++power_plant->waste_atoms;
        releaseSem(sem_power_plant, 0);
        exit_handler();
        exit(0);
    } 
        struct Atom child;
        reserveSem(sem_atom,0);
        child.atomic_number = atom_parent->atomic_number / 2;
        atom_parent->atomic_number = atom_parent->atomic_number - child.atomic_number;
        atoms[power_plant->atom_count] = child;
        ++power_plant->atom_count;
        releaseSem(sem_atom,0);
        int liberata = 0;
        if(atom_parent->atomic_number == child.atomic_number){
            liberata = energy(atom_parent->atomic_number, child.atomic_number);
            if (inhibitor->inhibitor_setup){
                message.msg_absorb = liberata;
                if(msgsnd(inhibitor_stack, &message, sizeof(message) - sizeof(long), 0) == -1) {}
                if (msgrcv(inhibitor_stack, &message, sizeof(message) - sizeof(long), 1, 0) == -1) {}
                liberata = message.msg_absorb;
        }
/*
if (inhibitor->inhibitor_setup == true) {
    float rand_num = (float)rand() / RAND_MAX * 0.5;
    inhibitor->absorbed_energy += (liberata * rand_num);
    liberata -= (liberata * rand_num);
}
*/
        reserveSem(sem_power_plant, 0);
        reserveSem(sem_inhibitor, 0);
        if ((power_plant->energy += liberata) > vars->ENERGY_EXPLODE_THRESHOLD) {
            if (inhibitor->inhibitor_setup == true) {
                int energia_da_assorbire = (power_plant->energy - vars->ENERGY_EXPLODE_THRESHOLD) * 2;
                inhibitor->absorbed_energy += energia_da_assorbire;
                power_plant->energy -= energia_da_assorbire;
            } else {
                vars->exit_flag = 1;
                if(kill(vars->master_pid, SIGUSR2) == -1) ERROR;
                releaseSem(sem_inhibitor, 0);
                releaseSem(sem_power_plant, 0);
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
        return;
    }
}

void exit_handler(){
    pid_t child_pid;
    while ((child_pid = waitpid(-1, NULL, WNOHANG)) > 0);
    if ((shmdt(atoms))       == -1) ERROR;
    if ((shmdt(power_plant)) == -1) ERROR;
    if ((shmdt(inhibitor))   == -1) ERROR;
    unloadIPCs();
    exit(0);
}
