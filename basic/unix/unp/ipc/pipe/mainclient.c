#include "../../common/err_func.h"
#include "../../common/wrap_sys_ipc.h"
#include "../../common/wrap_sys_iocall.h"
#include "../../common/wrap_sys_proccall.h"
#include "../../common/wrap_sys_sockcall.h"
#include "fifo_common.h"


int main(int argc, char *argv[])
{
    int32_t  readfifo, writefifo;
    uint32_t len;
    int32_t  n;
    int8_t   *ptr, buff[MAXLINE], fifoname[MAXLINE];
    pid_t    pid;
    
    pid = getpid();
    snprintf(fifoname, sizeof(fifoname), "/tmp/fifo.%ld", (long)pid);
    if ( (mkfifo(fifoname, FILE_MODE) < 0) && (errno != EEXIST) )
        err_sys("can't create %s", fifoname);

    snprintf(buff, sizeof(buff), "%ld ", (long)pid);
    len = strlen(buff);
    ptr = buff + len;

    Fgets(ptr, MAXLINE - len, stdin);
    len = strlen(buff);

    writefifo = Open(SERV_FIFO, O_WRONLY, 0);
    Write(writefifo, buff, len);

    readfifo = Open(fifoname, O_RDONLY, 0);
    while ( (n = Read(readfifo, buff, MAXLINE)) > 0 )
        Write(STDOUT_FILENO, buff, n);

    Close(readfifo);
    Unlink(fifoname);
    exit(0);
}