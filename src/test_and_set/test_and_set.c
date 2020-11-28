#include <stdio.h>
#include <stdlib.h>

//----------------------------------------------------------------------------------------------------------------------
//MUTEX
int *mutex[1024];//array with the value of the mutex (1 if lock 0 if not)
int isInit[1024];//array that shows if a mutex is init or not

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
        asm(//asm to exchange atomically 1 with the value of mutex[i] to know if it is already lock or not
            "movl $1, %eax;"
            "xchgl %eax, %1;"
            "movl %eax, %0" 
            :"=m" (flag) 
            :"m" (*(int*)mutex[id]) 
            :"eax");
    }
}
void mutex_unlock(int id){
    int a=0;
    asm(//asm to set atomically the value of mutex[i] to 0
        "movl $0, %%eax;"
        "xchgl %%eax, %1;" :"=m" (a) :"m" (*(int*)mutex[id]) :"eax");
}
void mutex_destroy(int id){
    free(mutex[id]);
    isInit[id]=0;
}


//----------------------------------------------------------------------------------------------------------------------
//SEMAPHORE

int sem_mutex[1024];//array with the mutex associated to the semaphore
int vals[1024];//array with the value of the semaphore
int semInit[1024];//array that shows if a semaphore is init or not

int sem_init(int init_val){
    if (init_val < 0) return -1;
    for(int i=0; i<1024;i++){
        if(!semInit[i]) {
            int mutexId=mutex_init();
            if(mutexId<0) return -1;
            sem_mutex[i]=mutexId;
            vals[i]=init_val;
            semInit[i]=1;
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