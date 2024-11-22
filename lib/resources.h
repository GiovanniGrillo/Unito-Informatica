#ifndef RESOURCES_H
#define RESOURCES_H
#include <sys/types.h>
#include <stdbool.h>
#include <stdio.h>
/*Simulation Duration */
#define SIM_DURATION 10

/* Data Structures */
typedef struct Var {
    pid_t master_pid;
    int ENERGY_DEMAND;
    int ENERGY_EXPLODE_THRESHOLD;
    int N_ATOMI_INIT;
    int N_ATOM_MAX;
    int N_MSG;
    int N_NUOVI_ATOMI;
    int STEP_ALIMENTAZIONE;
    int STEP_ATTIVATORE;
    int i;
} Var;

typedef struct PowerPlant{
    int energy;
    int atom_count;
    int waste_atoms;
}PowerPlant;

typedef struct Atom {
    pid_t Atom_pid;
    int atomic_number;
} Atom;

typedef struct Inhibitor {
    pid_t Inhibitor_pid;
    bool inhibitor_setup;
    int absorbed_energy;
    int denied_fission;
    int done_fission;
}Inhibitor;

struct msg_buffer {
    long msg_type;
    int msg_op;
    int msg_absorb;
} message;

/* Message Queue */
    int inhibitor_stack;
    int msg_stack;

/* Semaphores */
    int sem_power_plant;
    int sem_inhibitor;
    int sem_atom;
    int sem_processes;
    int sem_fission;
    int sem_prova;

/* Shared Memory*/
    int shm_atoms;        Atom* atoms;
    int shm_vars;         Var* vars;
    int shm_power_plant;  PowerPlant* power_plant;
    int shm_inhibitor;    Inhibitor* inhibitor;

/* Files */
    FILE* sim_Input;
    FILE* sim_Output;

/* Global Variables */
    pid_t Atom_pid;
    pid_t Activator_pid;
    pid_t Powersupply_pid;

#endif