#ifndef _WRAP_SYS_IOCALL_H_
#define _WRAP_SYS_IOCALL_H_

#include "wrap_sys_type.h"

int32_t Open(const int8_t *path, int32_t oflag, mode_t mode);
int32_t Close(int32_t fd);
int32_t Unlink(const int8_t *path);

int32_t Read(int32_t filedes, void *buff, uint32_t nbytes);
int32_t Readn(int32_t filedes, void *buff, uint32_t nbytes);
int32_t Write(int32_t filedes, const void *buff, uint32_t nbytes);
int32_t Writen(int32_t filedes, const void *buff, uint32_t nbytes);
int32_t Readline(int32_t filedes, void *buff, uint32_t maxlen);

int32_t	 Fclose(FILE *fp);
FILE	*Fdopen(int32_t fd, const int8_t *type);
int8_t	*Fgets(int8_t *ptr, int32_t n, FILE *stream);
FILE	*Fopen(const int8_t *filename, const int8_t *mode);
int32_t	 Fputs(const int8_t *ptr, FILE *stream);


int32_t	Select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);
int32_t Poll(PollFD *fdarray, uint64_t nfds, uint32_t timeout);

int32_t Getopt(int32_t argc, int8_t *const *argv, const int8_t *str);

int32_t Fcntl(int32_t fd, int32_t cmd, void *arg);

#endif // !_WRAP_SYS_IOCALL_H_