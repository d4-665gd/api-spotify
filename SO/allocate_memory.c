#include <stdio.h>
#include <stdlib.h>

int main(){
    unsigned long n = 0;
    while(malloc(1 << 20) != NULL){
        printf("Got %ldMB", ++n);
    }
    fprintf(stderr, "\n\n malloc failure after %ld MB \n\n",n);
    return 0;
}