#include <stdlib.h>
int *mutex[100];
int vals[100];

int sem_init(int init_val){
    if (init_val < 0) return -1;
    for(int i=0; i<100;i++){
        if(vals[i] == -1) {
            mutex[i]=malloc(sizeof(int));
            vals[i]=init_val;
            return i;
        }
    }
    return -1;
}

int sem_wait(int id);

int sem_post(int id);

int sem_destroy(int id);