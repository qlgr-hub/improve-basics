#include "../common/err_func.h"
#include "../common/wrap_sys_sockcall.h"
#include "../common/wrap_sys_proccall.h"
#include "../common/wrap_sys_iocall.h"

int32_t my_open(const int8_t *pathname, int32_t mode);
int32_t read_fd(int32_t fd, void *ptr, uint32_t nbytes, int32_t *recvfd);

int main(int argc, char *argv[])
{
    int32_t fd, n;
    int8_t buff[BUFSIZE];

    if (argc != 2)
        err_quit("usage: mycat <pathname>");

    if ( (fd = my_open(argv[1], O_RDONLY)) < 0 )
        err_sys("cannot open %s", argv[1]);

    while ( (n = Read(fd, buff, BUFSIZE)) > 0 )
        Write(STDOUT_FILENO, buff, n);

    exit(0);
}


int32_t my_open(const int8_t *pathname, int32_t mode)
{
    int32_t fd, sockfd[2], status;
    pid_t childpid;
    int8_t c, argsockfd[10], argmode[10];

    Socketpair(AF_LOCAL, SOCK_STREAM, 0, sockfd);

    if ( (childpid = Fork()) == 0 ) {
        Close(sockfd[0]);

        snprintf(argsockfd, sizeof(argsockfd), "%d", sockfd[1]);
        snprintf(argmode, sizeof(argmode), "%d", mode);
        execl("./openfile", "openfile", argsockfd, pathname, argmode, (int8_t *)NULL);
        err_sys("execl error");
    }

    Close(sockfd[1]);

    Waitpid(childpid, &status, 0);
    if (WIFEXITED(status) == 0)
        err_quit("child did not terminate");
    if ( (status = WEXITSTATUS(status)) == 0 )
        read_fd(sockfd[0], &c, 1, &fd);
    else {
        errno = status;
        fd = -1;
    }

    Close(sockfd[0]);
    return (fd);
}


#define HAVE_MSGHDR_MSG_CONTROL
int32_t read_fd(int32_t fd, void *ptr, uint32_t nbytes, int32_t *recvfd)
{
    MsgHdr msg;
    IoVec  iov[1];
    int32_t n;

#ifdef HAVE_MSGHDR_MSG_CONTROL
    union {
        CMsgHdr cm;
        int8_t control[CMSG_SPACE(sizeof(int32_t))];
    } control_un;

    CMsgHdr *cmptr;

    msg.msg_control = control_un.control;
    msg.msg_controllen = sizeof(control_un.control);
#else
    int32_t newfd;

    msg.msg_accrights = (caddr_t)&newfd;
    msg.msg_accrightslen = sizeof(int32_t);
#endif // HAVE_MSGHDR_MSG_CONTROL

    msg.msg_name = NULL;
    msg.msg_namelen = 0;

    iov[0].iov_base = ptr;
    iov[0].iov_len = nbytes;
    msg.msg_iov = iov;
    msg.msg_iovlen = 1;

    if ( (n = recvmsg(fd, &msg, 0)) <= 0 )
        return (n);

#ifdef HAVE_MSGHDR_MSG_CONTROL
    if ( (cmptr = CMSG_FIRSTHDR(&msg)) != NULL && cmptr->cmsg_len == CMSG_LEN(sizeof(int32_t)) ) {
        if (cmptr->cmsg_level != SOL_SOCKET)
            err_quit("control level != SOL_SOCKET");
        if (cmptr->cmsg_type != SCM_RIGHTS)
            err_quit("control type != SCM_RIGHTS");
        *recvfd = *((int32_t *)CMSG_DATA(cmptr));
    } else
        *recvfd = -1;
#else
    if (msg.msg_accrightslen == sizeof(int32_t))
        *recvfd = newfd;
    else 
        *recvfd = -1;
#endif // HAVE_MSGHDR_MSG_CONTROL

    return (n);
}
