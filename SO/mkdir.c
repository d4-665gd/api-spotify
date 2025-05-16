/**
 * Equipo: 10
 * Programa:
 * David Loyola Montaño 
 * Carlos Ernesto Marcial Olmedo
 */

 #include <stdio.h>      
 #include <sys/types.h>  // Tipos de datos para llamadas al sistema
 #include <sys/stat.h>   // Manejo de atributos de archivos y directorios
 #include <string.h>     
 #include <unistd.h>     
 #include <stdlib.h>     
 
 #define PERMISOS_PREDETERMINADOS 0777  // Permisos predeterminados si no se especifican

// Prototipos de funciones
 int esModificador(const char *modificador); // Determina si un argumento es un modificador válido
 int crearDirectorio(const char *nombreDirectorio, const char *modificador, mode_t permisos); // Crea un directorio con permisos personalizados
 int cambiarDirectorio(const char *nombreDirectorio); // Cambia el directorio actual al especificado
 int directorioExiste(const char *nombreDirectorio); // Verifica la existencia de un directorio
 int contarSubdirectorios(const char *ruta); // Cuenta cuántos subdirectorios existen en una ruta


int main(int argc, char *argv[]) {
    char ruta[256]; // Variable para almacenar la ruta del directorio
    mode_t permisos = PERMISOS_PREDETERMINADOS; // Valor por defecto de permisos

     // Verificación de argumentos y ayuda
     if (argc < 2 || strcmp(argv[1], "--help") == 0) {
        // Mensajes de ayuda si no se dan argumentos válidos
         fprintf(stderr, "Uso: %s <ruta_base>\n", argv[0]); 
         fprintf(stderr, "Uso: %s <ruta_base> <ruta_base> <ruta_base> \n", argv[0]);
         fprintf(stderr, "Uso: %s <ruta_base>/<ruta_subcarpetas>\n", argv[0]);
         fprintf(stderr, "Uso: %s -p <ruta_base>/<ruta_subcarpetas>\n", argv[0]);
         fprintf(stderr, "Uso: %s -v <nombre>\n", argv[0]);
         fprintf(stderr, "Uso: %s -vp <ruta_base>/<ruta_subcarpetas>\n", argv[0]);
         fprintf(stderr, "Uso: %s -m <permisos> <nombre>\n", argv[0]);
         fprintf(stderr, "Uso: %s --help\n", argv[0]); // Muestra todas las opciones disponibles
         return 1; // Código de error por falta de argumentos
     }
    
     // Procesamiento de modificadores
    if (strcmp(argv[1], "-m") == 0) { // Si se usa la opción para modificar permisos
        if (argc < 4) {
            fprintf(stderr, "Error: Se debe proporcionar un valor de permisos y un nombre de directorio.\n");
            return 1;
        }
        permisos = strtol(argv[2], NULL, 8);  // Convierte permisos de cadena a número octal
        strncpy(ruta, argv[3], sizeof(ruta) - 1);
    } else if (esModificador(argv[1])==0) { // Si el primer argumento es un modificador válido
        if (argc < 3) {
            fprintf(stderr, "Error: Se esperaba una ruta después de '%s'.\n", argv[2]);
            return 1;
        }
        strncpy(ruta, argv[2], sizeof(ruta) - 1);
    } else {
        strncpy(ruta, argv[1], sizeof(ruta) - 1);
        if (argc > 2) { // Si hay uno o múltiples directorios, los crea individualmente 
            for (int i = 1; i < argc; i++) { 
                crearDirectorio(argv[i], "null", permisos);
            }
            return 0; // Finalización exitosa del programa
        }
    }

    ruta[sizeof(ruta) - 1] = '\0'; // Asegura que la ruta esté correctamente terminada

     // Creación de directorios en caso de múltiples subdirectorios o modificadores
    if (strchr(ruta, '/') == NULL) {  // Si la ruta no contiene subdirectorios
        crearDirectorio(ruta, argv[1], permisos);
    } else {  // Si la ruta contiene subdirectorios
        char rutaAux[256];
        strcpy(rutaAux, ruta);
        int totalSubdirectorios = contarSubdirectorios(rutaAux);
        char *token = strtok(ruta, "/"); // Divide la ruta en segmentos usando "/"
        int contador = 0;

        while (token != NULL) { // Itera por cada subdirectorio en la ruta
            if ((directorioExiste(token)==1 || contador == totalSubdirectorios || strcmp(argv[1],"-vp") == 0  || strcmp(argv[1],"-p") == 0)&& strcmp(argv[1],"-v") != 0) {
                if(directorioExiste(token)!=1){ // Si el directorio ya existe se omite su creacion
                    crearDirectorio(token, argv[1], permisos); // Crea el directorio si es válido
                }
            } else {
                printf("mkdir: cannot create directory ‘%s’: No such file or directory.\n", argv[1]);
                return 1;
            }
            cambiarDirectorio(token); // Navega al siguiente subdirectorio
            token = strtok(NULL, "/");
            contador++;
        }
    }

    return 0; // Finalización exitosa del programa
}

// Función para verificar si el argumento es un modificador válido
int esModificador(const char *modificador){
     if(strcmp(modificador,"-v") == 0 || strcmp(modificador,"-vp") == 0 || strcmp(modificador, "-p") == 0)
       return 0;
    return -1;
}


// Función para crear un directorio con permisos especificados
int crearDirectorio(const char *nombreDirectorio, const char *modificador, mode_t permisos) {
    if (mkdir(nombreDirectorio, permisos) == 0) { // Intenta crear el directorio con los permisos especificados
        if(strcmp(modificador,"-vp")== 0 || strcmp(modificador,"-v") == 0){
            printf("mkdir: created directory '%s'\n", nombreDirectorio);
        }
        return 0;
    } else {
        perror("mkdir"); // En caso de error, imprime el motivo
        return -1;
    }
}

// Función para cambiar al directorio especificado
int cambiarDirectorio(const char *nombreDirectorio) {
    if (chdir(nombreDirectorio) != 0) { // Intenta cambiar al nuevo directorio
        perror("chdir"); // En caso de error, imprime el motivo
        return -1;
    }
    return 0;
}

// Función para verificar si un directorio existe
int directorioExiste(const char *nombreDirectorio) {
    struct stat info;
    return stat(nombreDirectorio, &info) == 0 && S_ISDIR(info.st_mode);/// Verifica si el directorio existe
}

// Función para contar cuántos subdirectorios existen
int contarSubdirectorios(const char *ruta) {
    int contador = 0;
    for (; *ruta; ruta++)
        if (*ruta == '/') contador++; // Cuenta cuántos caracteres '/' existen en la ruta
    return contador;
}
