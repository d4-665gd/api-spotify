#include <threads.h>
#include <stdio.h>
mtx_t mutex;
int shared_data = 0;
//checar clasrrom para 2 ejemplos de semaforos sin nombre
int thread_function(void *arg) {
mtx_lock(&mutex);
shared_data++;
printf("Thread %ld: shared_data = %d\n", (long)arg, shared_data);
mtx_unlock(&mutex);
return 0;
}

int main() {
thrd_t thread1, thread2;
mtx_init(&mutex, mtx_plain);
thrd_create(&thread1, thread_function, (void *)1);
thrd_create(&thread2, thread_function, (void *)2);
thrd_join(thread1, NULL);
thrd_join(thread2, NULL);
mtx_destroy(&mutex);
return 0;
}