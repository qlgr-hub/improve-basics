#include "../../common/wrap_sys_type.h"
#include "../../common/wrap_sys_iocall.h"
#include "../../common/wrap_sys_ipc.h"
#include "../../common/err_func.h"
#include "../../common/wrap_std_alloc.h"

int main(int argc, char **argv)
{
    int32_t c, flags;
    mqd_t mqd;
    int32_t n;
    uint32_t prio;
    void *buff;
    struct mq_attr attr;

    memset(&attr, 0, sizeof(attr));

    flags = O_RDONLY;
    while ( (c = Getopt(argc, argv, "n")) != -1 ) {
        switch (c) {
            case 'n':
                flags |= O_NONBLOCK;
                break;
        }
    }

    if (optind != argc - 1)
        err_quit("usage: mqreceive [ -n ] <name>");

    mqd = Mq_open(argv[optind], flags);
    Mq_getattr(mqd, &attr);

    buff = Malloc(attr.mq_msgsize);

    n = Mq_receive(mqd, buff, attr.mq_msgsize, &prio);
    printf("read %ld bytes, priority = %u\n", (long)n, prio);

    exit(0);
}