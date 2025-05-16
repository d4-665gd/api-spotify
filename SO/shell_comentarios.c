#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>


#define TAM 1024 // Definición del tamaño máximo para los comandos

// Declaración de funciones auxiliares
void ejecutarComando(char *comando, int entrada, int salida);
int totalTuberias(const char * comando);

int main() {
    char comando[TAM];

    while (1) {
        printf("Team10@penguin:~$ "); // Mostrar el prompt personalizado
        fgets(comando, sizeof(comando), stdin); // Leer la entrada del usuario
        comando[strcspn(comando, "\n")] = '\0'; // Eliminar el salto de línea
        
        // Verificar si el usuario escribe "exit" para salir del shell
        if (strcmp(comando, "exit") == 0) {
            printf("Saliendo del shell...\n");
            break;
        }
        
        int size = totalTuberias(comando) + 1; // Calcular la cantidad de segmentos separados por tuberías
        char *segmentos[size];
        int i = 1;
        segmentos[0] = strtok(comando, "|"); // Dividir el comando en segmentos separados por tuberías
        
        while (i < size) {
            segmentos[i] = strtok(NULL, "|");
            i++;
        }

        int pipefd[2]; 
        pipe(pipefd); // Crear una tubería

        // Ejecutar cada segmento de la tubería
        for (i = 0; i < size; i++) {
            int entrada = (i == 0) ? STDIN_FILENO : pipefd[0]; // Primera entrada es la entrada estándar
            int salida = (i == size-1) ? STDOUT_FILENO : pipefd[1]; // Última salida es la salida estándar
            
            ejecutarComando(segmentos[i], entrada, salida); // Ejecutar el segmento actual
            
            // Cerrar los extremos de la tubería que ya no se necesitan
            if (entrada != STDIN_FILENO) close(entrada);
            if (salida != STDOUT_FILENO) close(salida);
        }

        // Esperar a que todos los procesos hijos finalicen
        for (i = 0; i < size; i++) {
            wait(NULL);
        }
    }

    return 0;
}

// Función que ejecuta un comando en un proceso hijo
void ejecutarComando(char *comando, int entrada, int salida) {
    pid_t pid = fork(); // Crear un proceso hijo

    if (pid == -1) {
        perror("Error al crear el proceso hijo"); // Manejo de error en caso de fallo en la bifurcación
    } else if (pid == 0) { // Código que ejecuta el proceso hijo
        
        // Redireccionar entrada estándar si es necesario
        if (entrada != STDIN_FILENO) {
            dup2(entrada, STDIN_FILENO);
            close(entrada);
        }

        // Redireccionar salida estándar si es necesario
        if (salida != STDOUT_FILENO) {
            dup2(salida, STDOUT_FILENO);
            close(salida);
        }
        
        // Separar el comando en argumentos
        char *args[TAM];
        int i = 0;
        char *token = strtok(comando, " ");
        while (token != NULL) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL; // Terminar la lista de argumentos con NULL
        
        execvp(args[0], args); // Ejecutar el comando usando execvp
        perror("Error ejecutando el comando"); // Manejo de error si el comando falla
        exit(EXIT_FAILURE);        
    }
}

// Función que cuenta la cantidad de tuberías '|' en el comando ingresado
int totalTuberias(const char * comando) {
    int i = 0;
    for (; *comando; comando++)
        if (*comando == '|') i++; // Contar cuántos caracteres '|' hay en el comando
    return i;
}
