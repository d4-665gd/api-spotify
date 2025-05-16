#include <threads.h>
#include <stdio.h>
int thread_function(void *arg) {
int *value = (int *)arg;
printf("Thread running with value: %d\n", *value);
return 0;
}
int main() {
thrd_t thread;
int value = 42;
if (thrd_create(&thread, thread_function, &value) != thrd_success) {
fprintf(stderr, "Error creating thread\n");
return 1;
}
thrd_join(thread, NULL);
return 0;
}