#include "../../common/wrap_sys_type.h"
#include "../../common/wrap_sys_iocall.h"
#include "../../common/wrap_sys_ipc.h"
#include "../../common/err_func.h"
#include "../../common/wrap_std_alloc.h"

#define MAXMSG (8192 + sizeof(long))

int main(int argc, char **argv)
{
    int32_t msqid;
    int32_t n;
    struct msgbuf *buff;

    if (argc != 2)
        err_quit("usage: msgrcvid <msqid>");

    msqid = atoi(argv[1]);

    buff = Malloc(MAXMSG);

    n = Msgrcv(msqid, buff, MAXMSG, 0, 0);
    printf("read %d bytes, type = %ld\n", n, buff->mtype);

    exit(0);
}