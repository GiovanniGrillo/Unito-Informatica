#include <stdio.h>
#include <time.h>


void provasleep() {
    struct timespec request = {0, 500000000}; // Imposta la pausa a 500 millisecondi
    struct timespec remaining; // Per memorizzare il tempo rimanente in caso di interruzione
    if (nanosleep(&request, &remaining) == -1) {
        perror("ERROR");
    } else {
        printf("Processo in sleep");
    }
}