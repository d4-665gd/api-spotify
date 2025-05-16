#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define HIJOS 5
#define NIETOS 5

int main() {
    pid_t pid;

    for (int i = 0; i < HIJOS; i++) {
        pid = fork();
        if (pid < 0) {
            perror("fork hijo");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Proceso hijo
            printf("→ Hijo PID: %d | Padre PID: %d\n", getpid(), getppid());

            for (int j = 0; j < NIETOS; j++) {
                pid_t pid_nieto = fork();
                if (pid_nieto < 0) {
                    perror("fork nieto");
                    exit(EXIT_FAILURE);
                } else if (pid_nieto == 0) {
                    printf("    → Nieto PID: %d | Padre PID: %d\n", getpid(), getppid());
                    exit(0); // Nieto termina
                } else {
                    waitpid(pid_nieto, NULL, 0); // Esperar al nieto
                }
            }

            exit(0); // Hijo termina después de crear nietos
        } else {
            waitpid(pid, NULL, 0); // Padre espera al hijo
        }
    }

    printf("Proceso padre original (PID: %d) terminó.\n", getpid());
    return 0;
}
