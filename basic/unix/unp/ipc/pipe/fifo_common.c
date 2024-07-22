#include "fifo_common.h"
#include "../../common/err_func.h"
#include "../../common/wrap_sys_iocall.h"

int32_t mesg_send(int32_t fd, struct mymesg *mptr)
{
    return (Write(fd, mptr, MESGHDRSIZE + mptr->mesg_len));
}

int32_t mesg_recv(int32_t fd, struct mymesg *mptr)
{
    int32_t len;
    int32_t n;

    if ( (n = Read(fd, mptr, MESGHDRSIZE)) == 0 )
        return 0;
    else if (n != MESGHDRSIZE)
        err_quit("message header: expected %d, got %d", MESGHDRSIZE, n);

    if ( (len = mptr->mesg_len) > 0 )
        if ( (n = Read(fd, mptr->mesg_data, len)) != len )
            err_quit("message data: expected %d, got %d", len, n);

    return (len); 
}


int32_t Mesg_send(int32_t fd, struct mymesg *mptr)
{
    return mesg_send(fd, mptr);
}

int32_t Mesg_recv(int32_t fd, struct mymesg *mptr)
{
    return mesg_recv(fd, mptr);
}
