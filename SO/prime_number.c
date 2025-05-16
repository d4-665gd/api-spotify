#include <threads.h>
#include <stdio.h>
#include <stdbool.h>
#define NUM_THREADS 4
#define RANGE 100000
mtx_t mutex;
int prime_count = 0;
bool is_prime(int n) {
if (n < 2) return false;
for (int i = 2; i * i <= n; i++) {
if (n % i == 0) return false;
}
return true;
}
int thread_function(void *arg) {
int start = (int)(long)arg * (RANGE / NUM_THREADS);
int end = start + (RANGE / NUM_THREADS);
for (int i = start; i < end; i++) {
if (is_prime(i)) {
mtx_lock(&mutex);
prime_count++;
mtx_unlock(&mutex);
}//estrict alternancia entre hilo padre e hijo
}//Intercalación: si un tiempo para un proceso es mas grande 
//que otro, realizas una parte de un proceso y continuas con otro y
//luego con el primero y asi 
return 0;
}
int main() {
thrd_t threads[NUM_THREADS];
mtx_init(&mutex, mtx_plain);
for (int i = 0; i < NUM_THREADS; i++) {
thrd_create(&threads[i], thread_function, (void *)(long)i);
}
for (int i = 0; i < NUM_THREADS; i++) {
thrd_join(threads[i], NULL);
}
mtx_destroy(&mutex);
printf("Total prime numbers: %d\n", prime_count);
return 0;
}