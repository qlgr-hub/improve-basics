#ifndef _WRAP_SYS_PROCCALL_H_
#define _WRAP_SYS_PROCCALL_H_

#include "wrap_sys_type.h"

int32_t Fork();
int32_t Wait(int32_t *iptr);
int32_t Waitpid(int32_t pid, int32_t *iptr, int32_t options);

Sigfunc    *Signal(int32_t signo, Sigfunc *func);
Sigfunc    *Signal_intr(int signo, Sigfunc *func);
Sigfunc_rt *Signal_rt(int32_t signo, Sigfunc_rt *func, sigset_t *mask);
Sigfunc_rt *Signal_rt_intr(int32_t signo, Sigfunc_rt *func, sigset_t *mask);
int32_t Sigqueue(pid_t pid, int32_t signo, const union sigval value);
int32_t Sigwait(const sigset_t *set, int32_t *sig);
int32_t	Sigemptyset(sigset_t *set);
int32_t	Sigfillset(sigset_t *set);
int32_t	Sigaddset(sigset_t *set, int32_t signo);
int32_t	Sigdelset(sigset_t *set, int32_t signo);
int32_t	Sigismember(const sigset_t *set, int32_t signo);
int32_t	Sigpending(sigset_t *set);
int32_t	Sigprocmask(int32_t how, const sigset_t *set, sigset_t *oset);


int32_t daemon_init(const int8_t *pname, int32_t facility);

int8_t *Gf_time();

#endif // !_WRAP_SYS_PROCCALL_H_