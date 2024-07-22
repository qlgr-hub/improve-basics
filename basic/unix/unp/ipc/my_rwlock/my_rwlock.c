#include "my_rwlock.h"
#include "../../common/err_func.h"

int32_t my_rwlock_init(my_rwlock_t *rw, my_rwlockattr_t *attr)
{
    int32_t result;

    if (attr != NULL)
        return (EINVAL); /* not supported */

    if ( (result = pthread_mutex_init(&rw->rw_mutex, NULL)) != 0 )
        goto err1;
    if ( (result = pthread_cond_init(&rw->rw_condreaders, NULL)) != 0 )
        goto err2;
    if ( (result = pthread_mutex_init(&rw->rw_condwriters, NULL)) != 0 )
        goto err3;
    rw->rw_nwaitreaders = 0;
    rw->rw_nwaitwriters = 0;
    rw->rw_refcount = 0;
    rw->rw_magic = RW_MAGIC;

    return (0);

// 单个函数中用这个还是很不错的
err3:
    pthread_cond_destroy(&rw->rw_condreaders);
err2:
    pthread_mutex_destroy(&rw->rw_mutex);
err1:
    return (result);
}

int32_t my_rwlock_destroy(my_rwlock_t *rw)
{
    if (rw->rw_magic != RW_MAGIC)
        return (EINVAL);
    if (rw->rw_refcount != 0 ||
        rw->rw_nwaitreaders != 0 || rw->rw_nwaitwriters != 0)
        return (EBUSY);

    pthread_mutex_destroy(&rw->rw_mutex);
    pthread_cond_destroy(&rw->rw_condreaders);
    pthread_cond_destroy(&rw->rw_condwriters);
    rw->rw_magic = 0;

    return (0);
}

static void rwlock_cancelrdwait(void *arg)
{
    my_rwlock_t *rw;

    rw = arg;
    rw->rw_nwaitreaders--;
    pthread_mutex_unlock(&rw->rw_mutex);
}

int32_t my_rwlock_rdlock(my_rwlock_t *rw)
{
    int32_t result;

    if (rw->rw_magic != RW_MAGIC)
        return (EINVAL);

    if ( (result = pthread_mutex_lock(&rw->rw_mutex)) != 0 )
        return (result);

    while (rw->rw_refcount < 0 || rw->rw_nwaitwriters > 0) {
        rw->rw_nwaitreaders++;
        pthread_cleanup_push(rwlock_cancelrdwait, (void *)rw);
        result = pthread_cond_wait(&rw->rw_condreaders, &rw->rw_mutex);
        pthread_cleanup_pop(0);
        rw->rw_nwaitreaders--;
        if (result != 0)
            break;
    }
    if (result == 0)
        rw->rw_refcount++;

    pthread_mutex_unlock(&rw->rw_mutex);
    return (result);
}

static void rwlock_cancelwrwait(void *arg)
{
    my_rwlock_t *rw;

    rw = arg;
    rw->rw_nwaitwriters--;
    pthread_mutex_unlock(&rw->rw_mutex);
}

int32_t my_rwlock_wrlock(my_rwlock_t *rw)
{
    int32_t result;

    if (rw->rw_magic != RW_MAGIC)
        return (EINVAL);

    if ( (result = pthread_mutex_lock(&rw->rw_mutex)) != 0 )
        return (result);

    while (rw->rw_refcount != 0) {
        rw->rw_nwaitwriters++;
        pthread_cleanup_push(rwlock_cancelwrwait, (void *)rw);
        result = pthread_cond_wait(&rw->rw_condwriters, &rw->rw_mutex);
        pthread_cleanup_pop(0);
        rw->rw_nwaitwriters--;
        if (result != 0)
            break;
    }
    if (result == 0)
        rw->rw_refcount = -1;

    pthread_mutex_unlock(&rw->rw_mutex);
    return (result);
}

