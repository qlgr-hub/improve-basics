#include "mylock.h"
#include <fcntl.h>
#include <stdio.h>
#include "../../common/wrap_sys_iocall.h"

void my_lock(int fd)
{
    struct flock lock;

    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;

    Fcntl(fd, F_SETLKW, &lock); // 此处如果换成F_SETLK 则fcntl返回错误不阻塞
}

void my_unlock(int fd)
{
    struct flock lock;

    lock.l_type = F_UNLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;

    Fcntl(fd, F_SETLK, &lock);
}