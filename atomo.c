#include "lib_header.c"
#include "lib_atomo.c"


int main() {
    srand(time(NULL));
    loadIPCs();
    setup_signal_handler(NULL);

  //  if ((atoms        = shmat(shm_atoms,       NULL, 0)) == (void*) -1) ERROR;
  //  if ((power_plant  = shmat(shm_power_plant, NULL, 0)) == (void*) -1) ERROR;
  //  if ((inhibitor    = shmat(shm_inhibitor, NULL, 0)) == (void*) -1) ERROR;

    int received_messages = 0;
    //reserveSem(sem_var,0);
    while(vars->exit_flag != 1) {
        while ((vars->atom_Fork > 0)) {
            if(vars->exit_flag != 0){
                //releaseSem(sem_var,0);
                exit(0);
            }
            //releaseSem(sem_var,0);
            if (msgrcv(msg_stack, &message, sizeof(message) - sizeof(long), 1, 0) == -1)
                continue;

            ++received_messages;
              attShm();
            //reserveSem(sem_power_plant, 0);
            if (power_plant->atom_count > 0) {
                int numero_casuale = rand() % (power_plant->atom_count - 1) + 1;
                //releaseSem(sem_power_plant, 0);
                //reserveSem(sem_atom, 0);
                Atom atom_parent = atoms[(numero_casuale)];

                switch (atom_parent.Atom_pid = fork()) {
                    case -1:
                        perror("MELTDOWN");
                        exit(1);
                        break;
                    case 0:
                        do_fission(atom_parent);
                        exit(0);
                        break;
                    default:
                        break;
                }
                //releaseSem(sem_atom, 0);
                //reserveSem(sem_var,0);
                if(received_messages %((vars->N_MSG)/2) == 0){
                    releaseSem(sem_var, 0);
                    sim_overview(received_messages);
                }
            }
            else
                printf("atoms are transferred to the power plant");
        }

    }
 //  if ((shmdt(atoms))       == -1) ERROR;
 //  if ((shmdt(power_plant)) == -1) ERROR;
 //  if ((shmdt(inhibitor)) == -1) ERROR;
    unloadIPCs();
    return 0;
}