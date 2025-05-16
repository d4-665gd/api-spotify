/*
   Ejemplo de uso de semáforos sin nombre (unamed) con
   memoria compartida y mapeo de memoria.

   Lo anterior es necesario cuando se utiliza fork debido
   a que fork genera espacios de memoria independientes para los
   procesos, y se requiere que el semáforo sea visto por ambos
   procesos.
   
   Compare con sem_unamed_thread.c
   
   Compilar con:
   	$ gcc -Wall sem_unamed.c -o suf -lpthread -lrt

   @autor Ricardo Ruiz Rodríguez.
*/
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/mman.h>

#define ERROR -1
#define SHARED 1

int main(int argc, char *argv[]){
   sem_t *sem;
   pid_t cpid;
   int shm_fd;
   
   shm_fd = shm_open("/sem_shm", O_CREAT | O_RDWR, 0666);
   if(shm_fd == ERROR){
      printf("%s\n", strerror(errno));
      exit(EXIT_FAILURE);
   }

   if(ftruncate(shm_fd, sizeof(sem_t)) == ERROR){
      printf("%s\n", strerror(errno));
      exit(EXIT_FAILURE);
   }
   
   sem = (sem_t *) mmap(0, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
   if(sem == MAP_FAILED) {
      printf("%s\n", strerror(errno));
      exit(EXIT_FAILURE);
	}

   if(sem_init(sem, SHARED, 0) == ERROR){
      printf("%s\n", strerror(errno));
      exit(EXIT_FAILURE);
   }

   cpid = fork();
   if(cpid == ERROR) {
      printf("%s\n", strerror(errno));
      exit(EXIT_FAILURE);
    }

   if(cpid == 0){ // Proceso hijo
      if(sem_post(sem) == ERROR){   // UP
         printf("%s\n", strerror(errno));
         exit(EXIT_FAILURE);
      }else{
         printf("Proceso hijo despertando al proceso padre\n");
      }
      printf("Fin de proceso hijo\n");
   }else{ // Proceso padre
      printf("Proceso padre bloqueado\n");
      if(sem_wait(sem) == ERROR){   // DOWN
         printf("%s\n", strerror(errno));
         exit(EXIT_FAILURE);
      }else{
         printf("Proceso padre desbloqueado\n");
      }
      printf("Proceso padre liberando semáforo\n");
      if(sem_destroy(sem) == ERROR){
         printf("%s\n", strerror(errno));
         exit(EXIT_FAILURE);
      }else{
         printf("\tSemáforo liberado\n");
      }
      printf("Fin de proceso Padre\n");
   }

   return 0;
}

