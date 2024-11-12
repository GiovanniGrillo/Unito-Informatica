#include "lib_header.h"

void exit_handler(){
    unloadIPCs();
    exit(0);
}