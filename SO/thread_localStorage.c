#include <threads.h>
#include <stdio.h>
_Thread_local int thread_local_var = 0;
int thread_function(void *arg) {
thread_local_var = (int)(long)arg;
printf("Thread %ld: thread_local_var = %d\n", (long)arg,thread_local_var);
return 0;
}//si los hilos requieren almacenamiento exclusivo
//variables exclusivas incompartibles
int main() {
thrd_t thread1, thread2;
thrd_create(&thread1, thread_function, (void *)1);
thrd_create(&thread2, thread_function, (void *)2);
thrd_join(thread1, NULL);
thrd_join(thread2, NULL);
return 0;
}