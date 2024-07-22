#include "../../common/err_func.h"
#include "../../common/wrap_sys_ipc.h"
#include "../../common/wrap_sys_iocall.h"
#include "../../common/wrap_sys_proccall.h"
#include "../../common/wrap_sys_sockcall.h"

void client(int32_t, int32_t), server(int32_t, int32_t);

int main(int argc, char *argv[])
{
    int    pipe1[2], pipe2[2];
    pid_t  childpid;

    Pipe(pipe1);
    Pipe(pipe2);

    if ( (childpid = Fork()) == 0) {
        Close(pipe1[1]);
        Close(pipe2[0]);

        server(pipe1[0], pipe2[1]);
        exit(0);
    }

    Close(pipe1[0]);
    Close(pipe2[1]);

    client(pipe2[0], pipe1[1]);

    Waitpid(childpid, NULL, 0);
    exit(0);
}

void client(int32_t readfd, int32_t writefd)
{
    uint32_t len;
    int32_t  n;
    int8_t   buff[MAXLINE];

    Fgets(buff, MAXLINE, stdin);
    len = strlen(buff);
    if (buff[len - 1] == '\n')
        len--;

    Write(writefd, buff, len);

    while ( (n = Read(readfd, buff, MAXLINE)) > 0 )
        Write(STDOUT_FILENO, buff, n);
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