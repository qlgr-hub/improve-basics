#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <sys/time.h>
#include <string.h>
#include <limits.h>

int makethread(void *(*fn)(void *), void *arg, pthread_t *tidp)
{
    int            err;
    pthread_attr_t attr;

    err = pthread_attr_init(&attr);
    if (err != 0)
        return (err);

    err = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    if (err == 0) {
        err = pthread_create(tidp, &attr, fn, arg);
        printf("pthread_create tid[%lu] err=%s\n", (unsigned long)(*tidp), strerror(err));
    }

    pthread_attr_destroy(&attr);

    return (err);
}

void *thread_func(void *arg)
{
    printf("thread_func start...\n");

    return ((void *)0);
}

int main()
{
    int err;
    pthread_t tid;

    if (makethread(thread_func, NULL, &tid) != 0) {
        printf("makethread error\n");
        exit(1);
    }

    if ( (err = pthread_join(tid, NULL)) != 0) {
        printf("pthread_join error: %s\n", strerror(err));
        exit(1);
    }

    exit(0);
}












// need compile heapsort.c
// #define NTHR      8
// #define NUMNUM    8000000L
// #define TNUM      (NUMNUM / NTHR)

// long nums[NUMNUM];
// long snums[NUMNUM];

// pthread_barrier_t b;

// #ifdef SOLARIS
// #define heapsort qsort
// #else
// extern int heapsort(void *, size_t, size_t, int (*)(const void *, const void *));
// #endif // SOLARIS

// int complong(const void *arg1, const void *arg2)
// {
//     long l1 = *((long *)arg1);
//     long l2 = *((long *)arg2);

//     if (l1 == l2)
//         return 0;
//     else if (l1 < l2)
//         return -1;
//     else
//         return 1;
// }

// void *thread_func(void *arg)
// {
//     long idx = (long)arg;

//     heapsort(&nums[idx], TNUM, sizeof(long), complong);
//     pthread_barrier_wait(&b);

//     printf("all the bor's done, I can do other work now!\n");

//     return ((void *)0);
// }

// void merge()
// {
//     long idx[NTHR];
//     long i, minidx, sidx, num;

//     for (i = 0; i < NTHR; i++)
//         idx[i] = i * TNUM;

//     for (sidx = 0; sidx < NUMNUM; sidx++) {
//         num = LONG_MAX;
//         for (i = 0; i < NTHR; i++) {
//             if ( (idx[i] < (i+1)*TNUM) && (nums[idx[i]] < num)) {
//                 num = nums[idx[i]];
//                 minidx = i;
//             }
//         }
//         snums[sidx] = nums[idx[minidx]];
//         idx[minidx]++;
//     }
// }

// int main()
// {
//     unsigned long  i;
//     struct timeval start, end;
//     long long      startusec, endusec;
//     double         elapsed;
//     int            err;
//     pthread_t      tid;

//     srandom(1);
//     for (i = 0; i < NUMNUM; i++)
//         nums[i] = random();

//     gettimeofday(&start, NULL);
//     // pthread_barrier_init(&b, NULL, NTHR+1);
//     // for (i = 0; i < NTHR; i++) {
//     //     err = pthread_create(&tid, NULL, thread_func, (void *)(i * TNUM));
//     //     if (err != 0) {
//     //         printf("can not create thread\n");
//     //         exit(1);
//     //     }
//     // }
//     // pthread_barrier_wait(&b);
//     // merge();
//     heapsort(&nums[0], NUMNUM, sizeof(long), complong);
//     gettimeofday(&end, NULL);

//     startusec = start.tv_sec * 1000000 + start.tv_usec;
//     endusec = end.tv_sec * 1000000 + end.tv_usec;
//     elapsed = (double)(endusec - startusec) / 1000000.0;
//     printf("sort took %.4f seconds\n", elapsed);
//     //for (i = 0; i < NUMNUM; i++)
//     //   printf("%ld\n", snums[i]);

//     exit(0);
// }




















// struct job {
//     struct job *j_next;
//     struct job *j_prev;
//     pthread_t   j_id;
//     int         j_work;
// };

// struct queue {
//     struct job         *q_head;
//     struct job         *q_tail;
//     pthread_rwlock_t    q_lock;
//     pthread_spinlock_t  q_lock_start;
// };

// int queue_init(struct queue *qp)
// {
//     int err;

//     qp->q_head = NULL;
//     qp->q_tail = NULL;

