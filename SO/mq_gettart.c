#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    mqd_t mq;
    struct mq_attr attr;

    /* Abrir la cola de mensajes */
    mq = mq_open("/mi_cola", O_RDONLY);
    if (mq == (mqd_t) -1) {
        perror("Error al abrir la cola de mensajes");
        exit(EXIT_FAILURE);
    }

    /* Obtener los atributos de la cola de mensajes */
    if (mq_getattr(mq, &attr) == -1) {
        perror("Error al obtener atributos de la cola de mensajes");
        exit(EXIT_FAILURE);
    }

    /* Mostrar los atributos */
    printf("Flags: %ld\n", attr.mq_flags);
    printf("Máximo número de mensajes: %ld\n", attr.mq_maxmsg);
    printf("Tamaño máximo de mensaje: %ld bytes\n", attr.mq_msgsize);
    printf("Mensajes actuales en la cola: %ld\n", attr.mq_curmsgs);

    /* Cerrar la cola de mensajes */
    mq_close(mq);

    return 0;
}
