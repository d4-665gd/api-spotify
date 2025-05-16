#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#define TAM 1024

void ejecutarComando(char *comando,int entrada,int salida);
int totalTuberias(const char * comando);

int main() {
    char comando[TAM];
    while (1) {
        printf("Team10@penguin:~$ ");
        fgets(comando, sizeof(comando), stdin);
        comando[strcspn(comando, "\n")] = '\0'; // Eliminar el salto de línea
        
       
        // Verificar si el usuario escribe "exit"
        if (strcmp(comando, "exit") == 0) {
            printf("Saliendo del shell...\n");
            break;
        }
        
        int size=totalTuberias(comando)+1;
        char *segmentos[size];
        int i=1;
        segmentos[0] = strtok(comando, "|");
        
        while(i<size){
            segmentos[i]= strtok(NULL, "|");
            i++;
        }

        int pipefd[2]; 
        pipe(pipefd);

        for (i=0;i<size;i++){

            int entrada = (i == 0) ? STDIN_FILENO : pipefd[0];
            int salida = (i == size-1) ? STDOUT_FILENO : pipefd[1];
            ejecutarComando(segmentos[i],entrada,salida);

            if (entrada != STDIN_FILENO) close(entrada);
            if (salida != STDOUT_FILENO) close(salida);
        }

        for(i=0;i<size;i++){
            wait(NULL);
        }

            
 }     
    return 0;
}



void ejecutarComando(char *comando,int entrada, int salida){

    pid_t pid = fork();
    if (pid == -1) {
        perror("Error al crear el proceso hijo");
    } else if (pid == 0) {

        if(entrada!=STDIN_FILENO){
            dup2(entrada, STDIN_FILENO);
            close(entrada);
        }

        if(salida!=STDOUT_FILENO){
            dup2(salida, STDOUT_FILENO);
            close(salida);
        }
        
    char *args[TAM];
    int i = 0;
    char *token = strtok(comando, " ");
    while (token != NULL) {
        args[i++] = token;
        token = strtok(NULL, " ");
    }

    args[i] = NULL;

    execvp(args[0], args);
    perror("Error ejecutando el comando");
    exit(EXIT_FAILURE);        
    }

}

int totalTuberias(const char * comando){
    int i = 0;
    for (; *comando; comando++)
        if (*comando == '|') i++;
    return i;

}