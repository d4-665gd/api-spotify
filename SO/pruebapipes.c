#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_CMD 10       // máximo número de comandos en una línea
#define MAX_ARGS 100     // máximo número de argumentos por comando
#define MAX_LINE 1024    // tamaño máximo de la línea de entrada

void parse_command(char* input, char** commands, int* count) {
    char* token = strtok(input, "|");
    while (token != NULL && *count < MAX_CMD) {
        commands[(*count)++] = token;
        token = strtok(NULL, "|");
    }
}

void parse_args(char* command, char** args) {
    char* token = strtok(command, " \t\n");
    int i = 0;
    while (token != NULL && i < MAX_ARGS - 1) {
        args[i++] = token;
        token = strtok(NULL, " \t\n");
    }
    args[i] = NULL;
}

int main() {
    char line[MAX_LINE];
    char* commands[MAX_CMD];
    int pipe_fd[MAX_CMD - 1][2];

    while (1) {
        printf("minishell$ ");
        fflush(stdout);

        if (!fgets(line, sizeof(line), stdin)) break;

line[strcspn(line, "\n")] = 0;

// Ahora sí comparamos correctamente
if (strcmp(line, "") == 0) continue;
if (strcmp(line, "exit") == 0) break;
        


        int num_cmds = 0;
        parse_command(line, commands, &num_cmds);

        for (int i = 0; i < num_cmds - 1; ++i)
            pipe(pipe_fd[i]);

        for (int i = 0; i < num_cmds; ++i) {
            pid_t pid = fork();
            if (pid == 0) {
                // Redirección de entrada
                if (i > 0) {
                    dup2(pipe_fd[i - 1][0], STDIN_FILENO);
                }

                // Redirección de salida
                if (i < num_cmds - 1) {
                    dup2(pipe_fd[i][1], STDOUT_FILENO);
                }

                // Cerrar todos los extremos de pipe
                for (int j = 0; j < num_cmds - 1; ++j) {
                    close(pipe_fd[j][0]);
                    close(pipe_fd[j][1]);
                }

                // Parsear argumentos y ejecutar
                char* args[MAX_ARGS];
                parse_args(commands[i], args);
                execvp(args[0], args);
                perror("execvp"); // si falla
                exit(EXIT_FAILURE);
            }
        }

        // Cerrar todos los extremos de pipe en el padre
        for (int i = 0; i < num_cmds - 1; ++i) {
            close(pipe_fd[i][0]);
            close(pipe_fd[i][1]);
        }

        // Esperar a todos los hijos
        for (int i = 0; i < num_cmds; ++i)
            wait(NULL);
    }

    return 0;
}
