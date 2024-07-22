#include "../../common/wrap_sys_type.h"
#include "../../common/wrap_sys_iocall.h"
#include "../../common/wrap_sys_ipc.h"
#include "../../common/err_func.h"

#define MAX_DATA   64 * 1024
#define MAX_NMESG  4096
#define MAX_NIDS   40960
int     max_mesg;  

struct mymesg {
    long type;
    int8_t data[MAX_DATA];
} mesg;

int main(int argc, char **argv)
{
    int32_t i, j, msqid, qid[MAX_NIDS];

    msqid = Msgget(IPC_PRIVATE, FILE_MODE | IPC_CREAT);
    mesg.type = 1;

    for (i = MAX_DATA; i > 0; i -= 128) {
        if (msgsnd(msqid, &mesg, i, 0) == 0) {
            printf("maximum amount of data per message = %d\n", i);
            max_mesg = i;
            break;
        }
        if (errno != EINVAL)
            err_sys("msgsnd error for length %d", i);
    }
    if (i == 0)
        err_quit("i == 0");
    Msgctl(msqid, IPC_RMID, NULL);

    mesg.type = 1;
    for (i = 8; i <= max_mesg; i *= 2) {
        msqid = Msgget(IPC_PRIVATE, FILE_MODE | IPC_CREAT);
        for (j = 0; j < MAX_NMESG; j++) {
            if (msgsnd(msqid, &mesg, i, IPC_NOWAIT) != 0) {
                if (errno == EAGAIN)
                    break;
                err_sys("msgsnd error, i = %d, j = %d", i, j);
                break;
            }
        }
        printf("%d %d-byte messages were placed onto queue,", j, i);
        printf(" %d bytes total\n", i * j);
        Msgctl(msqid, IPC_RMID, NULL);
    }

    mesg.type = 1;
    for (i = 0; i <= MAX_NIDS; i++) {
        if ( (qid[i] = msgget(IPC_PRIVATE, FILE_MODE | IPC_CREAT)) == -1 ) {
            printf("%d identifiers open at once\n", i);
            break;
        }
    }
    for (j = 0; j < i; j++)
        Msgctl(qid[j], IPC_RMID, NULL);

    exit(0);
}