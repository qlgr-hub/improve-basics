#include "my_rwlock.h"
#include "../../common/wrap_sys_thread.h"

my_rwlock_t rwlock = MY_RWLOCK_INITIALIZER;
//pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER;
pthread_t tid1, tid2;
void *thread1(void *), *thread2(void *);

int main(int argc, char **argv)
{
    void *status;

    Set_concurrency(2);
    pthread_create(&tid1, NULL, thread1, NULL);
    sleep(1);
    pthread_create(&tid2, NULL, thread2, NULL);

    pthread_join(tid2, &status);
    if (status != PTHREAD_CANCELED)
        printf("thread2 status = %p\n", status);
    pthread_join(tid1, &status);
    if (status != NULL)
        printf("thread1 status = %p\n", status);

    printf("rw_refcount = %d, rw_nwaitreaders = %d, rw_nwaitwriters = %d\n",
        rwlock.rw_refcount, rwlock.rw_nwaitreaders, rwlock.rw_nwaitwriters);
    //printf("over\n");

    My_rwlock_destroy(&rwlock);
    //pthread_rwlock_destroy(&rwlock);
}

void *thread1(void *arg)
{
    My_rwlock_rdlock(&rwlock);
    //pthread_rwlock_rdlock(&rwlock);
    printf("thread1() got a read lock\n");
    sleep(3);
    pthread_cancel(tid2);
    sleep(3);
    My_rwlock_unlock(&rwlock);
    //pthread_rwlock_unlock(&rwlock);
    return (NULL);
}

void *thread2(void *arg)
{
    printf("thread2() trying to obtain a write lock\n");
    My_rwlock_wrlock(&rwlock);
    //pthread_rwlock_wrlock(&rwlock);
    printf("thread2() got a write lock\n");
    sleep(1);
    My_rwlock_unlock(&rwlock);
    //pthread_rwlock_unlock(&rwlock);
    return (NULL);
}