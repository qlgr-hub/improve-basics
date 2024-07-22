#include "../../common/wrap_sys_type.h"
#include "../../common/wrap_sys_iocall.h"
#include "../../common/wrap_sys_ipc.h"
#include "../../common/err_func.h"


int main(int argc, char **argv)
{
    int32_t msqid;

    if (argc != 2)
        err_quit("usage: msgrmid <pathname>");

    msqid = Msgget(Ftok(argv[1], 0), 0);
    Msgctl(msqid, IPC_RMID, NULL);

    exit(0);
}