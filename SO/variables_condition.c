#include <threads.h>
#include <stdio.h>
mtx_t mutex;
cnd_t cond;
int ready = 0;
int producer(void *arg) {
mtx_lock(&mutex);
ready = 1;//activa varabe
cnd_signal(&cond);//marca cambio
mtx_unlock(&mutex);//libera semaforo
return 0;
}
int consumer(void *arg) {
mtx_lock(&mutex);
while (!ready) {
cnd_wait(&cond, &mutex);
}
//se requieren 2 semaforos para maneho de procesos
printf("Consumer: ready = %d\n", ready);
mtx_unlock(&mutex);
return 0;
}
int main() {
thrd_t producer_thread, consumer_thread;
mtx_init(&mutex, mtx_plain);
cnd_init(&cond);
thrd_create(&producer_thread, producer, NULL);
thrd_create(&consumer_thread, consumer, NULL);
thrd_join(producer_thread, NULL);
thrd_join(consumer_thread, NULL);
mtx_destroy(&mutex);
cnd_destroy(&cond);
return 0;
}