//     err = pthread_rwlock_init(&qp->q_lock, NULL);
//     if (err != 0)
//         return err;

//     err = pthread_spin_init(&qp->q_lock_start, PTHREAD_PROCESS_PRIVATE);
//     if (err != 0)
//         return err;

//     return (0);
// }

// int queue_destroy(struct queue *qp)
// {
//     int err;

//     qp->q_head = NULL;
//     qp->q_tail = NULL;

//     err = pthread_rwlock_destroy(&qp->q_lock);
//     if (err != 0)
//         return err;

//     err = pthread_spin_destroy(&qp->q_lock_start);
//     if (err != 0)
//         return err;

//     return (0);
// }

// void job_insert(struct queue *qp, struct job *jp)
// {
//     pthread_rwlock_wrlock(&qp->q_lock);

//     jp->j_next = qp->q_head;
//     jp->j_prev = NULL;

//     if (qp->q_head != NULL)
//         qp->q_head->j_prev = jp;
//     else
//         qp->q_tail = jp;
    
//     qp->q_head = jp;

//     pthread_rwlock_unlock(&qp->q_lock);
// }


// void job_append(struct queue *qp, struct job *jp)
// {
//     pthread_rwlock_wrlock(&qp->q_lock);

//     jp->j_next = NULL;
//     jp->j_prev = qp->q_tail;

//     if (qp->q_tail != NULL)
//         qp->q_tail->j_next = jp;
//     else
//         qp->q_head = jp;
    
//     qp->q_tail = jp;

//     pthread_rwlock_unlock(&qp->q_lock);
// }

// void job_remove(struct queue *qp, struct job *jp)
// {
//     pthread_rwlock_wrlock(&qp->q_lock);

//     if (qp->q_head == jp) {
//         qp->q_head = jp->j_next;
//         if (qp->q_tail == jp)
//             qp->q_tail = NULL;
//         else
//             qp->q_head->j_prev = jp->j_prev;
//     } else if (qp->q_tail == jp) {
//         qp->q_tail = jp->j_prev;
//         qp->q_tail->j_next = jp->j_next;
//     } else {
//         jp->j_prev->j_next = jp->j_next;
//         jp->j_next->j_prev = jp->j_prev;
//     }

//     pthread_rwlock_unlock(&qp->q_lock);
// }

// struct job *job_find(struct queue *qp, pthread_t id)
// {
//     struct job *jp;

//     if (pthread_rwlock_rdlock(&qp->q_lock) != 0)
//         return NULL;

//     for (jp = qp->q_head; jp != NULL; jp = jp->j_next)
//         if (pthread_equal(jp->j_id, id))
//             break;

//     pthread_rwlock_unlock(&qp->q_lock);

//     return (jp);
// }

// void *thread_func(void *arg)
// {
//     struct queue *qp = (struct queue*)arg;

//     // just for wait pthread_create return
//     pthread_spin_lock(&qp->q_lock_start);
//     pthread_spin_unlock(&qp->q_lock_start);

//     struct job *jp;

//     jp = job_find(qp, pthread_self());
//     if (jp) {
//         printf("thread[%lu] start work(%d)...\n", (unsigned long)jp->j_id, jp->j_work);
//         while (--jp->j_work);
//         printf("thread[%lu] end work(%d)...\n", (unsigned long)jp->j_id, jp->j_work);
//     }

//     return ((void *)0);
// }

// #define RANDOM_RANGE(a, b) ( (rand() % (b-a+1)) + a )
// #define JOBCOUNT 10

// int main(void)
// {
//     struct queue *qp;
//     struct job   *jp, *tmp;
//     int i;

//     srand(time(NULL));

//     qp = (struct queue *)malloc(sizeof(struct queue));
//     if (qp == NULL) {
//         printf("malloc error, qp\n");
//         exit(-1);
//     }
//     queue_init(qp);

//     for (i = 0; i < JOBCOUNT; i++) {
//         jp = (struct job *)malloc(sizeof(struct job));
//         if (jp == NULL) {
//             printf("malloc error, [i=%d]\n", i);
//             exit(-1);
//         }
        
//         jp->j_work = RANDOM_RANGE(900000, 1000000);
//         jp->j_id = -1;

//         job_append(qp, jp);

