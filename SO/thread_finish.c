#include <threads.h>
#include <stdio.h>
int thread_function(void *arg) {
printf("Thread running\n");
thrd_exit(0);
}
int main() {
thrd_t thread;
if (thrd_create(&thread, thread_function, NULL) != thrd_success) {
fprintf(stderr, "Error creating thread\n");
return 1;
}
thrd_join(thread, NULL);
return 0;
}