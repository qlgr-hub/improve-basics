#include "../../../common/err_func.h"
#include "../../../common/wrap_sys_ipc.h"
#include "../../../common/wrap_sys_iocall.h"
#include "svmsg.h"

void client(int32_t, int32_t);

int main(int argc, char *argv[])
{
    int32_t readid, writeid;

    writeid = Msgget(MQ_KEY1, 0);
    readid = Msgget(IPC_PRIVATE, FILE_MODE | IPC_CREAT);

    client(readid, writeid);

    Msgctl(readid, IPC_RMID, NULL);

    exit(0);
}

void client(int32_t readid, int32_t writeid)
{
    uint32_t len;
    int32_t  n;
    int8_t *ptr;
    struct mymesg mesg;

    snprintf(mesg.mesg_data, MAXMESGDATA, "%d ", readid);
    len = strlen(mesg.mesg_data);
    ptr = mesg.mesg_data + len;
    
    Fgets(ptr, MAXMESGDATA - len, stdin);
    len = strlen(mesg.mesg_data);
    if (mesg.mesg_data[len - 1] == '\n')
        len--;
    mesg.mesg_len = len;
    mesg.mesg_type = 1;

    Mesg_send(writeid, &mesg);

    while ( (n = Mesg_recv(readid, &mesg)) > 0 )
        Write(STDOUT_FILENO, mesg.mesg_data, n);
}