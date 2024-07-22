#include "../../common/err_func.h"
#include "../../common/wrap_sys_ipc.h"
#include "../../common/wrap_sys_iocall.h"
#include "../../common/wrap_sys_proccall.h"
#include "../../common/wrap_sys_sockcall.h"
#include "fifo_common.h"


int main(int argc, char *argv[])
{
    int32_t readfifo, writefifo, dummyfd, fd;
    int8_t  *ptr, buff[MAXLINE + 1], fifoname[MAXLINE];
    pid_t   pid;
    int32_t n;

    if ( (mkfifo(SERV_FIFO, FILE_MODE) < 0) && (errno != EEXIST) )
        err_sys("can't create %s", SERV_FIFO);

    readfifo = Open(SERV_FIFO, O_RDONLY, 0);
    dummyfd = Open(SERV_FIFO, O_WRONLY, 0);

    while ( (n = Readline(readfifo, buff, MAXLINE)) > 0 ) {
        if (buff[n - 1] == '\n')
            n--;
        buff[n] = '\0';

        if ( (ptr = strchr(buff, ' ')) == NULL ) {
            err_msg("bogus request: %s", buff);
            continue;
        }

        *ptr++ = 0;
        pid = atol(buff);
        snprintf(fifoname, sizeof(fifoname), "/tmp/fifo.%ld", (long)pid);
        if ( (writefifo = open(fifoname, O_WRONLY, 0)) < 0 ) {
            err_msg("cannot open: %s", fifoname);
            continue;
        }
        
        if ( (fd = open(ptr, O_RDONLY)) < 0 ) {
            snprintf(buff + n, sizeof(buff) - n, ": can't open, %s\n", strerror(errno));
            n = strlen(ptr);
            Write(writefifo, ptr, n);
            Close(writefifo);
        } else {
            while ( (n = Read(fd, buff, MAXLINE)) > 0 )
                Write(writefifo, buff, n);
            Close(fd);
            Close(writefifo);
        }
    }

    exit(0);
}