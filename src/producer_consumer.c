#include<stdlib.h>
#include<stdio.h>
#include<stdint.h>
#include <semaphore.h>
#include <pthread.h>
#define N 8
#define SIZE 1024
int buffer[N];
int isEmpty[N];
int cons=0;
int prod=0;
sem_t empty;
sem_t full;
pthread_mutex_t mutex;
pthread_mutex_t a;
pthread_mutex_t b;

void work(){
    ;
    //while(rand()>10000);
}

void* producer(void* param){
    while(1){
        sem_wait(&empty);
        work();
        int a=rand()-rand();
        pthread_mutex_lock(&mutex);
        if(prod>=SIZE) break;
        int i=0;
        while(!isEmpty[i]) i++;
        buffer[i]=prod;
        isEmpty[i]=0;
        prod++;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
    pthread_mutex_unlock(&mutex);
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
    pthread_t thread_prod[3];
    pthread_t thread_cons[3];
    sem_init(&full,0,0);
    sem_init(&empty,0,N);
    pthread_mutex_init(&mutex,NULL);
    for (int i = 0; i <N ; ++i) {
        isEmpty[i]=1;
    }
    for (int i = 0; i < 3; i++)
    {
        pthread_create(&thread_prod[i],NULL,&producer,NULL);
    }
    for (int i = 0; i < 3; i++)
    {
        pthread_create(&thread_cons[i],NULL,&consumer,NULL);
    }
    printf("threads created\n");
    for (int i = 0; i < 3; i++)
    {
        pthread_join(thread_prod[i],NULL);
    }
    printf("Producers finished\n");
    for (int i = 0; i < 3; i++)
    {
        pthread_join(thread_cons[i],NULL);
    }
    printf("Consumers finished\n");
    return 0;
}