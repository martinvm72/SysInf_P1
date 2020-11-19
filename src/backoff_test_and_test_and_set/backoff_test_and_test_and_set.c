#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

//----------------------------------------------------------------------------------------------------------------------
//MUTEX

int *mutex[1024];
int isInit[1024];
int RANDNUMB[]={RAND_MAX,RAND_MAX/3*2,RAND_MAX/2,RAND_MAX/4,RAND_MAX/8};//average time for randBoucle : 40ns, 80ns, 150ns, 200ns, 400ns

void randBoucle(int a){
    while(rand()>RANDNUMB[a]);
}
int mutex_init(){
    for(int i=0; i<1024;i++){
        if(!isInit[i]) {
            mutex[i]=malloc(sizeof(int));
            isInit[i]=1;
            return i;
        }
    }
    return -1;
}
void mutex_lock(int id){
    int flag=1;
    while(flag==1){
        int flag2=*mutex[id];
        int i=0;
        while (flag2!=0){
            randBoucle(i);
            flag2=*mutex[id];
            if(i<4) i++;
        }
        asm("movl $1, %%eax;"
            "xchgl %%eax, %1;"
            "movl %%eax, %0" 
            :"=m" (flag) 
            :"m" (*(int*)mutex[id]) 
            :"eax");
    }
}

void mutex_unlock(int id){
    int a;
    asm(
        "movl $0, %%eax;"
        "xchgl %%eax, %1;" :"=m" (a) :"m" (*(int*)mutex[id]) :"eax");
}
void mutex_destroy(int id){
    free(mutex[id]);
    isInit[id]=0;
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