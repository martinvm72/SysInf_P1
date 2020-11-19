//MAX 100 MUTEX at same time
int mutex_init();
void mutex_lock(int id);
void mutex_unlock(int id);
void mutex_destroy(int id);