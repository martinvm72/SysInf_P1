//#include "test_and_test_and_set.h"
#include <stdio.h>
#include<stdint.h>
#include<sys/time.h>
#include "test_and_test_and_set.c"
void work(float a){
    while (rand()>RAND_MAX/8);
}
//1 3/2 2 4 8
int main(int argc, char const *argv[])
{
    /*
    int id1=mutex_init();
    int id2=mutex_init();
    mutex_lock(id1);
    mutex_lock(id2);
    mutex_unlock(id1);
    mutex_lock(id1);
    mutex_unlock(id1);
    mutex_lock(id1);
    //mutex_lock(id1);
    mutex_unlock(id2);
    mutex_unlock(id1);
    mutex_lock(id1);
    mutex_unlock(id1);
    mutex_lock(id2);
    mutex_lock(id1);
    mutex_unlock(id1);
    mutex_unlock(id2);
    mutex_destroy(id1);
    for(int i=0; i<100; i++){
        int a=mutex_init();
        if(a==-1) printf("ha\n");
    }
    for(int i=0;i<100; i++){
        mutex_destroy(i);
    }
    for(int i=0; i<100; i++){
        int a=mutex_init();
        if(a==-1) printf("he\n");
    }/*
    struct timeval t1;
    struct timeval t2;
    for(float j=1; j<6; j*=1.2){
        gettimeofday(&t1,NULL);
        for (int i = 0; i < 1000; i++)
        {
            work(j);
        }
        gettimeofday(&t2,NULL);
        printf("%f : %ld\n",j,t2.tv_usec-t1.tv_usec);
    }
    gettimeofday(&t1,NULL);
       for (int i = 0; i < 1000; i++)
        {
        }
    gettimeofday(&t2,NULL);
    printf(" : %ld\n",t2.tv_usec-t1.tv_usec);*/
    int a=sem_init(3);
    sem_wait(a);
    sem_wait(a);
    sem_wait(a);
    sem_post(a);
    sem_wait(a);
    sem_wait(a);
    return 0;
}
