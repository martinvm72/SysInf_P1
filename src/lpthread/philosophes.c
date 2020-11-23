#include<stdlib.h>
#include<stdio.h>
#include<stdint.h>
#include <semaphore.h>
#include <pthread.h>
#include <time.h>

struct args { //Strcuture of the parameteres for the threads
    int num;
    int N;
    pthread_mutex_t* forks;
};

void think(){} //Guru Meditation

void eat(){} //Yummy


void* philosophe(void* params){
    int num = ((struct args*)params)->num;
    int N = ((struct args*)params)->N;
    pthread_mutex_t* forks = ((struct args*)params)->forks;
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
    for(int i=0; i<100000; i++){ //1M philosophe cycles
        think();
        pthread_mutex_lock(&forks[fork1]);
        pthread_mutex_lock(&forks[fork2]);
        eat();
        pthread_mutex_unlock(&forks[fork2]);
        pthread_mutex_unlock(&forks[fork1]);
    }
    return NULL;
}

int main(int argc, char const *argv[])
{
    int N = atoi(argv[1]);
    pthread_t threads[N];
    pthread_mutex_t forks[N];

    for(int i = 0; i<N; i++){ //Initialize forks semaphores
        pthread_mutex_init(&forks[i], NULL); //1 if a fork is free, 0 if it's not
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
        pthread_mutex_destroy(&forks[i]);
    }
    return 0;
}
