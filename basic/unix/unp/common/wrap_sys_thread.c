#include "wrap_sys_thread.h"

int32_t Pthread_attr_init(pthread_attr_t *attr)
{
	int32_t	n;

	if ( (n = pthread_attr_init(attr)) != 0 ) {
#ifdef _UNP_DEMO_
	    errno = n;
	    err_sys("pthread_attr_init error");
#endif // _UNP_DEMO_
    }
    return (n);
}

int32_t Pthread_attr_destroy(pthread_attr_t *attr)
{
	int32_t	n;

	if ( (n = pthread_attr_destroy(attr)) != 0 ) {
#ifdef _UNP_DEMO_
	    errno = n;
	    err_sys("pthread_attr_destroy error");
#endif // _UNP_DEMO_
    }
    return (n);
}

int32_t Pthread_attr_setdetachstate(pthread_attr_t *attr, int32_t detach)
{
    int32_t	n;

	if ( (n = pthread_attr_setdetachstate(attr, detach)) != 0 ) {
#ifdef _UNP_DEMO_
	    errno = n;
	    err_sys("pthread_attr_setdetachstate error");
#endif // _UNP_DEMO_
    }
    return (n);
}

int32_t Pthread_attr_setscope(pthread_attr_t *attr, int32_t scope)
{
    int32_t	n;

	if ( (n = pthread_attr_setscope(attr, scope)) != 0 ) {
#ifdef _UNP_DEMO_
	    errno = n;
	    err_sys("pthread_attr_setscope error");
#endif // _UNP_DEMO_
    }
    return (n);
}

int32_t Pthread_create(pthread_t *tid, const pthread_attr_t *attr, void * (*func)(void *), void *arg)
{
    int32_t	n;

	if ( (n = pthread_create(tid, attr, func, arg)) != 0 ) {
#ifdef _UNP_DEMO_
	    errno = n;
	    err_sys("pthread_create error");
#endif // _UNP_DEMO_
    }
    return (n);
}

int32_t Pthread_join(pthread_t tid, void **status)
{
    int32_t	n;

	if ( (n = pthread_join(tid, status)) != 0 ) {
#ifdef _UNP_DEMO_
	    errno = n;
	    err_sys("pthread_join error");
#endif // _UNP_DEMO_
    }
    return (n);
}

int32_t Pthread_detach(pthread_t tid)
{
    int32_t	n;

	if ( (n = pthread_detach(tid)) != 0 ) {
#ifdef _UNP_DEMO_
	    errno = n;
	    err_sys("pthread_detach error");
#endif // _UNP_DEMO_
    }
    return (n);
}

int32_t Pthread_kill(pthread_t tid, int signo)
{
    int32_t	n;

	if ( (n = pthread_kill(tid, signo)) != 0 ) {
#ifdef _UNP_DEMO_
	    errno = n;
	    err_sys("pthread_kill error");
#endif // _UNP_DEMO_
    }
    return (n);
}

int32_t Pthread_mutexattr_init(pthread_mutexattr_t *attr)
{
    int32_t	n;

	if ( (n = pthread_mutexattr_init(attr)) != 0 ) {
#ifdef _UNP_DEMO_
	    errno = n;
	    err_sys("pthread_mutexattr_init error");
#endif // _UNP_DEMO_
    }
    return (n);
}

int32_t Pthread_mutexattr_destroy(pthread_mutexattr_t *attr)
{
    int32_t	n;

	if ( (n = pthread_mutexattr_destroy(attr)) != 0 ) {
#ifdef _UNP_DEMO_
	    errno = n;
	    err_sys("pthread_mutexattr_destroy error");
#endif // _UNP_DEMO_
    }
    return (n);
}

#ifdef	_POSIX_THREAD_PROCESS_SHARED
int32_t Pthread_mutexattr_setpshared(pthread_mutexattr_t *attr, int flag)
{
    int32_t	n;

	if ( (n = pthread_mutexattr_setpshared(attr, flag)) != 0 ) {
#ifdef _UNP_DEMO_
	    errno = n;
	    err_sys("pthread_mutexattr_setpshared error");
#endif // _UNP_DEMO_
    }
    return (n);
}
#endif // _POSIX_THREAD_PROCESS_SHARED

int32_t Pthread_mutex_init(pthread_mutex_t *mptr, pthread_mutexattr_t *attr)
{
     int32_t n;

	if ( (n = pthread_mutex_init(mptr, attr)) != 0 ) {
#ifdef _UNP_DEMO_
	    errno = n;
	    err_sys("pthread_mutex_init error");
#endif // _UNP_DEMO_
    }
    return (n);
}

int32_t Pthread_mutex_destroy(pthread_mutex_t *mptr)
{
     int32_t n;

	if ( (n = pthread_mutex_destroy(mptr)) != 0 ) {
#ifdef _UNP_DEMO_
	    errno = n;
	    err_sys("pthread_mutex_destroy error");
#endif // _UNP_DEMO_
    }
    return (n);
}


int32_t Pthread_mutex_lock(pthread_mutex_t *mptr)
{
    int32_t n;

	if ( (n = pthread_mutex_lock(mptr)) != 0 ) {
#ifdef _UNP_DEMO_
	    errno = n;
	    err_sys("pthread_mutex_lock error");
#endif // _UNP_DEMO_
    }
    return (n);
}

