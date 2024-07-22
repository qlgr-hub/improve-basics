#include "mylock.h"

pid_t lock_test(int32_t fd, int32_t type, off_t offset, int32_t whence, off_t len)
{
    struct flock lock;

    lock.l_type = type;        /* F_RDLCK, F_WRLCK, F_UNLCK */
    lock.l_start = offset;     /* byte offset, relative to l_whence */
    lock.l_whence = whence;    /* SEEK_SET, SEEK_CUR, SEEK_END */
    lock.l_len = len;          /* #bytes (0 means to EOF) */

    if ( fcntl(fd, F_GETLK, &lock) == -1 )
        return (-1);           /* unexpected error */

    if (lock.l_type == F_UNLCK)
        return (0);            /* fasle, region not locked by another proc */
    return (lock.l_pid);       /* true, return positive PID of lock owner */
}

pid_t Lock_test(int32_t fd, int32_t type, off_t offset, int32_t whence, off_t len)
{
    pid_t ret;
    if ( (ret = lock_test(fd, type, offset, whence, len)) == -1 )
    {
#ifdef _UNP_DEMO_
        err_sys("lock_test error");
#endif // _UNP_DEMO_
    }

    return (ret);
}