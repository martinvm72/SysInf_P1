#include <stdio.h>
#include <stdlib.h>
int *mutex;
void init(){
    mutex=malloc(sizeof(int));
    *mutex=0;
}
void lock(){
    int flag=1;
    while(flag==1){
        asm("movl $1, %%eax;"
            "xchgl %%eax, %1;"
            "movl %%eax, %0" 
            :"=m" (flag) 
            :"m" (*(int*)mutex) 
            :"eax");
    }
}
void unlock(){
    int flag=0;
    asm(
        "movl $0, %%eax;"
        "xchgl %%eax, %1;" :"=m" (flag) :"m" (*(int*)mutex) :"eax");
}