#include "wrap_sys_iocall.h"
#include "err_func.h"
#include <unistd.h>
#include <errno.h>

int32_t Open(const int8_t *path, int32_t oflag, mode_t mode)
{
    int32_t fd;
    if ( (fd = open(path, oflag, mode)) < 0 )
    {
#ifdef _UNP_DEMO_
        err_sys("open error");
#endif // _UNP_DEMO_
    }

    return fd;
}

int32_t Close(int32_t sockfd)
{
    int32_t ret;
    if ( (ret = close(sockfd)) < 0 )
    {
#ifdef _UNP_DEMO_
        err_sys("close error");
#endif // _UNP_DEMO_
    }

    return ret;
}

int32_t Unlink(const int8_t *path)
{
    int32_t ret;
    if ( (ret = unlink(path)) < 0 )
    {
#ifdef _UNP_DEMO_
        err_sys("unlink error");
#endif // _UNP_DEMO_
    }

    return ret;
}

int32_t Read(int32_t filedes, void *buff, uint32_t nbytes)
{
    int32_t ret;

    if ( (ret = read(filedes, buff, nbytes)) < 0 )
    {
#ifdef _UNP_DEMO_
        err_sys("read error");
#endif // _UNP_DEMO_
    }

    return ret;
}

int32_t Write(int32_t filedes, const void *buff, uint32_t nbytes)
{
    int32_t ret;

    if ( (ret = write(filedes, buff, nbytes)) < 0 )
    {
#ifdef _UNP_DEMO_
        err_sys("write error");
#endif // _UNP_DEMO_
    }

    return ret;
}

int32_t Readn(int32_t filedes, void *buff, uint32_t nbytes)
{
    int32_t nleft;
    int32_t nread;
    int8_t  *ptr;

    ptr = buff;
    nleft = nbytes;
    while (nleft > 0) {
        if ( (nread = Read(filedes, ptr, nleft)) < 0 ) {
            if (errno == EINTR)
                nread = 0;
            else 
                return (-1);
        } else if (nread == 0) {
            break;
        }

        nleft -= nread;
        ptr   += nread;
    }

    return (nbytes - nleft);
}

int32_t Writen(int32_t filedes, const void *buff, uint32_t nbytes)
{
    int32_t nleft;
    int32_t nwritten;
    const int8_t *ptr;

    ptr = buff;
    nleft = nbytes;
    while (nleft > 0) {
        if ( (nwritten = Write(filedes, ptr, nleft)) <= 0 ) {
            if (nwritten < 0 && errno == EINTR)
                nwritten = 0;
            else 
                return (-1);
        }

        nleft -= nwritten;
        ptr   += nwritten;
    }

    return (nbytes);
}

static int32_t readline(int32_t filedes, void *buff, uint32_t maxlen)
{
    int32_t n, rc;
    int8_t  c, *ptr;

    ptr = buff;
    for (n = 1; n < maxlen; n++) {
    again:
        if ( (rc = Read(filedes, &c, 1)) == 1 ) {
            *ptr++ = c;
            if (c == '\n')
                break;
        } else if (rc == 0) {
            *ptr = 0;
            return (n - 1);
        } else {
            if (errno == EINTR)
                goto again;
            return (-1);
        }
    }

    *ptr = 0;
    return (n);
}

static int32_t read_cnt;
static int8_t  *read_ptr;
static int8_t  read_buf[MAXLINE];

static int32_t my_read(int32_t fd, int8_t *ptr)
{
    if (read_cnt <= 0) {
    again:
        if ( (read_cnt = Read(fd, read_buf, sizeof(read_buf))) < 0) {
            if (errno == EINTR)
                goto again;
            return (-1);
        } else if (read_cnt == 0) {
            return (0);
        }

        read_ptr = read_buf;
    }

    read_cnt--;
    *ptr = *read_ptr++;
    return (1);
}

int32_t Readline(int32_t filedes, void *buff, uint32_t maxlen)
{
    int32_t n, rc;
    int8_t  c, *ptr;

    ptr = buff;
    for (n = 1; n < maxlen; n++) {
        if ( (rc = my_read(filedes, &c)) == 1 ) {
            *ptr++ = c;
            if (c == '\n')
                break;
        } else if (rc == 0) {
            *ptr = 0;
            return (n - 1);
        } else {
            return (-1);
        }
    }

    *ptr = 0;
    return (n);
}

static int32_t readlinebuf(void **vptrptr)
{
    if (read_cnt)
        *vptrptr = read_ptr;
    return (read_cnt);
}

int32_t Fclose(FILE *fp)
{
    int32_t ret;
	if ( (ret = fclose(fp)) != 0 )
    {
#ifdef _UNP_DEMO_
        err_sys("fclose error");
#endif // _UNP_DEMO_
    }

    return (ret);
}

FILE *Fdopen(int32_t fd, const int8_t *type)
{
	FILE *fp;

	if ( (fp = fdopen(fd, type)) == NULL )
	{
#ifdef _UNP_DEMO_
        err_sys("fdopen error");
#endif // _UNP_DEMO_
    }

	return (fp);
}

int8_t *Fgets(int8_t *ptr, int32_t n, FILE *stream)
{
	int8_t *rptr;

	if ( (rptr = fgets(ptr, n, stream)) == NULL && ferror(stream) )
	{
#ifdef _UNP_DEMO_
        err_sys("fgets error");
#endif // _UNP_DEMO_
    }

	return (rptr);
}

FILE *Fopen(const int8_t *filename, const int8_t *mode)
{
	FILE *fp;

	if ( (fp = fopen(filename, mode)) == NULL )
	{
#ifdef _UNP_DEMO_
        err_sys("fopen error");
#endif // _UNP_DEMO_
    }

	return(fp);
}

int32_t Fputs(const int8_t *ptr, FILE *stream)
{
    int32_t ret;
	if ( (ret = fputs(ptr, stream)) == EOF )
	{
#ifdef _UNP_DEMO_
        err_sys("fputs error");
#endif // _UNP_DEMO_
    }

    return (ret);
}

int32_t	Select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout)
{
    int32_t ret;
	if ( (ret = select(nfds, readfds, writefds, exceptfds, timeout)) < 0 )
	{
#ifdef _UNP_DEMO_
        err_sys("select error");
#endif // _UNP_DEMO_
    }

    return (ret);
}

int32_t Poll(PollFD *fdarray, uint64_t nfds, uint32_t timeout)
{
    int32_t ret;
	if ( (ret = poll(fdarray, nfds, timeout)) < 0 )
	{
#ifdef _UNP_DEMO_
        err_sys("poll error");
#endif // _UNP_DEMO_
    }

    return (ret);
}

int32_t Getopt(int32_t argc, int8_t *const *argv, const int8_t *str)
{
	int32_t	opt;

	if ( ( opt = getopt(argc, argv, str)) == '?')
		exit(1);		/* getopt() has already written to stderr */

	return(opt);
}

int32_t Fcntl(int32_t fd, int32_t cmd, void *arg)
{
    int32_t ret;
    if ( (ret = fcntl(fd, cmd, arg)) == -1 )
    {
#ifdef _UNP_DEMO_
        err_sys("fcntl error");
#endif // _UNP_DEMO_
    }

    return (ret);
}