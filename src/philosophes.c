#include<stdlib.h>
#include<stdio.h>
#include<stdint.h>
#include <semaphore.h>
#include <pthread.h>
#include <time.h>

struct args { //Strcuture of the parameteres for the threads
    int num;
    int N;
    sem_t* forks;
};

void think(){} //Guru Meditation

void eat(){} //Yummy


void* philosophe(void* params){
    int num = ((struct args*)params)->num;
    int N = ((struct args*)params)->N;
    sem_t* forks = ((struct args*)params)->forks;
    int fork1;
    int fork2;

    if(num==N-1){ //if (s)he's the latest philosophe
        fork1 = 0;
        fork2 = num;
    }
    else{
        fork1 = num;
        fork2 = num+1;
    }
    for(int i=0; i<1000000; i++){ //1M philosophe cycles
        think();
        sem_wait(&forks[fork1]);
        sem_wait(&forks[fork2]);
        eat();
        sem_post(&forks[fork2]);
        sem_post(&forks[fork1]);
    }
    return NULL;
}

int main(int argc, char const *argv[])
{
    int N = atoi(argv[1]);
    pthread_t threads[N];
    sem_t forks[N];

    for(int i = 0; i<N; i++){ //Initialize forks semaphores
        sem_init(&forks[i], 0, 1); //1 if a fork is free, 0 if it's not
    }

    for (int i = 0; i < N; i++)
    {
        struct args* params = (struct args *)malloc(sizeof(struct args));
        params->num = i;
        params->N = N;
        params->forks = forks;
        pthread_create(&threads[i], NULL, &philosophe, (void *)params);
    }

    for (int i = 0; i < N; i++)
    {
        pthread_join(threads[i], NULL);
    }

    for(int i = 0; i<N; i++){ //Destroy forks semaphores
        sem_destroy(&forks[i]);
    }
    return 0;
}
