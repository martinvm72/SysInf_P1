#include<stdlib.h>
#include<stdio.h>
#include<stdint.h>
#include <semaphore.h>
#include <pthread.h>
#include<sys/time.h>
#define N 96
#define SIZE 1024
int buffer[N];
int isEmpty[N];// array to know which case of the buffer is full
int cons=0;// number of data already consumed
int prod=0;// number of data already produceed
sem_t empty;// semaphore, val = nbr of empty case
sem_t full;// semaphore, val = nbr of not empty case
pthread_mutex_t mutex;// buffer's mutex

void* producer(void* param){
    while(1){
        while(rand()>RAND_MAX/1000);
        int a=rand()-rand();
        sem_wait(&empty); //Wait to fill an empty case
        pthread_mutex_lock(&mutex);
        if(prod>=SIZE) {
            pthread_mutex_unlock(&mutex);
            break;
        }
        int i=0;
        while(!isEmpty[i]) i++;//find an empty place
        buffer[i]=a;
        isEmpty[i]=0;
        prod++;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);// say to consumers that one more case is full
    }
    //pthread_mutex_unlock(&mutex);//unlock the buffer because it wasn't close because of the break
    sem_post(&empty);//awake threads that are waiting (they will quite boucle because prod=SIZE )
    sem_post(&full);// all have been produce so we can awake all read threads 
    // if we don't do that there will be only 1024 post on full and so no one consumer thread will finish
    return NULL;
}
void *consumer(void *param){
    while(1){
        sem_wait(&full);//wait a full case
        pthread_mutex_lock(&mutex);
        if(cons>=SIZE) {
            pthread_mutex_unlock(&mutex);
            break;
        }
        int i=0;
        while(isEmpty[i]) i++;//find a full case
        isEmpty[i]=1;
        int a=buffer[i];
        cons++;
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);// say to producers that one more case is empty
        while(rand()>RAND_MAX/1000);
    }
    sem_post(&full);//awake threads that are waiting (they will quite boucle because cons=SIZE )
    return NULL;
}

int main(int argc, char const *argv[])
{
    //Create the number of threads requested
    int nbrProd=atoi(argv[1]); 
    int nbrCons=atoi(argv[2]);
    
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
        //printf("prod\n");
    }
    //sem_post(&full);//(another way to solve the problem)
    for (int i = 0; i < nbrCons; i++)
    {
        pthread_join(thread_cons[i],NULL);
        //printf("cons\n");
    }
    sem_destroy(&full);
    sem_destroy(&empty);
    pthread_mutex_destroy(&mutex);
    return 0;
}