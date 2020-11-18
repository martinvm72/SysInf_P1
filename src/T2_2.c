#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include "test_and_set.h"

struct args { //Strcuture of the parameteres for the threads
    int cycle;
};

void* lock_test(void* params){
    int id = init();
    if(id==-1) printf("OUPS... SOMETHING WENT WRONG!");
    for(int i=0; i<((struct args*)params)->cycle; i++){
        lock(id);
        while(rand()>RAND_MAX/10000);
        unlock(id);
    }
    destroy(id);
    return NULL;
}

int main(int argc, char const *argv[])
{
    int N = atoi(argv[1]);
    pthread_t threads[N];
    struct args* params = (struct args *)malloc(sizeof(struct args));
    params->cycle= round(6400/N);
    for (int i = 0; i < N; i++)
    {
        pthread_create(&threads[i], NULL, &lock_test, (void *)params);
    }
    for (int i = 0; i < N; i++)
    {
        pthread_join(threads[i], NULL);
    }
    return 0;
}
