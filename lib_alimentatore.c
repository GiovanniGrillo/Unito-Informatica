#include "lib_header.h"

void exit_handler(){
    if ((shmdt(atoms))       == -1) ERROR;
    if ((shmdt(power_plant)) == -1) ERROR;
    unloadIPCs();
    exit(0);
}
