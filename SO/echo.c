#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

#define PORT 8080
#define MAX_CONN 10
#define BUFFER_SIZE 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE];
    int connection_count = 0;

    // Crear el socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Configurar la dirección del servidor
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Vincular el socket a la dirección
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Escuchar conexiones entrantes
    if (listen(server_fd, MAX_CONN) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("Servidor escuchando en el puerto %d...\n", PORT);

    // Aceptar hasta MAX_CONN conexiones
    while (connection_count < MAX_CONN) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, 
                           (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        // Incrementar contador de conexiones
        connection_count++;

        // Obtener y mostrar la fecha del servidor
        time_t now = time(NULL);
        struct tm *t = localtime(&now);
        char server_time[100];//strftime - formato de fecha/tiempo
        strftime(server_time, sizeof(server_time), "%Y-%m-%d %H:%M:%S", t);
        printf("(%d) Fecha del servidor: %s\n", connection_count, server_time);

        // Leer la fecha enviada por el cliente
        memset(buffer, 0, BUFFER_SIZE);
        read(new_socket, buffer, BUFFER_SIZE);
        printf("(%d) Fecha del cliente: %s\n", connection_count, buffer);

        close(new_socket);
    }

    printf("Límite de 10 conexiones alcanzado. Cerrando servidor.\n");
    close(server_fd);
    return 0;
}
