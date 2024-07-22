#ifndef _WRAP_SYS_THREAD_H_
#define _WRAP_SYS_THREAD_H_

#include "wrap_sys_type.h"

int32_t Pthread_attr_init(pthread_attr_t *attr);
int32_t Pthread_attr_destroy(pthread_attr_t *attr);
int32_t Pthread_attr_setdetachstate(pthread_attr_t *attr, int32_t detach);
int32_t Pthread_attr_setscope(pthread_attr_t *attr, int32_t scope);
int32_t Pthread_create(pthread_t *tid, const pthread_attr_t *attr, void * (*func)(void *), void *arg);
int32_t Pthread_join(pthread_t tid, void **status);
int32_t Pthread_detach(pthread_t tid);
int32_t Pthread_kill(pthread_t tid, int signo);

int32_t Pthread_mutexattr_init(pthread_mutexattr_t *attr);
int32_t Pthread_mutexattr_destroy(pthread_mutexattr_t *attr);
int32_t Pthread_mutexattr_setpshared(pthread_mutexattr_t *attr, int flag);
int32_t Pthread_mutex_init(pthread_mutex_t *mptr, pthread_mutexattr_t *attr);
int32_t Pthread_mutex_destroy(pthread_mutex_t *mptr);
int32_t Pthread_mutex_lock(pthread_mutex_t *mptr);
int32_t Pthread_mutex_unlock(pthread_mutex_t *mptr);

int32_t Pthread_condattr_init(pthread_condattr_t *attr);
int32_t Pthread_condattr_destroy(pthread_condattr_t *attr);
int32_t Pthread_condattr_setpshared(pthread_condattr_t *attr, int flag);
int32_t Pthread_cond_broadcast(pthread_cond_t *cptr);
int32_t Pthread_cond_signal(pthread_cond_t *cptr);
int32_t Pthread_cond_wait(pthread_cond_t *cptr, pthread_mutex_t *mptr);
int32_t Pthread_cond_timedwait(pthread_cond_t *cptr, pthread_mutex_t *mptr, const struct timespec *tsptr);

int32_t Pthread_key_create(pthread_key_t *key, void (*func)(void *));
int32_t Pthread_setcancelstate(int state, int *oldstate);
int32_t Pthread_setspecific(pthread_key_t key, const void *value);
int32_t Pthread_once(pthread_once_t *ptr, void (*func)(void));
long	pr_thread_id(pthread_t *ptr);
int32_t Set_concurrency(int level);

#endif // !_WRAP_SYS_THREAD_H_