#include "lib_header.h"
//#define STEP_ATTIVATORE 1
//#define atomi_da_scindere [10] 
//#define MAX_ATOMI 10 // per ora li faccio runnare in locale

void processo_attivatore() {
    while (1) {
        sleep(STEP_ATTIVATORE); // Attende STEP_ATTIVATORE unità di tempo
        
        // Seleziona atomi per la scissione (implementazione a discrezione)
        int[] atomi_da_scindere = seleziona_atomi(); 
        //TODO COMUNICAZIONE CON ATOMO: ATTIVA SCISSIONE
        // Comunica agli atomi selezionati di scindersi
        for (int i = 0; i < sizeof(atomi_da_scindere)/sizeof(atomi_da_scindere[0]); i++) {
            comunica_scissione(atomi_da_scindere[i]);
        }
    }
}
int main(int argc, char const *argv[])
{
    processo_attivatore();
    return 0;
}