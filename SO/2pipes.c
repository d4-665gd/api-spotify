/*Comunicar 3 procesos con 2 pipes*/
//dup2(arg1,arg2) duplica arg1 a arg2
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#define READ_END 0
#define WRITE_END 1

int main(int argc, char* argv[]){
  int fd1[2],fd2[2];
  int status,pid;

  pipe(fd1);

  pid= fork();
    if(pid == 0){ //hijo
        close(fd1[READ_END]);    //cerrar extremo no necesario
        dup2(fd1[WRITE_END],STDOUT_FILENO);

        execlp("/bin/ls","ls","-l",NULL);
    }  else{ //padre
        close(fd1[WRITE_END]);

        pipe(fd2);
        pid = fork();

        if(pid == 0){ //hijo
            close(fd2[READ_END]);    

            dup2(fd1[READ_END],STDIN_FILENO);
            close(fd1[READ_END]); 

            dup2(fd2[WRITE_END],STDOUT_FILENO);
            close(fd2[WRITE_END]);             
    
            execlp("/bin/grep","grep","u",NULL);
        } else {
            close(fd1[READ_END]); 
            close(fd2[WRITE_END]); 

            pid = fork();

            if(pid == 0){

                dup2(fd2[READ_END],STDIN_FILENO);
               close(fd2[READ_END]); 

               execlp("/usr/bin/wc","wc","-l",NULL);

            }  //checar api de spotify
        }

    }

    close(fd2[READ_END]);

    wait(&status);
    wait(&status);
    wait(&status);
    return 0;
}