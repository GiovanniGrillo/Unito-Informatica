#define SIM_DURATION 10

/*enum stampa {INIZIALE, GIORNALIERA, FINALE};*/

typedef struct Var {
int ENERGY_DEMAND;
int N_ATOMI_INIT;
int N_ATOM_MAX;
int MIN_N_ATOMICO;
int STEP_ALIMENTAZIONE;
int ENERGY_EXPLODE_THRESHOLD;
int flagTerminazione;
int fork_atomi;
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

/*
typedef struct msg {
    long m_type;
    int  n;
} msg;*/

struct msg_buffer {
    long msg_type;
} message;

/* Coda di messaggi */
int semPila;
int msgPila;
//msg message;

/* Semafori */
int semAttivatore;
int semPila;
int semShm;
int semProcessi;

/* Memorie Codivise*/
int shmAtomi;   Atomo* atomi;
int shmVar;     Var*   var;
int shmPila;    int*   pila;
int shmCentrale; Centrale* centrale;

/* Flag Terminazione e controlloSegnali*/
int flagTempesta;
int flagTerminazione;

/* File 
FILE* out_progetto;
FILE* in_progetto;*/

/* Variabili Globali */

/*pid_t pid; 
pid_t pidAtomo; */