//         // sub thread need wait pthread_create retrun, otherwise job_find may go wrong.
//         // windows can create a suspended thread, but pthread api not support that.
//         pthread_spin_lock(&qp->q_lock_start);
//         if (pthread_create(&jp->j_id, NULL, thread_func, (void *)qp) != 0) {
//             printf("pthread_create error, [i=%d]\n", i);
//             exit(-1);
//         }
//         pthread_spin_unlock(&qp->q_lock_start);
//     }

//     jp = qp->q_head;
//     while (jp) {
//         if (pthread_join(jp->j_id, NULL) != 0) {
//             printf("pthread_join error, [job=%lu]\n", (unsigned long)jp->j_id);
//         }
        
//         tmp = jp;
//         jp = jp->j_next;
//         printf("job[%lu] work=%d\n", (unsigned long)tmp->j_id, tmp->j_work);
//         free(tmp);
//     }

//     queue_destroy(qp);
//     free(qp);

//     exit(0);
// }















// int main(void)
// {
//     int err;
//     struct timespec tout;
//     struct tm       *tmp;
//     char buf[64];
//     pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

//     pthread_mutex_lock(&lock);
//     printf("mutex lock is locked\n");

//     clock_gettime(CLOCK_REALTIME, &tout);
//     tmp = localtime(&tout.tv_sec);
//     strftime(buf, sizeof(buf), "%r", tmp);
//     printf("current time is %s\n", buf);

//     tout.tv_sec += 10;
//     err = pthread_mutex_timedlock(&lock, &tout);

//     clock_gettime(CLOCK_REALTIME, &tout);
//     tmp = localtime(&tout.tv_sec);
//     strftime(buf, sizeof(buf), "%r", tmp);
//     printf("the time is now %s\n", buf);

//     if (err == 0)
//         printf("mutex loecked again!\n");
//     else 
//         printf("can't lock mutex again:%s\n", strerror(err));

//     exit(0);
// }














// #define NHASH 29
// #define HASH(id) (((unsigned long)id) % NHASH)

// struct foo *fh[NHASH];

// pthread_mutex_t hashlock = PTHREAD_MUTEX_INITIALIZER;

// struct foo {
//     int             f_count;
//     pthread_mutex_t f_lock;
//     int             f_id;
//     struct foo      *f_next;
// };

// struct foo *foo_alloc(int id)
// {
//     struct foo *fp;
//     int         idx;

//     if ( (fp = malloc(sizeof(struct foo))) != NULL ) {
//         fp->f_count = 1;
//         fp->f_id = id;
//         if (pthread_mutex_init(&fp->f_lock, NULL) != 0) {
//             free(fp);
//             return (NULL);
//         }

//         idx = HASH(id);
//         pthread_mutex_lock(&hashlock);
//         fp->f_next = fh[idx];
//         fh[idx] = fp;
//         pthread_mutex_lock(&fp->f_lock);
//         pthread_mutex_unlock(&hashlock);

//         pthread_mutex_unlock(&fp->f_lock);
//     }

//     return (fp);
// }

// void foo_hold(struct foo *fp) 
// {
//     pthread_mutex_lock(&hashlock);
//     fp->f_count++;
//     pthread_mutex_unlock(&hashlock);
// }

// struct foo *foo_find(int id)
// {
//     struct foo *fp;

//     pthread_mutex_lock(&hashlock);

//     for (fp = fh[HASH(id)]; fp != NULL; fp = fp->f_next) {
//         if (fp->f_id == id) {
//             foo_hold(fp);
//             break;
//         }
//     }

//     pthread_mutex_unlock(&hashlock);

//     return (fp);
// }

// void foo_rele(struct foo *fp)
// {
//     struct foo *tfp;
//     int         idx;

//     pthread_mutex_lock(&hashlock);

//     if (--fp->f_count == 0) {
//         idx = HASH(fp->f_id);
//         tfp = fh[idx];
//         if (tfp == fp) {
//             fh[idx] = fp->f_next;
//         } else {
//             while(tfp->f_next != fp)
//                 tfp = tfp->f_next;
//             tfp->f_next = fp->f_next;
//         }
//         pthread_mutex_unlock(&hashlock);
//         pthread_mutex_destroy(&fp->f_lock);
//         free(fp);
//     } else {
//         pthread_mutex_unlock(&hashlock);
//     }
// }


// void *thread_func1(void *arg)
// {
//     printf("thread_func1 start...\n");

//     struct foo *fp = (struct foo *)arg;
//     foo_hold(fp);

