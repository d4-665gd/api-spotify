#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 5

int turno= 0; // (global) declarar variable compartida en memoria
pthread_mutex_t mutex;

void *funcion_hilo(void *arg){
    int id = *(int*)arg;//local

    for(int i=0;i<NUM_THREADS;i++){
        pthread_mutex_lock(&mutex); //comienza seccion critica
            if(turno==id){
                 printf("Hilo %d ejecutando iteración %d\n",id,i+1);
                turno = 1-id;
                }
        pthread_mutex_unlock(&mutex);//termina
        usleep(100000);
    }
    return NULL;
}
//prog multihilo tiene condicion de carrera lo que afectan resultados esperados
//en las zonas criticas se tienen operaciones atomicas donde solo un hilo puede actuar
int main(){
  pthread_t h1, h2;//arreglo de hilos
  int id1 =0, id2=1;
  pthread_mutex_init(&mutex,NULL);   
  
  pthread_create(&h1,NULL,funcion_hilo,&id1);
  pthread_create(&h2,NULL,funcion_hilo,&id2);

  pthread_join(h1,NULL);
  pthread_join(h2,NULL);

  pthread_mutex_destroy(&mutex);

    printf("Ejecución finalizada \n");        
    
    return 0;
}