int32_t Pthread_mutex_unlock(pthread_mutex_t *mptr)
{
    int32_t n;

	if ( (n = pthread_mutex_unlock(mptr)) != 0 ) {
#ifdef _UNP_DEMO_
	    errno = n;
	    err_sys("pthread_mutex_unlock error");
#endif // _UNP_DEMO_
    }
    return (n);
}

int32_t Pthread_condattr_init(pthread_condattr_t *attr)
{
    int32_t n;

	if ( (n = pthread_condattr_init(attr)) != 0 ) {
#ifdef _UNP_DEMO_
	    errno = n;
	    err_sys("pthread_condattr_init error");
#endif // _UNP_DEMO_
    }
    return (n);
}

int32_t Pthread_condattr_destroy(pthread_condattr_t *attr)
{
    int32_t n;

	if ( (n = pthread_condattr_destroy(attr)) != 0 ) {
#ifdef _UNP_DEMO_
	    errno = n;
	    err_sys("pthread_condattr_destroy error");
#endif // _UNP_DEMO_
    }
    return (n);
}

#ifdef	_POSIX_THREAD_PROCESS_SHARED
int32_t Pthread_condattr_setpshared(pthread_condattr_t *attr, int flag)
{
    int32_t n;

	if ( (n = pthread_condattr_setpshared(attr, flag)) != 0 ) {
#ifdef _UNP_DEMO_
	    errno = n;
	    err_sys("pthread_condattr_setpshared error");
#endif // _UNP_DEMO_
    }
    return (n);
}
#endif // _POSIX_THREAD_PROCESS_SHARED

int32_t Pthread_cond_broadcast(pthread_cond_t *cptr)
{
    int32_t n;

	if ( (n = pthread_cond_broadcast(cptr)) != 0 ) {
#ifdef _UNP_DEMO_
	    errno = n;
	    err_sys("pthread_cond_broadcast error");
#endif // _UNP_DEMO_
    }
    return (n);
}

int32_t Pthread_cond_signal(pthread_cond_t *cptr)
{
    int32_t n;

	if ( (n = pthread_cond_signal(cptr)) != 0 ) {
#ifdef _UNP_DEMO_
	    errno = n;
	    err_sys("pthread_cond_signal error");
#endif // _UNP_DEMO_
    }
    return (n);
}

int32_t Pthread_cond_wait(pthread_cond_t *cptr, pthread_mutex_t *mptr)
{
    int32_t n;

	if ( (n = pthread_cond_wait(cptr, mptr)) != 0 ) {
#ifdef _UNP_DEMO_
	    errno = n;
	    err_sys("pthread_cond_wait error");
#endif // _UNP_DEMO_
    }
    return (n);
}

int32_t Pthread_cond_timedwait(pthread_cond_t *cptr, pthread_mutex_t *mptr, const struct timespec *tsptr)
{
    int32_t n;

	if ( (n = pthread_cond_timedwait(cptr, mptr, tsptr)) != 0 ) {
#ifdef _UNP_DEMO_
	    errno = n;
	    err_sys("pthread_cond_timedwait error");
#endif // _UNP_DEMO_
    }
    return (n);
}

int32_t Pthread_key_create(pthread_key_t *key, void (*func)(void *))
{
    int32_t n;

	if ( (n = pthread_key_create(key, func)) != 0 ) {
#ifdef _UNP_DEMO_
	    errno = n;
	    err_sys("pthread_key_create error");
#endif // _UNP_DEMO_
    }
    return (n);
}

int32_t Pthread_setcancelstate(int state, int *oldstate)
{
    int32_t n;

	if ( (n = pthread_setcancelstate(state, oldstate)) != 0 ) {
#ifdef _UNP_DEMO_
	    errno = n;
	    err_sys("pthread_setcancelstate error");
#endif // _UNP_DEMO_
    }
    return (n);
}

int32_t Pthread_setspecific(pthread_key_t key, const void *value)
{
    int32_t n;

	if ( (n = pthread_setspecific(key, value)) != 0 ) {
#ifdef _UNP_DEMO_
	    errno = n;
	    err_sys("pthread_setspecific error");
#endif // _UNP_DEMO_
    }
    return (n);
}

int32_t Pthread_once(pthread_once_t *ptr, void (*func)(void))
{
    int32_t n;

	if ( (n = pthread_once(ptr, func)) != 0 ) {
#ifdef _UNP_DEMO_
	    errno = n;
	    err_sys("pthread_once error");
#endif // _UNP_DEMO_
    }
    return (n);
}

long pr_thread_id(pthread_t *ptr)
{
#if defined(sun)
	return((ptr == NULL) ? pthread_self() : *ptr);	/* Solaris */

#elif defined(__osf__) && defined(__alpha)
	pthread_t	tid;

	tid = (ptr == NULL) ? pthread_self() : *ptr;	/* Digital Unix */
	return(pthread_getsequence_np(tid));
#else
		/* 4everything else */
	return((ptr == NULL) ? pthread_self() : *ptr);
#endif
}

static int32_t set_concurrency(int level)
{
#ifdef	HAVE_THR_SETCONCURRENCY_PROTO
	int		thr_setconcurrency(int);

	return(thr_setconcurrency(level));
#else
	return(0);
#endif
}

int32_t Set_concurrency(int level)
{
	int32_t n;
	if ( (n = set_concurrency(level)) != 0 ) {
#ifdef _UNP_DEMO_
	    err_sys("set_concurrency error");
#endif // _UNP_DEMO_
	}
	return (n);
}