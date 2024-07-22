#include "../../common/err_func.h"
#include "../../common/wrap_sys_ipc.h"
#include "../../common/wrap_sys_iocall.h"
#include "../../common/wrap_sys_proccall.h"
#include "../../common/wrap_sys_sockcall.h"
#include "fifo_common.h"

void server(int32_t, int32_t);

int main(int argc, char *argv[])
{
    int32_t readfd, writefd;

    if ( (mkfifo(FIFO1, FILE_MODE) < 0) && (errno != EEXIST) )
        err_sys("can't create %s", FIFO1);

    if ( (mkfifo(FIFO2, FILE_MODE) < 0) && (errno != EEXIST) ) {
        Unlink(FIFO1);

        err_sys("can't create %s", FIFO2);
    }

    readfd = Open(FIFO1, O_RDONLY, 0);
    writefd = Open(FIFO2, O_WRONLY, 0);

    server(readfd, writefd);
    exit(0);
}

void server(int32_t readfd, int32_t writefd)
{
    int32_t fd;
    int32_t n;
    int8_t  buff[MAXLINE + 1];

    if ( (n = Read(readfd, buff, MAXLINE)) == 0 )
        err_quit("end-of-file while reading pathname");
    buff[n] = '\0';

    if ( (fd = open(buff, O_RDONLY)) < 0 ) {
        snprintf(buff + n, sizeof(buff) - n, ": can't open, %s\n", strerror(errno));

        n = strlen(buff);
        Write(writefd, buff, n);
    } else {
        while ( (n = Read(fd, buff, MAXLINE)) > 0 )
            Write(writefd, buff, n);

        Close(fd);
    }
}