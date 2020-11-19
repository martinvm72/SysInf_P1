#include <stdlib.h>
#include "test_and_test_and_set.h"
int sem_mutex[1024];
int vals[1024];
int semInit[1024];

int sem_init(int init_val){
    if (init_val < 0) return -1;
    for(int i=0; i<1024;i++){
        if(!semInit[i]) {
            int mutexId=mutex_init();
            if(mutexId<0) return -1;
            sem_mutex[i]=mutexId;
            vals[i]=init_val;
            return i;
        }
    }
    return -1;
}

int sem_wait(int id){
    while(1){
        mutex_lock(sem_mutex[id]);
        if(vals[id]>0){
            --vals[id];
            mutex_unlock(sem_mutex[id]);
            return 0;
        }
        mutex_unlock(sem_mutex[id]);
    }
}

int sem_post(int id){
    mutex_lock(sem_mutex[id]);
    ++vals[id];
    mutex_unlock(sem_mutex[id]);
    return 0;
}

int sem_destroy(int id){
    mutex_destroy(sem_mutex[id]);
    semInit[id]=0;
}