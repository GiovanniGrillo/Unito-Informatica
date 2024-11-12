#include "lib_header.h"

void exit_handler(){
    pid_t child_pid;
    while ((child_pid = waitpid(-1, NULL, WNOHANG)) > 0);
    if ((shmdt(atoms))       == -1) ERROR;
    if ((shmdt(power_plant)) == -1) ERROR;
    unloadIPCs();
    exit(0);
}