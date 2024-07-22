#include "../../common/wrap_sys_type.h"
#include "../../common/wrap_sys_iocall.h"
#include "../../common/wrap_sys_ipc.h"
#include "../../common/err_func.h"
#include "../../common/wrap_std_alloc.h"

#define MAXMSG (8192 + sizeof(long))

int main(int argc, char **argv)
{
    int32_t c, flag, msqid;
    long type;
    int32_t n;
    struct msgbuf *buff;

    type = flag = 0;
    while ( (c = Getopt(argc, argv, "nt:")) != -1 ) {
        switch (c) {
            case 'n':
                flag |= IPC_NOWAIT;
                break;
            case 't':
                type = atol(optarg);
                break;
        }
    }
    if (optind != argc - 1)
        err_quit("usage: msgrcv [ -n ] [ -t type ] <pathname>");

    msqid = Msgget(Ftok(argv[optind], 0), S_IRUSR);

    buff = Malloc(MAXMSG);

    n = Msgrcv(msqid, buff, MAXMSG, type, flag);
    printf("read %d bytes, type = %ld\n", n, buff->mtype);

    exit(0);
}