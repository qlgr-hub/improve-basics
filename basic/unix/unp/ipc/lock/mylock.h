#ifndef _LOCK_NONE_H_
#define _LOCK_NONE_H_

#include "../../common/wrap_sys_type.h"

#define Read_lock(fd, offset, whence, len) \
    Lock_reg(fd, F_SETLK, F_RDLCK, offset, whence, len)
#define Readw_lock(fd, offset, whence, len) \
    Lock_reg(fd, F_SETLKW, F_RDLCK, offset, whence, len)
#define Write_lock(fd, offset, whence, len) \
    Lock_reg(fd, F_SETLK, F_WRLCK, offset, whence, len)
#define Writew_lock(fd, offset, whence, len) \
    Lock_reg(fd, F_SETLKW, F_WRLCK, offset, whence, len)
#define Un_lock(fd, offset, whence, len) \
    Lock_reg(fd, F_SETLK, F_UNLCK, offset, whence, len)

#define Is_read_lockable(fd, offset, whence, len) \
    !Lock_test(fd, F_RDLCK, offset, whence, len)
#define Is_write_lockable(fd, offset, whence, len) \
    !Lock_test(fd, F_WRLCK, offset, whence, len)


void my_lock(int fd);
void my_unlock(int fd);

int32_t Lock_reg(int32_t fd, int32_t cmd, int32_t type, off_t offset, int32_t whence, off_t len);
pid_t   Lock_test(int32_t fd, int32_t type, off_t offset, int32_t whence, off_t len);

#endif // !_LOCK_NONE_H_