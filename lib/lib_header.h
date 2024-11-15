#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include <time.h>
#include <math.h>

#include "resources.h"

#include <dirent.h>
#define PERMISSIONS  0666
#define FTOK_FILE    "attivatore.c"

#define ERROR                                                                                                                                     \
    {                                                                                                                                             \
        if (errno) {                                                                                                                              \
            fprintf(stderr, "ERROR - line %d: file \"%s\" (pid %d) - n %d - (%s)\n", __LINE__, __FILE__, getpid(), errno, strerror(errno));       \
            exit(1);                                                                                                                              \
        }                                                                                                                                         \
    }

// *********** lib_header.c
long int convert_to_million(int n);

void loadIPCs();
void unloadIPCs();

int reserveSem(int id_sem, int n_sem);
int releaseSem(int id_sem, int n_sem);

void create_atoms(int number_atoms);

void setup_signal_handler(void (*handler)(int), int signum);
void exit_handler();
// ***********

// *********** lib_master.c
char* get_config_file();

void createIPCS(char* file);
void deallocIPC();
int set_sem(int sem_id, int sem_num, int val);

void daily_log();
void sim_overview(int day);

void terminate();
void explode_handler();
void meltdown_handler();
// ***********

// *********** lib_inibitore.c
int limit_fission();
int absorb_energy(int energy);
// ***********

// *********** lib_alimentatore.c
// ***********

// *********** lib_attivatore.c
// ***********

// *********** lib_atomo.c
int energy(int n1, int n2);
void do_fission(Atom* atom_parent, int child_pid);
// ***********

