#include<stdlib.h>
#include<stdio.h>
#include<stdint.h>
#include <semaphore.h>
#include <pthread.h>
#include<sys/time.h>
#define N 8
#define SIZE 1024
int buffer[N];
int isFull[N];
int prodCount;
int consCount;
sem_t full;
sem_t empty;
pthread_mutex_t mutex;

void work(){
    while(rand()>RAND_MAX/10000);
}

void* producer(void* param){
    while(1){
        work();
        int prod=rand()-rand();
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        if(prodCount>=SIZE){
            pthread_mutex_unlock(&mutex);
            break;
        }
        int i=0;
        while(isFull[i])i++;
        isFull[i]=1;
        buffer[i]=prod;
        prodCount++;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
    sem_post(&empty);
    sem_post(&full);
    return NULL;
}
void* consumer(void* param){
    while(1){
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        if(consCount>=SIZE){
            pthread_mutex_unlock(&mutex);
            break;
        }
        int i=0;
        while(!isFull[i])i++;
        isFull[i]=0;
        int cons=buffer[i];
        consCount++;
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
        work();
    }
    sem_post(&full);
    return NULL;
}

int main(int argc, char const *argv[])
{
    int nbrProd=atoi(argv[1]); 
    int nbrCons=atoi(argv[2]);
    sem_init(&empty,0,N);
    sem_init(&full,0,0);
    pthread_mutex_init(&mutex,NULL);
    pthread_t thread_prod[nbrProd];
    pthread_t thread_cons[nbrCons];
    for(int i=0;i<nbrProd;i++){
        pthread_create(&thread_prod[i],NULL,&producer,NULL);
    }
    for(int i=0;i<nbrCons;i++){
        pthread_create(&thread_cons[i],NULL,&consumer,NULL);
    }
    for(int i=0;i<nbrProd;i++){
        pthread_join(thread_prod[i],NULL);
    }
    for(int i=0;i<nbrCons;i++){
        pthread_join(thread_cons[i],NULL);
    }
    return 0;
}
