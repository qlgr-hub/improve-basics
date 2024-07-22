#include "../../common/wrap_sys_type.h"
#include "../../common/wrap_sys_iocall.h"
#include "../../common/wrap_sys_ipc.h"
#include "../../common/err_func.h"
#include "../../common/wrap_std_alloc.h"
#include "../../common/wrap_sys_proccall.h"

int main(int argc, char **argv)
{
    int32_t signo;
    mqd_t mqd;
    void *buff;
    int32_t n;
    sigset_t newmask;
    struct mq_attr attr;
    struct sigevent sigev;

    if (argc != 2)
        err_quit("usage: mqnotifysig2 <name>");

    mqd = Mq_open(argv[1], O_RDONLY | O_NONBLOCK);
    Mq_getattr(mqd, &attr);
    buff = Malloc(attr.mq_msgsize);

    Sigemptyset(&newmask);
    Sigaddset(&newmask, SIGUSR1);
    Sigprocmask(SIG_BLOCK, &newmask, NULL);

    sigev.sigev_notify = SIGEV_SIGNAL;
    sigev.sigev_signo = SIGUSR1;
    Mq_notify(mqd, &sigev);

    for ( ; ; ) {
        Sigwait(&newmask, &signo);
        if (SIGUSR1 == signo) {
            Mq_notify(mqd, &sigev);
            while ( (n = mq_receive(mqd, buff, attr.mq_msgsize, NULL)) >= 0 ) {
                printf("read %ld, bytes\n", (long)n);
            }
            if (errno != EAGAIN)
                err_sys("mq_receive error");
        }
    }

    exit(0);
}