int32_t my_rwlock_tryrdlock(my_rwlock_t *rw)
{
    int32_t result;

    if (rw->rw_magic != RW_MAGIC)
        return (EINVAL);

    if ( (result = pthread_mutex_lock(&rw->rw_mutex)) != 0 )
        return (result);

    if (rw->rw_refcount < 0 || rw->rw_nwaitwriters > 0) 
        return (EBUSY);
    else
        rw->rw_refcount++;

    pthread_mutex_unlock(&rw->rw_mutex);
    return (result);
}

int32_t my_rwlock_trywrlock(my_rwlock_t *rw)
{
    int32_t result;

    if (rw->rw_magic != RW_MAGIC)
        return (EINVAL);

    if ( (result = pthread_mutex_lock(&rw->rw_mutex)) != 0 )
        return (result);

    if (rw->rw_refcount != 0) 
        return (EBUSY);
    else
        rw->rw_refcount = -1;

    pthread_mutex_unlock(&rw->rw_mutex);
    return (result);
}

int32_t my_rwlock_unlock(my_rwlock_t *rw)
{
    int32_t result;

    if (rw->rw_magic != RW_MAGIC)
        return (EINVAL);

    if ( (result = pthread_mutex_lock(&rw->rw_mutex)) != 0 )
        return (result);

    if (rw->rw_refcount > 0)
        rw->rw_refcount--;
    else if (rw->rw_refcount == -1)
        rw->rw_refcount = 0;
    else
        err_dump("rw_refcount = %d", rw->rw_refcount);

    if (rw->rw_nwaitreaders > 0) {
        if (rw->rw_refcount == 0)
            result = pthread_cond_signal(&rw->rw_condwriters);
    } else if (rw->rw_nwaitreaders > 0)
        result = pthread_cond_broadcast(&rw->rw_condreaders);

    pthread_mutex_unlock(&rw->rw_mutex);
    return (result);
}


int32_t My_rwlock_init(my_rwlock_t *rw, my_rwlockattr_t *attr)
{
    int32_t n;

    if ( (n = my_rwlock_init(rw, attr)) != 0 ) {
#ifdef _UNP_DEMO_
        err_sys("my_rwlock_init error");
#endif // _UNP_DEMO_
    }
    return (n);
}

int32_t My_rwlock_destroy(my_rwlock_t *rw)
{
    int32_t n;

    if ( (n = my_rwlock_destroy(rw)) != 0 ) {
#ifdef _UNP_DEMO_
        err_sys("my_rwlock_destroy error");
#endif // _UNP_DEMO_
    }
    return (n);
}

int32_t My_rwlock_rdlock(my_rwlock_t *rw)
{
    int32_t n;

    if ( (n = my_rwlock_rdlock(rw)) != 0 ) {
#ifdef _UNP_DEMO_
        err_sys("my_rwlock_rdlock error");
#endif // _UNP_DEMO_
    }
    return (n);
}

int32_t My_rwlock_wrlock(my_rwlock_t *rw)
{
    int32_t n;

    if ( (n = my_rwlock_wrlock(rw)) != 0 ) {
#ifdef _UNP_DEMO_
        err_sys("my_rwlock_wrlock error");
#endif // _UNP_DEMO_
    }
    return (n);
}

int32_t My_rwlock_tryrdlock(my_rwlock_t *rw)
{
    int32_t n;

    if ( (n = my_rwlock_tryrdlock(rw)) != 0 ) {
#ifdef _UNP_DEMO_
        err_sys("my_rwlock_tryrdlock error");
#endif // _UNP_DEMO_
    }
    return (n);
}

int32_t My_rwlock_trywrlock(my_rwlock_t *rw)
{
    int32_t n;

    if ( (n = my_rwlock_trywrlock(rw)) != 0 ) {
#ifdef _UNP_DEMO_
        err_sys("my_rwlock_trywrlock error");
#endif // _UNP_DEMO_
    }
    return (n);
}

int32_t My_rwlock_unlock(my_rwlock_t *rw)
{
    int32_t n;

    if ( (n = my_rwlock_unlock(rw)) != 0 ) {
#ifdef _UNP_DEMO_
        err_sys("my_rwlock_unlock error");
#endif // _UNP_DEMO_
    }
    return (n);
}