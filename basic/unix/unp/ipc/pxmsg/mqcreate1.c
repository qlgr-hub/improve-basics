#include "../../common/wrap_sys_type.h"
#include "../../common/wrap_sys_iocall.h"
#include "../../common/wrap_sys_ipc.h"
#include "../../common/err_func.h"

int main(int argc, char **argv)
{
    int32_t c, flags;
    mqd_t mqd;

    flags = O_RDWR | O_CREAT;
    while ( (c = Getopt(argc, argv, "e")) != -1 ) {
        switch (c) {
            case 'e':
                flags |= O_EXCL;
                break;
        }
    }

    if (optind != argc - 1)
        err_quit("usage: mqcreate [-e] <name>");

    mqd = Mq_open(argv[optind], flags, FILE_MODE, NULL);

    Mq_close(mqd);
    exit(0);
}