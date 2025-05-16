#define _GNU_SOURCE

#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

#define TIMES 50
#define STACK_SIZE 1024 * 1024

int shared=0;

int child(){
    int i;
    shared = 12;
    for(i=0; i< TIMES;i++)
       printf("Proceso hijo :%d (variable global = %d)\n", i,shared);
    return EXIT_SUCCESS;
}

int main(int argc, char *argv[]){
 pid_t cpid;
 unsigned char *stackChild;
 unsigned char *stackTop;

 if((stackChild = malloc(STACK_SIZE)) == NULL){
    perror("malloc");
    exit(EXIT_FAILURE);
 
}
    stackTop = stackChild + STACK_SIZE;
    cpid = clone(child, stackTop, CLONE_VM | CLONE_FILES | SIGCHLD, NULL);
  if(cpid == -1){
    perror("clone");
    free(stackChild);
    exit(EXIT_FAILURE); //examen: consierando el codigo en clone traducelo en fork y viceversa repasar
  }

  pid_t w;
  int wstatus;
  w = waitpid(cpid,&wstatus, WUNTRACED | WCONTINUED);
  if (w==-1){
   perror("waitpid");
   exit(EXIT_FAILURE); 
   free(stackChild);
  
}//checar servicios semget (crea semaforo),semctl (inicializa semaforos a la vez),SETVAL(dar valor)
  
  /*contexto del padre*/  
  int i;
  shared = 74;
  for(i=0; i<TIMES; i++)
     printf("Proceso padre :%d (variable global = %d)\n", i,shared);
     /* podria generar un error de acceso no valido de memoria: no hay
     sincronia entre el proceso padre y el hijo*/
   free(stackChild); 
   exit(EXIT_SUCCESS); 
}