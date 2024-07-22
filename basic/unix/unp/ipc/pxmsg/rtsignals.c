#include "../../common/wrap_sys_type.h"
#include "../../common/wrap_sys_iocall.h"
#include "../../common/wrap_sys_ipc.h"
#include "../../common/err_func.h"
#include "../../common/wrap_std_alloc.h"
#include "../../common/wrap_sys_proccall.h"

static void sig_rt(int32_t, siginfo_t *, void *);

int main(int argc, char **argv)
{
    int32_t i, j;
    pid_t pid;
    sigset_t newset;
    union sigval val;

    printf("SIGRTMIN = %d, SIGRTMAX = %d\n", (int)SIGRTMIN, (int)SIGRTMAX);

    if ( (pid = Fork()) == 0 ) {
        Sigemptyset(&newset);
        Sigaddset(&newset, SIGRTMAX);
        Sigaddset(&newset, SIGRTMAX - 1);
        Sigaddset(&newset, SIGRTMAX - 2);
        Sigprocmask(SIG_BLOCK, &newset, NULL);

        Signal_rt(SIGRTMAX, sig_rt, &newset);
        Signal_rt(SIGRTMAX - 1, sig_rt, &newset);
        Signal_rt(SIGRTMAX - 2, sig_rt, &newset);

        sleep(6);

        Sigprocmask(SIG_UNBLOCK, &newset, NULL);
        sleep(3);
        exit(0);
    }

    sleep(3);
    for (i = SIGRTMAX; i >= SIGRTMAX - 2; i--) {
        for (j = 0; j <= 2; j++) {
            val.sival_int = j;
            Sigqueue(pid, i, val);
            printf("sent signal %d, val = %d\n", i, j);
        }
    }
    exit(0);
}

static void sig_rt(int32_t signo, siginfo_t *info, void *context)
{
    printf("received signal #%d, code = %d, ival = %d\n", signo, info->si_code, info->si_value.sival_int);
}