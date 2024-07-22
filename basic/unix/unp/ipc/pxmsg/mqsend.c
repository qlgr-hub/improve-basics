#include "../../common/wrap_sys_type.h"
#include "../../common/wrap_sys_iocall.h"
#include "../../common/wrap_sys_ipc.h"
#include "../../common/err_func.h"
#include "../../common/wrap_std_alloc.h"

int main(int argc, char **argv)
{
    mqd_t mqd;
    void  *ptr;
    uint32_t len;
    uint32_t prio;

    if (argc != 4)
        err_quit("usage: mqsend <name> <#bytes> <priority>");

    len = atoi(argv[2]);
    prio = atoi(argv[3]);

    mqd = Mq_open(argv[1], O_WRONLY);

    ptr = Calloc(len, sizeof(int8_t));
    Mq_send(mqd, ptr, len, prio);

    exit(0);
}