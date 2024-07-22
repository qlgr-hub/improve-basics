#include "../../common/wrap_sys_type.h"
#include "../../common/wrap_sys_iocall.h"
#include "../../common/wrap_sys_ipc.h"
#include "../../common/err_func.h"
#include "../../common/wrap_std_alloc.h"

int main(int argc, char **argv)
{
    int32_t msqid;
    uint32_t len;
    long type;
    struct msgbuf *ptr;

    if (argc != 4)
        err_quit("usage: msgsnd <pathname> <#bytes> <type>");
    len = atoi(argv[2]);
    type = atoi(argv[3]);

    msqid = Msgget(Ftok(argv[1], 0), S_IWUSR);

    ptr = Calloc(sizeof(long) + len, sizeof(char));
    ptr->mtype = type;

    Msgsnd(msqid, ptr, len, 0);

    exit(0);
}