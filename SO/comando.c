#include <fcntl.h> 
#include <stdio.h> 
#include <unistd.h> 
#include <string.h> 
#define TAM 16384 // Tamaño del buffer

// Función para reemplazar todas las ocurrencias de 'word' por 'word2' en 'buffer'
void replace_word(char *buffer, char *word, char *word2) {
    char *First = buffer;      // Inicializar el puntero 'First' apuntando al inicio del buffer
    char *resultado;           // Puntero para almacenar la ubicación de la palabra a reemplazar
    char aux[TAM];             // Buffer auxiliar para almacenar el texto modificado
    int i = 0, j = 0, k = 0, cambios = 0;  // Contadores para gestionar las posiciones y el número de cambios
    resultado = strstr(First, word);  // Buscar la primera ocurrencia de 'word' en el buffer
    
    while (resultado != NULL) {   // Mientras haya una ocurrencia de la palabra a reemplazar
        cambios++;                // Incrementar el contador de cambios
        i = resultado - buffer;  // Calcular la posición de la palabra en el buffer original

        // Copiar la parte del buffer que está antes de la palabra encontrada
        strncpy(aux + j, buffer + k, i - k);  
        j += i - k;  // Actualizar la posición 'j' en el buffer auxiliar

        // Copiar la palabra de reemplazo en el buffer auxiliar
        strncpy(aux + j, word2, strlen(word2));
        j += strlen(word2);  // Avanzar la posición 'j' en el buffer auxiliar

        k = i + strlen(word);  // Actualizar la posición 'k' para continuar buscando después de la palabra reemplazada
        resultado = strstr(buffer + k, word);  // Buscar la siguiente ocurrencia de la palabra en el buffer restante
    }
    
    // Copiar el resto del buffer después de la última palabra reemplazada
    strcpy(aux + j, buffer + k);  

    // Copiar el contenido del buffer auxiliar de vuelta al buffer original
    strcpy(buffer, aux);

    // Imprimir el texto modificado
    if (cambios==0){
        printf("La palabra %s no se encuentra en el archivo\n",word);
    }
}

int main(int argv, char * argc[]){
    int original_archivo, destino_archivo; // Descriptores de archivo para el archivo original y el destino
    char buffer[TAM]; // Buffer para almacenar el contenido del archivo

    // Abre el archivo original en modo de solo lectura
    original_archivo = open(argc[3], O_RDONLY);

    // Verifica si la apertura del archivo fue exitosa
    if (original_archivo == -1) {
        perror("Error al ejecutar comando snr\n"); // Imprime un mensaje de error si falla
        return 1; // Sale del programa con código de error
    } else {
        // Lee el contenido del archivo original al buffer
        read(original_archivo, buffer, TAM);
    }

    // Llama a la función para reemplazar la palabra especificada
    replace_word(buffer, argc[1], argc[2]);

    // Abre el archivo destino en modo de escritura, creación (si no existe) y truncamiento
    destino_archivo = open(argc[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);

    // Verifica si la apertura del archivo destino fue exitosa
    if (destino_archivo == -1) {
        perror("Error al abrir el archivo destino\n"); // Imprime un mensaje de error si falla
        return 1; // Sale del programa con código de error
    } else {
        // Escribe el contenido modificado del buffer en el archivo destino
        ssize_t bytes_escritos = write(destino_archivo, buffer, strlen(buffer));
        if (bytes_escritos == -1) {
            perror("Error al escribir en el archivo\n"); // Imprime un mensaje de error si falla la escritura
        }
    }

    // Cierra los descriptores de archivo
    close(original_archivo);
    close(destino_archivo);

    return 0; // Sale del programa con código de éxito
}