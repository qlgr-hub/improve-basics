#include "../../common/err_func.h"
#include "../../common/wrap_sys_type.h"
#include "../../common/wrap_sys_thread.h"
#include <pthread.h>

#define MAXNITEMS     1000000
#define MAXNTHREADS   100

int32_t nitems;
struct {
    pthread_mutex_t mutex;
    int32_t buff[MAXNITEMS];
    int32_t nput;
    int32_t nval;
} shared = {
    PTHREAD_MUTEX_INITIALIZER
};

void *produce(void *), *consume(void *);

int main(int argc, char **argv)
{
    int32_t i, nthreads, count[MAXNTHREADS];
    pthread_t tid_produce[MAXNTHREADS], tid_consume;

    if (argc != 3)
        err_quit("usage: prodcons2 <#items> <#threads>");
    nitems = MIN(atoi(argv[1]), MAXNITEMS);
    nthreads = MIN(atoi(argv[2]), MAXNTHREADS);

    Set_concurrency(nthreads);

    for (i = 0; i < nthreads; i++) {
        count[i] = 0;
        pthread_create(&tid_produce[i], NULL, produce, &count[i]);
    }
    pthread_create(&tid_consume, NULL, consume, NULL);

    for (i = 0; i < nthreads; i++) {
        pthread_join(tid_produce[i], NULL);
        printf("count[%d] = %d\n", i, count[i]);
    }
    pthread_join(tid_consume, NULL);

    exit(0);
}

void *produce(void *arg)
{
    for ( ; ; ) {
        pthread_mutex_lock(&shared.mutex);
        if (shared.nput >= nitems) {
            Pthread_mutex_unlock(&shared.mutex);
            return (NULL);
        }
        shared.buff[shared.nput] = shared.nval;
        shared.nput++;
        shared.nval++;
        Pthread_mutex_unlock(&shared.mutex);
        *((int32_t *) arg) += 1;
    }
}

void consume_wait(int32_t i) 
{
    for ( ; ; ) {
        pthread_mutex_lock(&shared.mutex);
        if (i < shared.nput) {
            Pthread_mutex_unlock(&shared.mutex);
            return;
        }
        Pthread_mutex_unlock(&shared.mutex);
    }
}

void *consume(void *arg)
{
    int32_t i;

    for (i = 0; i < nitems; i++) {
        consume_wait(i);
        if (shared.buff[i] != i)
            printf("buf[%d] = %d\n", i, shared.buff[i]);
    }
    return (NULL);
}