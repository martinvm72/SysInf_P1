#include <stdio.h>
#include <stdlib.h>

//----------------------------------------------------------------------------------------------------------------------
//MUTEX
int *mutex[1024];
int isInit[1024];

int mutex_init(){
    for(int i=0; i<1024;i++){
        if(!isInit[i]) {
            mutex[i]= (int *)malloc(sizeof(int));
            isInit[i]=1;
            return i;
        }
    }
    return -1;
}
void mutex_lock(int id){
    int flag=1;
    while(flag==1){
        asm("movl $1, %%eax;"
            "xchgl %%eax, %1;"
            "movl %%eax, %0" 
            :"=m" (flag) 
            :"m" (*(int*)mutex[id]) 
            :"eax");
    }
}
void mutex_unlock(int id){
    int a=0;
    asm(
        "movl $0, %%eax;"
        "xchgl %%eax, %1;" :"=m" (a) :"m" (*(int*)mutex[id]) :"eax");
}
void mutex_destroy(int id){
    free(mutex[id]);
    isInit[id]=NULL;
}


//----------------------------------------------------------------------------------------------------------------------
//SEMAPHORE

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