#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include "../test_and_set/test_and_set.c"

struct args { //Strcuture of the parameteres for the threads
    int cycle;
    int id;
};

void* lock_test(void* params){
    int id = ((struct args*)params)->id;
    if(id==-1) printf("OUPS... SOMETHING WENT WRONG!");
    for(int i=0; i<((struct args*)params)->cycle; i++){
        mutex_lock(id);
        while(rand()>RAND_MAX/10000);
        mutex_unlock(id);
    }
    return NULL;
}

int main(int argc, char const *argv[])
{
    int N = atoi(argv[1]);
    pthread_t threads[N];
    struct args* params = (struct args *)malloc(sizeof(struct args));
    params->cycle= round(6400/N);
    int id=mutex_init();
    for (int i = 0; i < N; i++)
    {
        params->id = id;
        pthread_create(&threads[i], NULL, &lock_test, (void *)params);
    }
    for (int i = 0; i < N; i++)
    {
        pthread_join(threads[i], NULL);
    }
    mutex_destroy(id);
    return 0;
}