//     sleep(2);
//     printf("thread_func1 mid...\n");

//     foo_rele(fp);

//     printf("thread_func1 end...\n");

//     return ((void *)0);
// }

// void *thread_func2(void *arg)
// {
//     printf("thread_func2 start...\n");

//     struct foo *fp = (struct foo *)arg;
//     foo_hold(fp);

//     sleep(3);
//     printf("thread_func2 mid...\n");

//     foo_rele(fp);

//     printf("thread_func2 end...\n");

//     return ((void *)0);
// }


// int main(void)
// {
//     pthread_t tid1, tid2;
//     struct foo *fp;

//     fp = foo_alloc(1);
//     if (fp == NULL) {
//         printf("foo_alloc error.\n");
//         return 1;
//     }

//     if (pthread_create(&tid1, NULL, thread_func1, (void *)fp) != 0)
//     {
//         printf("pthread_create 1 error.\n");
//         foo_rele(fp);
//         return 1;
//     }

//     if (pthread_create(&tid2, NULL, thread_func2, (void *)fp) != 0)
//     {
//         printf("pthread_create 2 error.\n");
//         foo_rele(fp);
//         return 1;
//     }

//     sleep(1);

//     printf("foo(id:%d, count:%d)\n", fp->f_id, fp->f_count);

//     if (pthread_join(tid1, NULL) != 0) {
//         printf("pthread_join tid1 error.\n");
//         foo_rele(fp);
//         return 1;
//     }

//     if (pthread_join(tid2, NULL) != 0) {
//         printf("pthread_join tid2 error.\n");
//         foo_rele(fp);
//         return 1;
//     }

//     foo_rele(fp);
//     return 0;
// }





// multi mutex
// #define NHASH 29
// #define HASH(id) (((unsigned long)id) % NHASH)

// struct foo *fh[NHASH];

// pthread_mutex_t hashlock = PTHREAD_MUTEX_INITIALIZER;

// struct foo {
//     int             f_count;
//     pthread_mutex_t f_lock;
//     int             f_id;
//     struct foo      *f_next;
// };

// struct foo *foo_alloc(int id)
// {
//     struct foo *fp;
//     int         idx;

//     if ( (fp = malloc(sizeof(struct foo))) != NULL ) {
//         fp->f_count = 1;
//         fp->f_id = id;
//         if (pthread_mutex_init(&fp->f_lock, NULL) != 0) {
//             free(fp);
//             return (NULL);
//         }

//         idx = HASH(id);
//         pthread_mutex_lock(&hashlock);
//         fp->f_next = fh[idx];
//         fh[idx] = fp;
//         pthread_mutex_lock(&fp->f_lock);
//         pthread_mutex_unlock(&hashlock);

//         pthread_mutex_unlock(&fp->f_lock);
//     }

//     return (fp);
// }

// void foo_hold(struct foo *fp) 
// {
//     pthread_mutex_lock(&fp->f_lock);
//     fp->f_count++;
//     pthread_mutex_unlock(&fp->f_lock);
// }

// struct foo *foo_find(int id)
// {
//     struct foo *fp;

//     pthread_mutex_lock(&hashlock);

//     for (fp = fh[HASH(id)]; fp != NULL; fp = fp->f_next) {
//         if (fp->f_id == id) {
//             foo_hold(fp);
//             break;
//         }
//     }

//     pthread_mutex_unlock(&hashlock);

//     return (fp);
// }

// void foo_rele(struct foo *fp)
// {
//     struct foo *tfp;
//     int         idx;

//     pthread_mutex_lock(&fp->f_lock);

//     if ( fp->f_count == 1 ) {
//         pthread_mutex_unlock(&fp->f_lock);
//         pthread_mutex_lock(&hashlock);
//         pthread_mutex_lock(&fp->f_lock);

//         if (fp->f_count != 1) {
//             fp->f_count--;
//             pthread_mutex_unlock(&fp->f_lock);
//             pthread_mutex_unlock(&hashlock);
//             return;
//         }

//         idx = HASH(fp->f_id);
//         tfp = fh[idx];
//         if (tfp == fp) {
//             fh[idx] = fp->f_next;
//         } else {
//             while(tfp->f_next != fp)
//                 tfp = tfp->f_next;
//             tfp->f_next = fp->f_next;
//         }
//         pthread_mutex_unlock(&hashlock);
//         pthread_mutex_unlock(&fp->f_lock);
//         pthread_mutex_destroy(&fp->f_lock);
//         free(fp);
//     } else {
//         fp->f_count--;
//         pthread_mutex_unlock(&fp->f_lock);
//     }
// }


