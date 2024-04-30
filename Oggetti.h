#define SIM_DURATION 30

typedef struct Var {
int ENERGY_DEMAND;
int ENERGY_EXPLODE_THRESHOLD;
int flagTerminazione;
int fork_atomi;
int MIN_N_ATOMICO;
int N_ATOMI_INIT;
int N_ATOM_MAX;
int STEP_ALIMENTAZIONE;
int STEP_ATTIVATORE;
} Var;

typedef struct Centrale{
    int energia;
    int n_atomi;
    int scorie;
}Centrale;


typedef struct Atomo {
    pid_t pidAtomo;
    int numero_atomico;
} Atomo;


struct msg_buffer {
    long msg_type;
} message;

/* Coda di messaggi */
int semPila;
int msgPila;
//msg message;

/* Semafori */
int semAttivatore;
int semFissione;
int semShm;
int semProcessi;
int semCentrale;

/* Memorie Codivise*/
int shmAtomi;   Atomo* atomi;
int shmVar;     Var*   var;
int shmPila;    int*   pila;
int shmCentrale; Centrale* centrale;

/* Flag Terminazione e controlloSegnali*/
int flagTempesta;
int flagTerminazione;

// File 
FILE* out_progetto;
FILE* in_progetto;


/* Variabili Globali */
   pid_t pidAtomo;
   pid_t pidAttivatore;
   pid_t pidAlimentatore;
