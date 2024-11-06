
/*Simulation Duration */
#define SIM_DURATION 10

/* Data Structures */
typedef struct Var {
    int ENERGY_DEMAND;
    int ENERGY_EXPLODE_THRESHOLD;
    int exit_flag;
    int atom_Fork;
    int MIN_N_ATOMICO;
    int N_ATOMI_INIT;
    int N_ATOM_MAX;
    int N_MSG;
    int N_NUOVI_ATOMI;
    int STEP_ALIMENTAZIONE;
    int STEP_ATTIVATORE;
    int STEP_INHIBITOR;
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
    bool inhibitor_setup;
    int absorbed_energy;
    int denied_fission;
    int done_fission;
}Inhibitor;

struct msg_buffer {
    long msg_type;
} message;

/* Message Queue */
    int sem_stack;
    int msg_stack;

/* Semaphores */
    int sem_var;
    int sem_power_plant;
    int sem_inhibitor;
    int sem_atom;

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
    pid_t Inhibitor_pid;