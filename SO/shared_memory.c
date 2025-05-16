#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
int shmid = shmget(IPC_PRIVATE, 1024, 0666 | IPC_CREAT);
if (shmid == -1) {
perror("Error creating shared memory segment");
return 1;
}
pid_t pid = fork();
if (pid == -1) {
perror("Error forking process");
return 1;
}
if (pid == 0) {
// Child process: write to shared memory
char *shmaddr = (char *)shmat(shmid, NULL, 0);
if (shmaddr == (char *)-1) {
perror("Error attaching shared memory");
return 1;
}
strcpy(shmaddr, "Hello from child");
shmdt(shmaddr);
} else {
// Parent process: read from shared memory
char *shmaddr = (char *)shmat(shmid, NULL, 0);
if (shmaddr == (char *)-1) {
perror("Error attaching shared memory");
return 1;
}
printf("Received: %s\n", shmaddr);
shmdt(shmaddr);
shmctl(shmid, IPC_RMID, NULL); // Remove the shared memory segment
}
return 0;
}
