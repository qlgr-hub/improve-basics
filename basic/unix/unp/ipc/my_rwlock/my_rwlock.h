#ifndef _MY_RWLOCK_H_
#define _MY_RWLOCK_H_

#include "../../common/wrap_sys_type.h"

typedef struct {
    pthread_mutex_t rw_mutex;
    pthread_cond_t  rw_condreaders;
    pthread_cond_t  rw_condwriters;
    int32_t rw_magic;
    int32_t rw_nwaitreaders;
    int32_t rw_nwaitwriters;
    int32_t rw_refcount;
} my_rwlock_t;

#define RW_MAGIC 0x19283746

#define MY_RWLOCK_INITIALIZER { PTHREAD_MUTEX_INITIALIZER, \
           PTHREAD_COND_INITIALIZER, PTHREAD_COND_INITIALIZER, \
           RW_MAGIC, 0, 0, 0 }

typedef int my_rwlockattr_t;


int32_t My_rwlock_init(my_rwlock_t *rw, my_rwlockattr_t *attr);
int32_t My_rwlock_destroy(my_rwlock_t *rw);
int32_t My_rwlock_rdlock(my_rwlock_t *rw);
int32_t My_rwlock_wrlock(my_rwlock_t *rw);
int32_t My_rwlock_tryrdlock(my_rwlock_t *rw);
int32_t My_rwlock_trywrlock(my_rwlock_t *rw);
int32_t My_rwlock_unlock(my_rwlock_t *rw);

#endif // !_MY_RWLOCK_H_