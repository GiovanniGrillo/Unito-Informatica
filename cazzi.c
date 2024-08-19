#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    struct timespec att = {1, 999999999};  // 9 secondi e 0 nanosecondi
    for (;;) {
        printf("Ciao\n");
        nanosleep(&att, NULL);
    }

    return 0;
}       


