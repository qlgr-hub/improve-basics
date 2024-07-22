#include "../common/err_func.h"
#include "../common/wrap_sys_sockcall.h"
#include "../common/wrap_sys_proccall.h"
#include "../common/wrap_sys_iocall.h"

int32_t write_fd(int32_t fd, void *ptr, uint32_t nbytes, int32_t sendfd);

int	main(int argc, char **argv)
{
    int32_t fd;

    if (argc != 4)
        err_quit("openfile <sockfd#> <filename> <mode>");

    if ( (fd = open(argv[2], atoi(argv[3]))) < 0 )
        exit( (errno > 0) ? errno : 255 );

    if (write_fd(atoi(argv[1]), "", 1, fd) < 0)
        exit( (errno > 0) ? errno : 255 );

    exit(0);
}


#define HAVE_MSGHDR_MSG_CONTROL
int32_t write_fd(int32_t fd, void *ptr, uint32_t nbytes, int32_t sendfd)
{
    MsgHdr msg;
    IoVec  iov[1];

#ifdef HAVE_MSGHDR_MSG_CONTROL
    union {
        CMsgHdr cm;
        int8_t control[CMSG_SPACE(sizeof(int32_t))];
    } control_un;

    CMsgHdr *cmptr;

    msg.msg_control = control_un.control;
    msg.msg_controllen = sizeof(control_un.control);

    cmptr = CMSG_FIRSTHDR(&msg);
    cmptr->cmsg_len = CMSG_LEN(sizeof(int32_t));
    cmptr->cmsg_level = SOL_SOCKET;
    cmptr->cmsg_type = SCM_RIGHTS;
    *((int32_t *)CMSG_DATA(cmptr)) = sendfd;
#else
    msg.msg_accrights = (caddr_t)&sendfd;
    msg.msg_accrightslen = sizeof(int32_t);
#endif // HAVE_MSGHDR_MSG_CONTROL

    msg.msg_name = NULL;
    msg.msg_namelen = 0;

    iov[0].iov_base = ptr;
    iov[0].iov_len = nbytes;
    msg.msg_iov = iov;
    msg.msg_iovlen = 1;

    return (sendmsg(fd, &msg, 0));
}