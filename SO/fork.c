#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

#define TIMES 10

int main(int argc, char *argv[]) {
    pid_t cpid; int status;
   cpid = fork(); // Create a new process

   if (cpid == -1) {
perror("fork");
exit  (EXIT_FAILURE);
} 


if (cpid == 0) {
    int i;
    
    for(i=0;i< TIMES; i++){
printf("Proceso padre:  %d\n", i);
}
exit (EXIT_SUCCESS);
 
} else if (cpid == wait(&status)){
    int i;
    for(i=0;i< TIMES; i++){
        printf("Proceso hijo:  %d\n", i);
         }
         exit (EXIT_SUCCESS);
   
}
return 0;
}