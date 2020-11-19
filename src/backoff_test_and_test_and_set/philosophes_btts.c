#include "backoff_test_and_test_and_set.c"
#include<stdlib.h>
#include<stdio.h>
#include<stdint.h>
#include<pthread.h>

struct args { //Strcuture of the parameteres for the threads
    int num;
    int N;
    int* forksIds;
};

void think(){} //Guru Meditation

void eat(){} //Yummy


void* philosophe(void* params){
    int num = ((struct args*)params)->num;
    int N = ((struct args*)params)->N;
    int* forksIds = ((struct args*)params)->forksIds;
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
    for(int i=0; i<1000000; i++){ //10000 philosophe cycles
        think();
        mutex_lock(forksIds[fork1]);
        mutex_lock(forksIds[fork2]);
        eat();
        mutex_unlock(forksIds[fork1]);
        mutex_unlock(forksIds[fork2]);
    }
    return NULL;
}

int main(int argc, char const *argv[])
{
    int N = atoi(argv[1]);
    pthread_t threads[N];
    int forksIds[N];

    for(int i = 0; i<N; i++){ //Initialize forks semaphores
        forksIds[i]=mutex_init(); //1 if a fork is free, 0 if it's not
    }

    for (int i = 0; i < N; i++)
    {
        struct args* params = (struct args *)malloc(sizeof(struct args));
        params->num = i;
        params->N = N;
        params->forksIds = forksIds;
        pthread_create(&threads[i], NULL, &philosophe, (void *)params);
    }

    for (int i = 0; i < N; i++)
    {
        pthread_join(threads[i], NULL);
    }

    for(int i = 0; i<N; i++){ //Destroy forks semaphores
        mutex_destroy(forksIds[i]);
    }
    return 0;
}