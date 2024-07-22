#include "../../common/err_func.h"
#include "../../common/wrap_sys_ipc.h"
#include "../../common/wrap_sys_iocall.h"
#include "../../common/wrap_sys_proccall.h"
#include "../../common/wrap_sys_sockcall.h"

int main(int argc, char *argv[])
{
    int    fd[2], n;
    int8_t c;
    pid_t  childpid;

    Pipe(fd);

    if ( (childpid = Fork()) == 0) {
        sleep(3);

        if ( (n = Read(fd[0], &c, 1)) != 1)
            err_quit("child: read returned %d", n);

        printf("child read %c\n", c);
        Write(fd[0], "c", 1);
        exit(0);
    }

    Write(fd[1], "p", 1);
    if ( (n = Read(fd[1], &c, 1)) != 1)
            err_quit("child: read returned %d", n);

    printf("parent read %c\n", c);
    exit(0);
}