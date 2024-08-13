/*Durata Simulazione*/
#define SIM_DURATION 20

/* Strutture dati */
typedef struct Var {
    int ENERGY_DEMAND;
    int ENERGY_EXPLODE_THRESHOLD;
    int exitFlag;
    int atomFork;
    int MIN_N_ATOMICO;
    int N_ATOMI_INIT;
    int N_ATOM_MAX;
    int N_MSG;
    int N_NUOVI_ATOMI;
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

typedef struct Inibitore {
    bool InibitoreSetup;
    int absorbed_energy;
    int scissioni_negate;
}Inibitore;

struct msg_buffer {
    long msg_type;
} message;

/* Coda di messaggi */
    int semPila;
    int msgPila;

/* Semafori */
    int semAttivatore;
    int semFissione;
    int semShm;
    int semProcessi;
    int semCentrale;
    int semInibitore;

/* Memorie Codivise*/
    int shmAtomi;     Atomo* atomi;
    int shmVar;       Var* var;
    int shmPila;      int* pila;
    int shmCentrale;  Centrale* centrale;
    int shmInibitore; Inibitore* inibitore;

/* Flag Terminazione e controlloSegnali*/
    int flagTempesta;
    int exitFlag;

/* File */
    FILE* out_progetto;
    FILE* in_progetto;

/* Variabili Globali */
    pid_t pidAtomo;
    pid_t pidAttivatore;
    pid_t pidAlimentatore;
    pid_t pidInibitore;