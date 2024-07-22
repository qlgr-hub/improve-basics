#include "../../common/wrap_sys_type.h"
#include "../../common/wrap_sys_iocall.h"
#include "../../common/wrap_sys_ipc.h"
#include "../../common/err_func.h"

int main(int argc, char **argv)
{
    if (argc != 2)
        err_quit("usage: mqunlink <name>");

    Mq_unlink(argv[1]);

    exit(0);
}