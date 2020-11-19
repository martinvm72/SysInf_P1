#include <stdlib.h>
#include "test_and_test_and_set.h"
int *mutex[1024];
int vals[1024];

int sem_init(int init_val){
    if (init_val < 0) return -1;
    for(int i=0; i<100;i++){
        if(!vals[i]) {
            mutex[i]=init();
            vals[i]=init_val;
            return i;
        }
    }
    return -1;
}

int sem_wait(int id){
    while(1){
        lock(id);
        if(vals[id]>0){
            --vals[id];
            unlock(id);
            return 0;
        }
        unlock(id);
    }
}

int sem_post(int id){
    lock(id);
    ++vals[id];
    unlock(id);
    return 0;
}

int sem_destroy(int id){
    destroy(id);
    vals[id]=NULL;
}