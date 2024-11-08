#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
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


#define PERMISSIONS  0666
#define FTOK_FILE    "attivatore.c"

#define ERROR                                                                                                                                     \
    {                                                                                                                                             \
        if (errno) {                                                                                                                              \
            fprintf(stderr, "ERROR - line %d: file \"%s\" (pid %d) - n %d - (%s)\n", __LINE__, __FILE__, getpid(), errno, strerror(errno));       \
            exit(1);                                                                                                                              \
        }                                                                                                                                         \
    }

long int convert_to_million(int n);

char* get_config_file();

void createIPCS(char* file);

void create_atoms(int n_atoms);

void loadIPCs();

void deallocIPC();

int reserveSem(int id_sem, int n_sem);

int releaseSem(int id_sem, int n_sem);

int set_sem(int sem_id, int sem_num, int val);

void unloadIPCs();

void do_fission(Atom* atom_parent, pid_t child_pid);

void sim_overview(int received_message);

void daily_log();

void handle_sig_inhibitor();

void setup_signal_handler(void (*handler)(int));

void exit_handler();