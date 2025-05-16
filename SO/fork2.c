#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <sched.h>

#define TIMES 10
#define STACK_SIZE 1024 * 1024
int shared=0;

int child(){
    int i;
    shared=21;
    for(i=0;i<TIMES;i++)
            printf("Proceso hijo: %d (Variable golbal = %d)\n",i,shared);
    return EXIT_SUCCESS;
}

int main(int argc, char *argv[]){
    pid_t cpid;
    unsigned char *stackChild;
    unsigned char *stackTop;

    if((stackChild==malloc(STACK_SIZE))){
        perror("malloc");
        exit(EXIT_FAILURE)
    }

    stackTop= stackChild + STACK_SIZE;
    cpid= clone(child, stackTop, CLONE_VM | CLONE_FILES, NULL);

    if(cpid==-1){
        perror("clone");
        exit(EXIT_FAILURE);
    }

    //Contexto del padre
    int i;
    shared=74;
    for(i=0;i<TIMES;i++)
        printf("Proceso hijo: %d (Variable golbal = %d)\n",i,shared);
    free(stackChild);
    exit(EXIT_SUCCESS);
    //return 0;
}
