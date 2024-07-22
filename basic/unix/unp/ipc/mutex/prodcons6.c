#include "../../common/err_func.h"
#include "../../common/wrap_sys_type.h"
#include "../../common/wrap_sys_thread.h"
#include <pthread.h>

#define MAXNITEMS     1000000
#define MAXNTHREADS   100

int32_t nitems;
int32_t buff[MAXNITEMS];
struct {
    pthread_mutex_t mutex;
    int32_t nput;
    int32_t nval;
} put = {
    PTHREAD_MUTEX_INITIALIZER
};

struct {
    pthread_mutex_t mutex;
    pthread_cond_t  cond;
    int32_t nready;
} nready1 = {
    PTHREAD_MUTEX_INITIALIZER, PTHREAD_COND_INITIALIZER
};

void *produce(void *), *consume(void *);

int32_t dosignal;

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
        pthread_mutex_lock(&put.mutex);
        if (put.nput >= nitems) {
            Pthread_mutex_unlock(&put.mutex);
            return (NULL);
        }
        buff[put.nput] = put.nval;
        put.nput++;
        put.nval++;
        pthread_mutex_unlock(&put.mutex);

        pthread_mutex_lock(&nready1.mutex);
        dosignal = (nready1.nready == 0);
        nready1.nready++;
        pthread_mutex_unlock(&nready1.mutex);
        
        if (dosignal)
            pthread_cond_signal(&nready1.cond);

        *((int32_t *) arg) += 1;
    }
}

void *consume(void *arg)
{
    int32_t i;

    for (i = 0; i < nitems; i++) {
        pthread_mutex_lock(&nready1.mutex);
        if (nready1.nready == 0)
            Pthread_cond_wait(&nready1.cond, &nready1.mutex);
        nready1.nready--;
        pthread_mutex_unlock(&nready1.mutex);

        if (buff[i] != i)
            printf("buff[%d] = %d\n", i, buff[i]);
    }
    return (NULL);
}