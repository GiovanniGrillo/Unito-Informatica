#include "resources.h"

#define FTOK_FILE    "attivatore.c"
#define PERMISSIONS  0666

#define ERROR                                                                                                                                     \
    {                                                                                                                                             \
        if (errno) {                                                                                                                              \
            fprintf(stderr, "ERROR - line %d: file \"%s\" (pid %d) - n %d - (%s)\n", __LINE__, __FILE__, getpid(), errno, strerror(errno));       \
            exit(1);                                                                                                                              \
        }                                                                                                                                         \
    }

// lib_header.c
long int convert_to_million(int n);

void loadIPCs();
void unloadIPCs();

int reserveSem(int id_sem, int n_sem);
int releaseSem(int id_sem, int n_sem);

void create_atoms(int number_atoms);

void setup_signal_handler(void (*handler)(int), int signum);

// lib_master.c
char* get_config_file();

void createIPCS(char* file);
void deallocIPC();
int set_sem(int sem_id, int sem_num, int val);

void daily_log();
void sim_overview(int day);

void terminate();
void explode_handler();
void meltdown_handler();
void exit_handler();

// lib_inibitore.c
int limit_fission();
int absorb_energy(int energy);
void exit_handler();

// lib_alimentatore.c
void exit_handler();

// lib_attivatore.c
void exit_handler();

// lib_atomo.c
int energy(int n1, int n2);
void do_fission(Atom* atom_parent, int child_pid);
void exit_handler();