// void *thread_func1(void *arg)
// {
//     printf("thread_func1 start...\n");

//     struct foo *fp = (struct foo *)arg;
//     foo_hold(fp);

//     sleep(2);
//     printf("thread_func1 mid...\n");

//     foo_rele(fp);

//     printf("thread_func1 end...\n");

//     return ((void *)0);
// }

// void *thread_func2(void *arg)
// {
//     printf("thread_func2 start...\n");

//     struct foo *fp = (struct foo *)arg;
//     foo_hold(fp);

//     sleep(3);
//     printf("thread_func2 mid...\n");

//     foo_rele(fp);

//     printf("thread_func2 end...\n");

//     return ((void *)0);
// }


// int main(void)
// {
//     pthread_t tid1, tid2;
//     struct foo *fp;

//     fp = foo_alloc(1);
//     if (fp == NULL) {
//         printf("foo_alloc error.\n");
//         return 1;
//     }

//     if (pthread_create(&tid1, NULL, thread_func1, (void *)fp) != 0)
//     {
//         printf("pthread_create 1 error.\n");
//         foo_rele(fp);
//         return 1;
//     }

//     if (pthread_create(&tid2, NULL, thread_func2, (void *)fp) != 0)
//     {
//         printf("pthread_create 2 error.\n");
//         foo_rele(fp);
//         return 1;
//     }

//     sleep(1);

//     printf("foo(id:%d, count:%d)\n", fp->f_id, fp->f_count);

//     if (pthread_join(tid1, NULL) != 0) {
//         printf("pthread_join tid1 error.\n");
//         foo_rele(fp);
//         return 1;
//     }

//     if (pthread_join(tid2, NULL) != 0) {
//         printf("pthread_join tid2 error.\n");
//         foo_rele(fp);
//         return 1;
//     }

//     foo_rele(fp);
//     return 0;
// }





// mutex
// struct foo {
//     int             f_count;
//     pthread_mutex_t f_lock;
//     int             f_id;
// };

// struct foo *foo_alloc(int id)
// {
//     struct foo *fp;

//     if ( (fp = malloc(sizeof(struct foo))) != NULL ) {
//         fp->f_count = 1;
//         fp->f_id = id;
//         if (pthread_mutex_init(&fp->f_lock, NULL) != 0) {
//             free(fp);
//             return (NULL);
//         }
//     }

//     return fp;
// }

// void foo_hold(struct foo *fp) 
// {
//     pthread_mutex_lock(&fp->f_lock);
//     fp->f_count++;
//     pthread_mutex_unlock(&fp->f_lock);
// }

// void foo_rele(struct foo *fp)
// {
//     pthread_mutex_lock(&fp->f_lock);

//     if ( (--fp->f_count) == 0 ) {
//         pthread_mutex_unlock(&fp->f_lock);
//         pthread_mutex_destroy(&fp->f_lock);
//         free(fp);
//     } else {
//         pthread_mutex_unlock(&fp->f_lock);
//     }
// }


// void *thread_func1(void *arg)
// {
//     printf("thread_func1 start...\n");

//     struct foo *fp = (struct foo *)arg;
//     foo_hold(fp);

//     sleep(2);
//     printf("thread_func1 mid...\n");

//     foo_rele(fp);

//     printf("thread_func1 end...\n");

//     return ((void *)0);
// }

// void *thread_func2(void *arg)
// {
//     printf("thread_func2 start...\n");

//     struct foo *fp = (struct foo *)arg;
//     foo_hold(fp);

//     sleep(3);
//     printf("thread_func2 mid...\n");

//     foo_rele(fp);

//     printf("thread_func2 end...\n");

//     return ((void *)0);
// }


// int main(void)
// {
//     pthread_t tid1, tid2;
//     struct foo *fp;

//     fp = foo_alloc(1);
//     if (fp == NULL) {
//         printf("foo_alloc error.\n");
//         return 1;
//     }

//     if (pthread_create(&tid1, NULL, thread_func1, (void *)fp) != 0)
//     {
//         printf("pthread_create 1 error.\n");
//         foo_rele(fp);
//         return 1;
//     }

