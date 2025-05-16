#include <threads.h>
#include <stdio.h>

mtx_t mutex;
long shared_data = 0; // Corrijo también: "int long" -> "long"

int thread_function(void *arg) {
    printf("Thread %ld running... \n", (long)arg);
    for (long i = 0; i < 100000; ++i) {
        mtx_lock(&mutex);
        shared_data++;
        mtx_unlock(&mutex);
    } 
    //region critica: Parte del codigo del programa donde se accede al recurso compartido
    printf("Thread %ld ended with value: %ld \n", (long)arg, shared_data);
    thrd_exit(0);
}
//contencion de hilos: estructura secuencial no eficiente
int main() {
    thrd_t thread1, thread2;
    mtx_init(&mutex, mtx_plain); // Inicializar el mutex

    thrd_create(&thread1, thread_function, (void *)1);
    thrd_create(&thread2, thread_function, (void *)2);

    printf("Main running ..\n");
    for (long i = 0; i < 200000; ++i) {
        mtx_lock(&mutex);
        shared_data--;
        mtx_unlock(&mutex);
    }

    // Esperar que los threads terminen
    thrd_join(thread1, NULL);
    thrd_join(thread2, NULL);

    printf("Main ended with value: %ld \n", shared_data);

    mtx_destroy(&mutex); // Destruir el mutex
    return 0;
}
