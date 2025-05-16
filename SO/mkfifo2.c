#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
    const char *queue_name = "/my_queue";
    mqd_t mq = mq_open(queue_name, O_CREAT | O_RDWR, 0666, NULL);
    if (mq == (mqd_t)-1) {
        perror("Error creating message queue");
        return 1;
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("Error forking process");
        return 1;
    }

    if (pid > 0) {
        // Padre: envía un mensaje al hijo
        const char *message = "Hello from parent";
        sleep(1); // Pequeño delay para asegurar que hijo esté listo para recibir
        if (mq_send(mq, message, strlen(message) + 1, 0) == -1) {
            perror("Error sending message");
            return 1;
        }
    } else {
        // Hijo: recibe y ejecuta el mensaje (aquí lo imprimimos)
        char buffer[1024];
        if (mq_receive(mq, buffer, sizeof(buffer), NULL) == -1) {
            perror("Error receiving message");
            return 1;
        }
        printf("Child received: %s\n", buffer);

        // Aquí podrías hacer algo más con el mensaje, como ejecutar un comando, por ejemplo:
        // system(buffer); // ⚠️ Úsalo con cuidado: ejecutar comandos puede ser peligroso
    }

    mq_close(mq);
    mq_unlink(queue_name); // Borra la cola de mensajes
    return 0;
}
