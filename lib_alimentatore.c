#include "lib_header.h"

int create_atoms(int number_atoms) {
    int i = 0;
    reserveSem(sem_atom,0);
    reserveSem(sem_power_plant,0);
    while (i < number_atoms) {
        atoms[power_plant->atom_count].atomic_number = (rand() % vars->N_ATOM_MAX) + 1;
        atoms[power_plant->atom_count].Atom_pid = (0);
        ++power_plant->atom_count;
        ++i;
    }
    releaseSem(sem_atom,0);
    releaseSem(sem_power_plant,0);
    return 0;
}

void exit_handler(){
    if ((shmdt(atoms))       == -1) ERROR;
    if ((shmdt(power_plant)) == -1) ERROR;
    unloadIPCs();
    exit(0);
}
