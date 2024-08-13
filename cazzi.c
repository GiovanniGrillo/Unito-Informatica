#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    // Inizializza il generatore di numeri casuali
    srand(time(NULL));

    // Genera un numero casuale tra 0 e 0.5
    float rand_num = (float)rand() / RAND_MAX * 0.5;

    // Stampa il risultato
    printf("Numero casuale tra 0 e 0.5: %f\n", rand_num);

    return 0;
}
