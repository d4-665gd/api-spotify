
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define max_comands 10
#define max_argums 100
#define max_lineas 1024

void ejecutarComando(char* comando, char** comandos, int* conta) {
    char* segmentos = strtok(comando, "|");
    while (segmentos != NULL && *conta < max_comands) {
        comandos[(*conta)++] = segmentos;
        segmentos = strtok(NULL, "|");
    }
}

void totalTuberias(char* comando, char** args) {
    char* segmentos = strtok(comando, " ");
    int i = 0;
    while (segmentos != NULL && i < max_argums - 1) {
        args[i++] = segmentos;
        segmentos = strtok(NULL, " ");
    }
    args[i] = NULL;
}

int main() {
    char line[max_lineas];
    char* comandos[max_comands];
    int pipe_fd[max_comands - 1][2];

    while (1) {
        printf("Team10@penguin:~$ ");
        fflush(stdout);

        if (!fgets(line, sizeof(line), stdin)) break;
        if (strcmp(line, "\n") == 0) continue;

        line[strcspn(line, "\n")] = 0;

        if (strcmp(line, "exit") == 0) {
            printf("Saliendo del shell...\n");
            break;
        }

        int num_comandos = 0;
        ejecutarComando(line, comandos, &num_comandos);

        for (int i = 0; i < num_comandos - 1; ++i)
            pipe(pipe_fd[i]);

        for (int i = 0; i < num_comandos; ++i) {
            pid_t pid = fork();
            if (pid == 0) {
                if (i > 0) {
                    dup2(pipe_fd[i - 1][0], STDIN_FILENO);
                }
                if (i < num_comandos - 1) {
                    dup2(pipe_fd[i][1], STDOUT_FILENO);
                }

                for (int j = 0; j < num_comandos - 1; ++j) {
                    close(pipe_fd[j][0]);
                    close(pipe_fd[j][1]);
                }

                char* args[max_argums];
                totalTuberias(comandos[i], args);
                execvp(args[0], args);
                perror("execvp");
                exit(EXIT_FAILURE);
            }
        }

        for (int i = 0; i < num_comandos - 1; ++i) {
            close(pipe_fd[i][0]);
            close(pipe_fd[i][1]);
        }

        for (int i = 0; i < num_comandos; ++i)
            wait(NULL);
    }

    return 0;
}
