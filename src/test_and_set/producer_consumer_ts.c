#include<stdlib.h>
#include<stdio.h>
#include<stdint.h>
#include "test_and_set.c"
#include<pthread.h>
#define N 8
#define SIZE 1024
int buffer[N];
int isEmpty[N];// array to know which case of the buffer is full
int cons=0;// number of data already consumed
int prod=0;// number of data already produceed
int sem_empty;// semaphore, val = nbr of empty case
int sem_full;// semaphore, val = nbr of not empty case
int mutexID;// buffer's mutex
void work(){}

void* producer(void* param){
    while(1){
        while(rand()>RAND_MAX/100);
        int a=rand()-rand();
        sem_wait(sem_empty); //Wait to fill an empty case
        mutex_lock(mutexID);
        if(prod>=SIZE) {
            mutex_unlock(mutexID);
            break;
        }
        int i=0;
        while(!isEmpty[i]) i++;//find an empty place
        buffer[i]=a;
        isEmpty[i]=0;
        prod++;
        mutex_unlock(mutexID);
        sem_post(sem_full);// say to consumers that one more case is full
    }
    //pthread_mutex_unlock(&mutex);//unlock the buffer because it wasn't close because of the break
    sem_post(sem_empty);//awake threads that are waiting (they will quite boucle because prod=SIZE )
    sem_post(sem_full);// all have been produce so we can awake all read threads 
    // if we don't do that there will be only 1024 post on full and so no one consumer thread will finish
    return NULL;
}
void *consumer(void *param){
    while(1){
        sem_wait(sem_full);//wait a full case
        mutex_lock(mutexID);
        if(cons>=SIZE) {
            mutex_unlock(mutexID);
            break;
        }
        int i=0;
        while(isEmpty[i]) i++;//find a full case
        isEmpty[i]=1;
        int a=buffer[i];
        cons++;
        mutex_unlock(mutexID);
        sem_post(sem_empty);// say to producers that one more case is empty
        while(rand()>RAND_MAX/100);
    }
    sem_post(sem_full);//awake threads that are waiting (they will quite boucle because cons=SIZE )
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
    sem_full=sem_init(0);
    sem_empty=sem_init(N);
    mutexID=mutex_init();
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
    sem_destroy(sem_full);
    sem_destroy(sem_empty);
    mutex_destroy(mutexID);
    return 0;
}