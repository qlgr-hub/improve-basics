#include "wrap_sys_proccall.h"
#include <unistd.h>
#include <signal.h>
#include <syslog.h>

int32_t Fork()
{
    int32_t ret;
    if ( (ret = fork()) == -1 )
    {
#ifdef _UNP_DEMO_
        err_sys("fork error");
#endif // _UNP_DEMO_
    }

    return (ret);
}


int32_t Wait(int32_t *iptr)
{
	int32_t	pid;

	if ( (pid = wait(iptr)) == -1 )
    {
#ifdef _UNP_DEMO_
        err_sys("wait error");
#endif // _UNP_DEMO_
    }

	return (pid);
}

int32_t Waitpid(int32_t pid, int32_t *iptr, int32_t options)
{
	int32_t	retpid;

	if ( (retpid = waitpid(pid, iptr, options)) == -1 )
    {
#ifdef _UNP_DEMO_
        err_sys("waitpid error");
#endif // _UNP_DEMO_
    }

	return (retpid);
}

// 加static后会与系统自带的冲突 不会覆盖
/*static*/ Sigfunc *signal(int32_t signo, Sigfunc *func)
{
    struct sigaction act, oact;

    act.sa_handler = func;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    if (signo == SIGALRM) {
#ifdef SA_INTERRUPT
        act.sa_flags |= SA_INTERRUPT;   /* Sunos 4.x */
#endif // SA_INTERRUPT
    } else {
#ifdef SA_RESTART
        act.sa_flags |= SA_RESTART;     /* SVR4, 4.4BSD */
#endif // SA_RESTART
    }

    if (sigaction(signo, &act, &oact) < 0)
        return SIG_ERR;

    return (oact.sa_handler);
}

Sigfunc *Signal(int32_t signo, Sigfunc *func)
{
    Sigfunc *sigfunc;
    if ( (sigfunc = signal(signo, func)) == SIG_ERR )
    {
#ifdef _UNP_DEMO_
        err_sys("signal error");
#endif // _UNP_DEMO_
    }

    return (sigfunc);
}

Sigfunc *
signal_intr(int signo, Sigfunc *func)
{
	struct sigaction	act, oact;

	act.sa_handler = func;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;

#ifdef	SA_INTERRUPT
	act.sa_flags |= SA_INTERRUPT;   /* Sunos 4.x */
#endif

	if (sigaction(signo, &act, &oact) < 0)
		return (SIG_ERR);

	return (oact.sa_handler);
}
/* end signal_intr */

Sigfunc *Signal_intr(int signo, Sigfunc *func)
{
	Sigfunc	*sigfunc;

	if ( (sigfunc = signal_intr(signo, func)) == SIG_ERR)
    {
#ifdef _UNP_DEMO_
        err_sys("signal_intr error");
#endif // _UNP_DEMO_
    }

	return(sigfunc);
}

static Sigfunc_rt *signal_rt(int32_t signo, Sigfunc_rt *func, sigset_t *mask)
{
    struct sigaction act, oact;

    act.sa_sigaction = func;
    act.sa_mask = *mask;
    act.sa_flags = SA_SIGINFO;

    if (signo == SIGALRM) {
#ifdef SA_INTERRUPT
        act.sa_flags |= SA_INTERRUPT;   /* Sunos 4.x */
#endif // SA_INTERRUPT
    } else {
#ifdef SA_RESTART
        act.sa_flags |= SA_RESTART;     /* SVR4, 4.4BSD */
#endif // SA_RESTART
    }

    if (sigaction(signo, &act, &oact) < 0)
        return (Sigfunc_rt *)SIG_ERR;

    return (oact.sa_sigaction);
}

Sigfunc_rt *Signal_rt(int32_t signo, Sigfunc_rt *func, sigset_t *mask)
{
    Sigfunc_rt	*sigfunc;

	if ( (sigfunc = signal_rt(signo, func, mask)) == (Sigfunc_rt *) SIG_ERR)
	{
#ifdef _UNP_DEMO_
        err_sys("signal_rt error");
#endif // _UNP_DEMO_
    }

	return(sigfunc);
}

static Sigfunc_rt *signal_rt_intr(int32_t signo, Sigfunc_rt *func, sigset_t *mask)
{
    struct sigaction act, oact;

    act.sa_sigaction = func;
    act.sa_mask = *mask;
    act.sa_flags = SA_SIGINFO;

#ifdef SA_INTERRUPT
    act.sa_flags |= SA_INTERRUPT;   /* Sunos 4.x */
#endif // SA_INTERRUPT

    if (sigaction(signo, &act, &oact) < 0)
        return (Sigfunc_rt *)SIG_ERR;

    return (oact.sa_sigaction);
}

