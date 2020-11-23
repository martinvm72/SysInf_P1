#include<stdlib.h>
#include<stdio.h>
#include<stdint.h>
#include <semaphore.h>
#include <pthread.h>
#include <time.h>
#define N 8
#define SIZE 1024
int buffer[N];
int isEmpty[N];// array to know which case of the buffer is full
int cons=0;// number of data already consumed
int prod=0;// number of data already produceed
sem_t empty;// semaphore, val = nbr of empty case
sem_t full;// semaphore, val = nbr of not empty case
pthread_mutex_t mutex;// buffer's mutex
void work(){
    clock_t start=clock();
    while(rand()>RAND_MAX/10000);
}

void* producer(void* param){
    while(1){
        sem_wait(&empty); //Wait or fill an empty case
        work();
        int a=rand()-rand();
        pthread_mutex_lock(&mutex);
        if(prod>=SIZE) break;
        int i=0;
        while(!isEmpty[i]) i++;//find an empty place
        buffer[i]=prod;
        isEmpty[i]=0;
        prod++;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);// say to consumer than one more case is full
    }
    pthread_mutex_unlock(&mutex);//unlock the buffer because it wasn't close because of the break
    sem_post(&full);
    return NULL;
}
void *consumer(void *param){
    while(1){
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        if(cons>=SIZE) break;
        int i=0;
        while(isEmpty[i]){
            i++;
        }
        isEmpty[i]=1;
        int a=buffer[i];
        cons++;
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
        work();
    }
    pthread_mutex_unlock(&mutex);
    sem_post(&full);
    return NULL;
}

int main(int argc, char const *argv[])
{
    //Create the number of threads requested
    int nbrProd=atoi(argv[1]); 
    int nbrCons=atoi(argv[2]);
    //printf("prod : %d   cons : %d\n",nbrProd,nbrCons);
    pthread_t thread_prod[nbrProd];
    pthread_t thread_cons[nbrCons];

    // Initialisation
    sem_init(&full,0,0);
    sem_init(&empty,0,N);
    pthread_mutex_init(&mutex,NULL);
    for (int i = 0; i <N ; ++i) {
        isEmpty[i]=1;
    }

    //Start threads(producers then consumers)
    for (int i = 0; i < nbrProd; i++)
    {
        pthread_create(&thread_prod[i],NULL,&producer,NULL);
    }
    for (int i = 0; i < nbrCons; i++)
    {
        pthread_create(&thread_cons[i],NULL,&consumer,NULL);
    }

    //Wait that threads have finished
    for (int i = 0; i < nbrProd; i++)
    {
        pthread_join(thread_prod[i],NULL);
    }
    for (int i = 0; i < nbrCons; i++)
    {
        pthread_join(thread_cons[i],NULL);
    }
    return 0;
}