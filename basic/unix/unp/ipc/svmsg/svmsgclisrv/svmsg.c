#include "svmsg.h"
#include "../../../common/err_func.h"
#include "../../../common/wrap_sys_ipc.h"

int32_t mesg_send(int32_t id, struct mymesg *mptr)
{
    return (msgsnd(id, &(mptr->mesg_type), mptr->mesg_len, 0));
}

int32_t mesg_recv(int32_t id, struct mymesg *mptr)
{
    int32_t n;

    n = msgrcv(id, &(mptr->mesg_type), MAXMESGDATA, mptr->mesg_type, 0);
    mptr->mesg_len = n;

    return (n);
}


int32_t Mesg_send(int32_t id, struct mymesg *mptr)
{
    return mesg_send(id, mptr);
}

int32_t Mesg_recv(int32_t id, struct mymesg *mptr)
{
    int32_t n;

    do {
        n = mesg_recv(id, mptr);
    } while (n == -1 && errno == EINTR);

    if (n == -1)
        err_sys("mesg_recv error");

    return n;
}