Sigfunc_rt *Signal_rt_intr(int32_t signo, Sigfunc_rt *func, sigset_t *mask)
{
    Sigfunc_rt	*sigfunc;

	if ( (sigfunc = signal_rt_intr(signo, func, mask)) == (Sigfunc_rt *) SIG_ERR)
	{
#ifdef _UNP_DEMO_
        err_sys("signal_rt_intr error");
#endif // _UNP_DEMO_
    }

	return(sigfunc);
}

int32_t Sigqueue(pid_t pid, int32_t signo, const union sigval value)
{
    int32_t	err;

	if ( (err = sigqueue(pid, signo, value)) == -1 )
    {
#ifdef _UNP_DEMO_
        err_sys("sigqueue error");
#endif // _UNP_DEMO_
    }

	return (err);
}

int32_t Sigwait(const sigset_t *set, int32_t *sig)
{
    int32_t	err;

	if ( (err = sigwait(set, sig)) != 0 )
    {
#ifdef _UNP_DEMO_
        errno = err;
        err_sys("sigwait error");
#endif // _UNP_DEMO_
    }

	return (err);
}

int32_t	Sigemptyset(sigset_t *set)
{
    int32_t	err;

	if ( (err = sigemptyset(set)) == -1 )
    {
#ifdef _UNP_DEMO_
        err_sys("sigemptyset error");
#endif // _UNP_DEMO_
    }

	return (err);
}

int32_t	Sigfillset(sigset_t *set)
{
    int32_t	err;

	if ( (err = sigfillset(set)) == -1 )
    {
#ifdef _UNP_DEMO_
        err_sys("sigfillset error");
#endif // _UNP_DEMO_
    }

	return (err);
}

int32_t	Sigaddset(sigset_t *set, int32_t signo)
{
    int32_t	err;

	if ( (err = sigaddset(set, signo)) == -1 )
    {
#ifdef _UNP_DEMO_
        err_sys("sigaddset error");
#endif // _UNP_DEMO_
    }

	return (err);
}

int32_t	Sigdelset(sigset_t *set, int32_t signo)
{
    int32_t	err;

	if ( (err = sigdelset(set, signo)) == -1 )
    {
#ifdef _UNP_DEMO_
        err_sys("sigdelset error");
#endif // _UNP_DEMO_
    }

	return (err);
}

int32_t	Sigismember(const sigset_t *set, int32_t signo)
{
    int32_t	err;

	if ( (err = sigismember(set, signo)) == -1 )
    {
#ifdef _UNP_DEMO_
        err_sys("sigismember error");
#endif // _UNP_DEMO_
    }

	return (err);
}

int32_t	Sigpending(sigset_t *set)
{
    int32_t	err;

	if ( (err = sigpending(set)) == -1 )
    {
#ifdef _UNP_DEMO_
        err_sys("sigpending error");
#endif // _UNP_DEMO_
    }

	return (err);
}

int32_t	Sigprocmask(int32_t how, const sigset_t *set, sigset_t *oset)
{
    int32_t	err;

	if ( (err = sigprocmask(how, set, oset)) == -1 )
    {
#ifdef _UNP_DEMO_
        err_sys("sigprocmask error");
#endif // _UNP_DEMO_
    }

	return (err);
}

#define MAXFD 64 
extern int32_t daemon_proc;

int32_t daemon_init(const int8_t *pname, int32_t facility)
{
    int32_t i;
    pid_t pid;

    if ( (pid = Fork()) < 0 )
        return (-1);
    else if (pid)
        _exit(0);

    if (setsid() < 0)
        return -1;
    
    Signal(SIGHUP, SIG_IGN);

    if ( (pid = Fork()) < 0 )
        return (-1);
    else if (pid)
        _exit(0);

    daemon_proc = 1;

    chdir("/");

    for (i = 0; i < MAXFD; i++)
        close(i);

    open("/dev/null", O_RDONLY);
    open("/dev/null", O_RDWR);
    open("/dev/null", O_RDWR);

    openlog(pname, LOG_PID, facility);

    return (0);
}

int8_t *gf_time()
{
    struct timeval	tv;
	static int8_t	str[30];
	int8_t			*ptr;

	if (gettimeofday(&tv, NULL) < 0)
		err_sys("gettimeofday error");

	ptr = ctime(&tv.tv_sec);
	strcpy(str, &ptr[11]);
		/* Fri Sep 13 00:00:00 1986\n\0 */
		/* 0123456789012345678901234 5  */
	snprintf(str+8, sizeof(str)-8, ".%06ld", tv.tv_usec);

	return(str);
}

int8_t *Gf_time()
{
	return (gf_time());
}