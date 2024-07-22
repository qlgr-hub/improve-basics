#include "../../common/wrap_sys_type.h"
#include "../../common/wrap_sys_iocall.h"
#include "../../common/wrap_sys_ipc.h"
#include "../../common/err_func.h"


int main(int argc, char **argv)
{
    int32_t msqid;
    struct msqid_ds info;
    struct msgbuf   buf;

    msqid = Msgget(IPC_PRIVATE, FILE_MODE | IPC_CREAT);

    buf.mtype = 1;
    buf.mtext[0] = 1;
    Msgsnd(msqid, &buf, 1, 0);

    Msgctl(msqid, IPC_STAT, &info);
    printf("read-write: %03o, cbytes = %lu, qnum = %lu, qbytes = %lu\n",
        info.msg_perm.mode & 0777, (ulong)info.msg_cbytes,
        (ulong)info.msg_qnum, (ulong)info.msg_qbytes);

    system("ipcs -q");

    Msgctl(msqid, IPC_RMID, NULL);

    exit(0);
}