#define NATOM_MAX 10
FILE* file_configurazione;
struct Atomo {
    int numero_atomico;
    int energia;
    // Altre informazioni dell'atomo, se necessario
};

struct Atomo crea_atomo() {
    struct Atomo nuovo_atomo;
    nuovo_atomo.numero_atomico = (rand() % NATOM_MAX) + 1;
    nuovo_atomo.energia = 0;
    return nuovo_atomo;
}

int calcola_energia_liberata(const struct Atomo *padre, const struct Atomo *figlio) {
    return padre->numero_atomico * figlio->numero_atomico - (padre->numero_atomico > figlio->numero_atomico ? padre->numero_atomico : figlio->numero_atomico);
}

void esegui_scissione(struct Atomo *padre, struct Atomo *figlio) {
    int energia_liberata = calcola_energia_liberata(padre, figlio);

    padre->energia += energia_liberata;
    figlio->energia = 0;

    printf("Scissione avvenuta. Energia liberata: %d\n", energia_liberata);
}

void creaIPCS(struct Configurazione *configurazione) {

    FILE *file = fopen("Progetto.conf", "r");

    if (file == NULL) {
        perror("Errore nell'apertura del file di configurazione");
        exit(EXIT_FAILURE);
    }

    // Lettura dei valori dalla configurazione
    fscanf(file, "ENERGY_DEMAND: %d\n", &configurazione->ENERGY_DEMAND);
    fscanf(file, "N_ATOMI_INIT: %d\n", &configurazione->N_ATOMI_INIT);
    fscanf(file, "N_ATOM_MAX: %d\n", &configurazione->N_ATOM_MAX);
    fscanf(file, "MIN_N_ATOMICO: %d\n", &configurazione->MIN_N_ATOMICO);
    fscanf(file, "STEP_ATTIVATORE: %d\n", &configurazione->STEP_ATTIVATORE);
    fscanf(file, "STEP_ALIMENTAZIONE: %d\n", &configurazione->STEP_ALIMENTAZIONE);
    fscanf(file, "SIM_DURATION: %d\n", &configurazione->SIM_DURATION);
    fscanf(file, "ENERGY_EXPLODE_THRESHOLD: %d\n", &configurazione->ENERGY_EXPLODE_THRESHOLD);

    fclose(file);
}