//     if (pthread_create(&tid2, NULL, thread_func2, (void *)fp) != 0)
//     {
//         printf("pthread_create 2 error.\n");
//         foo_rele(fp);
//         return 1;
//     }

//     sleep(1);

//     printf("foo(id:%d, count:%d)\n", fp->f_id, fp->f_count);

//     if (pthread_join(tid1, NULL) != 0) {
//         printf("pthread_join tid1 error.\n");
//         foo_rele(fp);
//         return 1;
//     }

//     if (pthread_join(tid2, NULL) != 0) {
//         printf("pthread_join tid2 error.\n");
//         foo_rele(fp);
//         return 1;
//     }

//     foo_rele(fp);
//     return 0;
// }









// //pthread_t ntid;

// struct foo {
//     int a, b, c, d;
// };

// void printfoo(const char *s, const struct foo *fp)
// {
//     printf("%s", s);
//     printf("  structure at 0x%lx\n", (unsigned long)fp);
//     printf("  foo.a = %d\n", fp->a);
//     printf("  foo.b = %d\n", fp->b);
//     printf("  foo.c = %d\n", fp->c);
//     printf("  foo.d = %d\n", fp->d);
// }

// void printids(const char *s)
// {
//     pid_t     pid;
//     pthread_t tid;

//     pid = getpid();
//     tid = pthread_self();

//     printf("%s pid %lu tid %lu (0x%lx)\n", s, (unsigned long)pid, (unsigned long)tid, (unsigned long)tid);
// }

// void *thrd_func(void *arg)
// {
//     return ((void *)0);
// }

// void cleanup(void *arg)
// {
//     printf("cleanup: %s\n", (const char *)arg);
// }

// void *thread_func1(void *arg)
// {
//     printf("thread 1 start\n");
//     pthread_cleanup_push(cleanup, "thread 1 first cleanup");
//     pthread_cleanup_push(cleanup, "thread 1 second cleanup");
//     printf("thread 1 push complete\n");

//     if (arg)
//         return (arg);

//     pthread_cleanup_pop(0);
//     pthread_cleanup_pop(0);

//     return ((void *)1);

//     // struct foo fooret = { 1, 2, 3, 4 };
//     //
//     // printfoo("thread 1:\n", &fooret);
//     // pthread_exit((void *)&fooret);
// }

// void *thread_func2(void *arg)
// {
//     printf("thread 2 start\n");
//     pthread_cleanup_push(cleanup, "thread 2 first cleanup");
//     pthread_cleanup_push(cleanup, "thread 2 second cleanup");
//     printf("thread 2 push complete\n");

//     if (arg)
//         pthread_exit(arg);

//     pthread_cleanup_pop(0);
//     pthread_cleanup_pop(0);

//     pthread_exit((void *)2);

//     // printf("thread 2: ID is %lu\n", (unsigned long)pthread_self());
//     // pthread_exit((void *)0);
// }

// int main(void)
// {
//     int err;
//     pthread_t tid1, tid2;
//     //struct foo *fp;
//     void *tret;

//     err = pthread_create(&tid1, NULL, thread_func1, (void *)1);
//     if (err != 0) {
//         printf("thread 1 create error.\n");
//         exit(0);
//     }

//     err = pthread_join(tid1, tret);
//     if (err != 0) {
//         printf("join thread 1 error.\n");
//         exit(0);
//     }
//     printf("thread 1 exit code %ld\n", (long)tret);

//     err = pthread_create(&tid2, NULL, thread_func2, (void *)2);
//     if (err != 0) {
//         printf("thread 2 create error.\n");
//         exit(0);
//     }

//     err = pthread_join(tid2, &tret);
//     if (err != 0) {
//         printf("join thread 2 error.\n");
//         exit(0);
//     }
//     printf("thread 2 exit code %ld\n", (long)tret);

//     //sleep(1);
//     //
//     //printfoo("main thread:\n", fp);
//     //
//     // err = pthread_join(tid2, &tret);
//     // if (err != 0) {
//     //     printf("join thread 2 error.\n");
//     //     exit(0);
//     // }
//     // printf("thread 2 exit code %ld\n", (long)tret);
//     //
//     //
//     //err = pthread_create(&ntid, NULL, thrd_func, NULL);
//     //if (err != 0) {
//     //   printf("pthread_create error.\n");
//     //   exit(1);
//     // }
//     //
//     //printids("main thread: ");
//     //
//     //sleep(1);
    
//     exit(0);
// }