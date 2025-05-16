#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/ipc.h>

#define ERROR -1

int main( int argc, char *argv[]){
  key_t llave;
  int semaforo;
  struct sembuf proceso;
  llave = ftok("/bin/ls",1974);
  if(llave== ERROR){
    perror("ftok() call failed");
    exit(1);
  }
  semaforo = semget(llave,1,0600 | IPC_CREAT);
  if(semaforo == ERROR){
    perror("semget() call failed");
    exit(1);
  }
  if(semctl(semaforo,0, SETVAL,0) == ERROR){
    perror("semctl() call failed");
    exit(1);
  }
  proceso.sem_num= 0;
  proceso.sem_op= 1;
  proceso.sem_flg= 0;

  if(semop (semaforo,&proceso,1) ==ERROR){
    perror("semop() call failed");
    exit(1);
  }
  printf("Fin del programa B");
  return 0;
}