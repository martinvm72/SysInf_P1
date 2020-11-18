#include <stdio.h>
#include <stdlib.h>
int *mutex[100];
int isInit[100];

int init(){
    for(int i=0; i<100;i++){
        if(!isInit[i]) {
            mutex[i]= (int *)malloc(sizeof(int));
            isInit[i]=1;
            return i;
        }
    }
    return -1;
}
void lock(int id){
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
void unlock(int id){
    int a=0;
    asm(
        "movl $0, %%eax;"
        "xchgl %%eax, %1;" :"=m" (a) :"m" (*(int*)mutex[id]) :"eax");
}
void destroy(int id){
    free(mutex[id]);
    isInit[id]=0;
}