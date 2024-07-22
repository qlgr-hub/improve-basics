#include "../../common/err_func.h"
#include "../../common/wrap_sys_ipc.h"
#include "../../common/wrap_sys_iocall.h"
#include "../../common/wrap_sys_proccall.h"
#include "../../common/wrap_sys_sockcall.h"
#include "fifo_common.h"

void client(int32_t, int32_t);

int main(int argc, char *argv[])
{
    int32_t readfd, writefd;

    writefd = Open(FIFO1, O_WRONLY, 0);
    readfd = Open(FIFO2, O_RDONLY, 0);
    
    client(readfd, writefd);

    Close(readfd);
    Close(writefd);

    Unlink(FIFO1);
    Unlink(FIFO2);

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