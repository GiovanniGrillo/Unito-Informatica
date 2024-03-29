#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <math.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include "lib_header.h"
#include "lib_atomo.h"




int main() {
    srand((unsigned int)time(NULL));

    // Simula la creazione di un atomo iniziale
    struct Atomo iniziale = crea_atomo();
    printf("Atomo iniziale creato con numero atomico: %d\n", iniziale.numero_atomico);

    // Simula la fissione dell'atomo iniziale
    simulateFission(&iniziale);

    return 0;
}


