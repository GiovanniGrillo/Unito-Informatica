#include "lib_header.h"

int main()
{
    printf("Stampo il test()\n");
    test();
    return 0;
}

void test(){
      printf("Testing createIPCs()\n");
    createIPCs("Progetto.out");
        printf("Testing createIPCs() finito--\n");  

        printf("Testing loadIPCs()\n");
    loadIPCs();
        printf("Testing loadIPCs() finito--\n"); 
        
        printf("Testing attShm()\n");
    attShm();
        printf("Testing attShm() finito--\n");

        printf("Testing detShm()\n");
    detShm();
        printf("Testing detShm() finito--\n");

        printf("Testing deallocIPCs()\n");
    deallocIPCs();
        printf("Testing deallocIPCs() finito--\n");

        printf("Testing unloadIPCs()\n");
    unloadIPCs();
        printf("Testing unloadIPCs() finito--\n");

}