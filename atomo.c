#include "lib/lib_header.c"
#include "lib/lib_atomo.c"


int main() {
    setbuf(stdout, NULL);
    srand(time(NULL));
    loadIPCs();
    setup_signal_handler(NULL); //SIGINT
    setup_exit_handler(exit_handler); //SIGTERM

    if ((atoms        = shmat(shm_atoms,       NULL, 0)) == (void*) -1) ERROR;
    if ((power_plant  = shmat(shm_power_plant, NULL, 0)) == (void*) -1) ERROR;
    if ((inhibitor    = shmat(shm_inhibitor,   NULL, 0)) == (void*) -1) ERROR;

    releaseSem(sem_processes,0);

   while(true) {
        if (msgrcv(msg_stack, &message, sizeof(message) - sizeof(long), 1, 0) == -1)
            continue;

        pid_t child_pid = 0;
        Atom* atom_parent;

        reserveSem(sem_atom, 0);
        reserveSem(sem_power_plant, 0);
        for (int i = 0; i < power_plant->atom_count; i++) {
            if (atoms[i].Atom_pid == getpid()) {
                atom_parent = &atoms[i];
                break;
            }
        }
        releaseSem(sem_power_plant, 0);
        releaseSem(sem_atom, 0);

        switch (child_pid = fork()) {
            case -1:
                fprintf(sim_Output, "\n***MELTDOWN***");
                perror("MELTDOWN");
                exit_handler();
                exit(1);
                break;
            case 0:
                break;
            default:
                do_fission(atom_parent, child_pid);
                break;
        }
    }
    exit_handler();
}