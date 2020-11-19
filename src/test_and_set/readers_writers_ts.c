#include<stdlib.h>
#include<stdio.h>
#include<stdint.h>
#include "test_and_set.c"
#include <pthread.h>
#include <time.h>

int w_sem; //semaphore for the writers
int r_sem; //semaphore for the readers
int mutex_writersCount; //mutex for writersCount
int mutex_readerCount; //mutex for readersCount
int z;
int writersCount = 0; //number of writers
int readersCount = 0; //number of readers

void write(){}

void read(){}

void* writer(void* params){
    for(int i=0; i<640; i++){
        mutex_lock(mutex_writersCount);
        writersCount++;
        if(writersCount==1){ //first writer
            sem_wait(r_sem); //wait for the readers to finish reading
        }
        mutex_unlock(mutex_writersCount);

        sem_wait(w_sem);
        write();
        sem_post(w_sem);

        mutex_unlock(mutex_writersCount);
        writersCount--;
        if(writersCount==0){ //last writter
            sem_post(r_sem);
        }
        mutex_unlock(mutex_writersCount);
        while(rand()>RAND_MAX/1000);
    }
}

void* reader(void* params){
    for(int i=0; i<2560; i++){
        mutex_lock(z);
        sem_wait(r_sem);
        mutex_lock(mutex_readerCount);
        readersCount++;
        if(readersCount==1){ //first reader
            sem_wait(w_sem); //wait for the writers to finish writing
        }
        mutex_unlock(mutex_readerCount);
        sem_post(r_sem);
        mutex_unlock(z);
        read();

        mutex_lock(mutex_readerCount);
        readersCount--;
        if(readersCount==0){ //last reader
            sem_post(w_sem);
        }
        mutex_unlock(mutex_readerCount);
        while(rand()>RAND_MAX/1000);
    }
}

int main(int argc, char const *argv[])
{
    int nb_w = atoi(argv[1]); //number of writers
    int nb_r = atoi(argv[2]); //number of readers
    pthread_t threads_w[nb_w];
    pthread_t threads_r[nb_r];
    w_sem=sem_init(1);
    r_sem=sem_init(1);
    mutex_readerCount=mutex_init();
    mutex_writersCount=mutex_init();
    z=mutex_init();
    for (int i = 0; i <nb_w; i++)
    {
        pthread_create(&threads_w[i], NULL, &writer, NULL);
    }
    for (int i = 0; i <nb_r; i++)
    {
        pthread_create(&threads_r[i], NULL, &reader, NULL);
    }
        for (int i = 0; i <nb_w; i++)
    {
        pthread_join(threads_w[i], NULL);
    }
    for (int i = 0; i <nb_r; i++)
    {
        pthread_join(threads_r[i], NULL);
    }
    sem_destroy(w_sem);
    sem_destroy(r_sem);
    mutex_destroy(mutex_readerCount);
    mutex_destroy(mutex_writersCount);
    mutex_destroy(z);
    return 0;
}