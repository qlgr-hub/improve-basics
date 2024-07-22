#include "../../common/wrap_sys_type.h"
#include "../../common/wrap_sys_iocall.h"
#include "../../common/wrap_sys_ipc.h"
#include "../../common/err_func.h"
#include "../../common/wrap_std_alloc.h"
#include "../../common/wrap_sys_proccall.h"

mqd_t mqd;
void *buff;
struct mq_attr attr;
struct sigevent sigev;

static void sig_usr1(int signo);

int main(int argc, char **argv)
{
    if (argc != 2)
        err_quit("usage: mqnotifysig1 <name>");

    mqd = Mq_open(argv[1], O_RDONLY);
    Mq_getattr(mqd, &attr);

    buff = Malloc(attr.mq_msgsize);

    Signal(SIGUSR1, sig_usr1);
    sigev.sigev_notify = SIGEV_SIGNAL;
    sigev.sigev_signo = SIGUSR1;
    Mq_notify(mqd, &sigev);

    for ( ; ; )
        pause();

    exit(0);
}

static void sig_usr1(int signo)
{
    int32_t n;
    Mq_notify(mqd, &sigev);
    n = Mq_receive(mqd, buff, attr.mq_msgsize, NULL);
    printf("SIGUSR1 received, read %ld, bytes\n", (long)n);
    return;
}