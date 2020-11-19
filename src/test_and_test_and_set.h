#include <stdlib.h>
int *mutex[1024];
int isInit[1024];

int mutex_init(){
    for(int i=0; i<1024;i++){
        if(!isInit[i]) {
            mutex[i]=(int *)malloc(sizeof(int));
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
        while (flag2!=0){
            flag2=*mutex[id];
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
