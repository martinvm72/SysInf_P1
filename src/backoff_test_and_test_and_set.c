#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
int *mutex[100];
int isInit[100];
int RANDNUMB[]={RAND_MAX,RAND_MAX/3*2,RAND_MAX/2,RAND_MAX/4,RAND_MAX/8};//average time for randBoucle : 40ns, 80ns, 150ns, 200ns, 400ns

void randBoucle(int a){
    while(rand()>RANDNUMB[a]);
}
int init(){
    for(int i=0; i<100;i++){
        if(!isInit[i]) {
            mutex[i]=malloc(sizeof(int));
            isInit[i]=1;
            return i;
        }
    }
    return -1;
}
void lock(int id){
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

void unlock(int id){
    int a;
    asm(
        "movl $0, %%eax;"
        "xchgl %%eax, %1;" :"=m" (a) :"m" (*(int*)mutex[id]) :"eax");
}
void destroy(int id){
    free(mutex[id]);
    isInit[id]=0;
}
