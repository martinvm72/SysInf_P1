#include<stdlib.h>
#include<stdio.h>
#include<stdint.h>
#include <semaphore.h>
#include <pthread.h>
#include <sys/time.h>

sem_t w_sem; //semaphore for the writers
sem_t r_sem; //semaphore for the readers
pthread_mutex_t mutex_writersCount; //mutex for writersCount
pthread_mutex_t mutex_readerCount; //mutex for readersCount
pthread_mutex_t z;
int writersCount = 0; //number of writers
int readersCount = 0; //number of readers
int nbrRead = 0;
int nbrWrite = 0;
pthread_mutex_t mutex_nbrRead;
pthread_mutex_t mutex_nbrWrite;
int size = 0;
int TMP[640+2560];
pthread_mutex_t mutex_TMP;
long start, mid, end;

struct timeval tv;

void write(){
    /*pthread_mutex_lock(&mutex_TMP);
    TMP[size] = 0;
    size++;
    pthread_mutex_unlock(&mutex_TMP);*/
}
void read(){
    /*pthread_mutex_lock(&mutex_TMP);
    TMP[size] = 1;
    size++;
    pthread_mutex_unlock(&mutex_TMP);*/
}

void* writer(void* params){
    while(1){
        pthread_mutex_lock(&mutex_nbrWrite);
        if(nbrWrite>=640){
            pthread_mutex_unlock(&mutex_nbrWrite);
            break;
        }
        nbrWrite++;
        pthread_mutex_unlock(&mutex_nbrWrite);
        while(rand()>RAND_MAX/10000);
        pthread_mutex_lock(&mutex_writersCount);
        writersCount++;
        if(writersCount==1){ //first writer
            sem_wait(&r_sem); //wait for the readers to finish reading
        }
        pthread_mutex_unlock(&mutex_writersCount);
        sem_wait(&w_sem);
        write();
        sem_post(&w_sem);

        pthread_mutex_lock(&mutex_writersCount);
        writersCount--;
        if(writersCount==0){ //last writter
            sem_post(&r_sem);
        }
        pthread_mutex_unlock(&mutex_writersCount);
    }
    return NULL;
}

void* reader(void* params){
    while(1){
        pthread_mutex_lock(&mutex_nbrRead);
        if(nbrRead>=2560){
            pthread_mutex_unlock(&mutex_nbrRead);
            break;
        }
        nbrRead++;
        pthread_mutex_unlock(&mutex_nbrRead);
        pthread_mutex_lock(&z);
        sem_wait(&r_sem);
        pthread_mutex_lock(&mutex_readerCount);
        readersCount++;
        if(readersCount==1){ //first reader
            sem_wait(&w_sem); //wait for the writers to finish writing
        }
        pthread_mutex_unlock(&mutex_readerCount);
        sem_post(&r_sem);
        pthread_mutex_unlock(&z);
        read();

        pthread_mutex_lock(&mutex_readerCount);
        readersCount--;
        if(readersCount==0){ //last reader
            sem_post(&w_sem);
        }
        pthread_mutex_unlock(&mutex_readerCount);
        while(rand()>RAND_MAX/10000);
    }
    return NULL;
}

int main(int argc, char const *argv[])
{
    int nb_w = atoi(argv[1]); //number of writers
    int nb_r = atoi(argv[2]); //number of readers
    pthread_t threads_w[nb_w];
    pthread_t threads_r[nb_r];
    sem_init(&w_sem, 0, 1);
    sem_init(&r_sem, 0, 1);
    pthread_mutex_init(&mutex_readerCount,NULL);
    pthread_mutex_init(&mutex_writersCount,NULL);
    pthread_mutex_init(&mutex_TMP,NULL);
    pthread_mutex_init(&z,NULL);
    pthread_mutex_init(&mutex_nbrWrite,NULL);
    pthread_mutex_init(&mutex_nbrRead,NULL);
    gettimeofday(&tv,NULL);
    start = 1000000 * tv.tv_sec + tv.tv_usec;
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
    gettimeofday(&tv,NULL);
    mid = 1000000 * tv.tv_sec + tv.tv_usec;
    for (int i = 0; i <nb_r; i++)
    {
        pthread_join(threads_r[i], NULL);
    }
    gettimeofday(&tv,NULL);
    end = 1000000 * tv.tv_sec + tv.tv_usec;
    sem_destroy(&w_sem);
    sem_destroy(&r_sem);
    pthread_mutex_destroy(&mutex_writersCount);
    pthread_mutex_destroy(&mutex_readerCount);
    pthread_mutex_destroy(&mutex_TMP);
    pthread_mutex_destroy(&z);
    pthread_mutex_destroy(&mutex_nbrWrite);
    pthread_mutex_destroy(&mutex_nbrRead);
    FILE *file;
    file = fopen("dahtah.txt", "a");
    /*for(int i=0; i<3200; i++){
        fprintf(file, "%d", TMP[i]);
    }
    fprintf(file, "\n");*/
    fprintf(file, "%ld %ld %ld\n", start, mid, end);
    fclose(file);
    return 0;
}
