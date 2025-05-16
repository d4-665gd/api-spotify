#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <sys/wait.h>

#define ERROR -1
#define LIMITE 20

union semun {
    int val;
};

int main() {
    key_t llave;
    int semaforos;
    struct sembuf operacion;
    union semun arg;

    
    llave = ftok("/bin/ls", 1974);
    if (llave == ERROR) {
        perror("ftok() falló");
        exit(1);
    }

    
    semaforos = semget(llave, 2, 0600 | IPC_CREAT);
    if (semaforos == ERROR) {
        perror("semget() falló"); //crear semaforo con fork y clone intercalable entre padre e hijo
        exit(1);
    }

    
    arg.val = 1;
    if (semctl(semaforos, 0, SETVAL, arg) == ERROR) {
        perror("semctl padre falló");
        exit(1);
    }

    arg.val = 0;
    if (semctl(semaforos, 1, SETVAL, arg) == ERROR) {
        perror("semctl hijo falló");
        exit(1);
    }

    pid_t pid = fork();
    if (pid == ERROR) {
        perror("fork() falló");
        exit(1);
    }

    for (int i = 0; i < LIMITE; i++) {
        if (pid == 0) { 
            
            operacion.sem_num = 1;
            operacion.sem_op = -1;
            operacion.sem_flg = 0;
            semop(semaforos, &operacion, 1);

          
            printf("Hijo dice hola (%d)\n", i+1);
            fflush(stdout);

            
            operacion.sem_num = 0;
            operacion.sem_op = 1;
            semop(semaforos, &operacion, 1);
        } else { 
            
            operacion.sem_num = 0;
            operacion.sem_op = -1;
            operacion.sem_flg = 0;
            semop(semaforos, &operacion, 1);

            
            printf("Padre dice hola (%d)\n", i+1);
            fflush(stdout);

            
            operacion.sem_num = 1;
            operacion.sem_op = 1;
            semop(semaforos, &operacion, 1);
        }
    }

    if (pid != 0) {
        wait(NULL); 
        semctl(semaforos, 0, IPC_RMID); 
        printf("Fin del programa\n");
    }

    return 0;
}
