#include "../../common/wrap_sys_type.h"
#include "../../common/wrap_sys_iocall.h"
#include "../../common/wrap_sys_ipc.h"
#include "../../common/err_func.h"
#include "../../common/wrap_std_alloc.h"
#include "../../common/wrap_sys_proccall.h"

int pipefd[2];
static void sig_usr1(int signo);

int main(int argc, char **argv)
{
    int nfds;
    int8_t c;
    fd_set rset;
    mqd_t mqd;
    void *buff;
    int32_t n;
    struct mq_attr attr;
    struct sigevent sigev;

    if (argc != 2)
        err_quit("usage: mqnotifysig2 <name>");

    mqd = Mq_open(argv[1], O_RDONLY | O_NONBLOCK);
    Mq_getattr(mqd, &attr);
    buff = Malloc(attr.mq_msgsize);

    Pipe(pipefd);

    Signal(SIGUSR1, sig_usr1);
    sigev.sigev_notify = SIGEV_SIGNAL;
    sigev.sigev_signo = SIGUSR1;
    Mq_notify(mqd, &sigev);

    for ( ; ; ) {
        FD_SET(pipefd[0], &rset);
        nfds = Select(pipefd[0] + 1, &rset, NULL, NULL, NULL);

        if (FD_ISSET(pipefd[0], &rset)) {
            Read(pipefd[0], &c, 1);

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

static void sig_usr1(int signo)
{
    Write(pipefd[1], "", 1);
    return;
}