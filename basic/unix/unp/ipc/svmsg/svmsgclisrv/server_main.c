#include "../../../common/err_func.h"
#include "../../../common/wrap_sys_ipc.h"
#include "../../../common/wrap_sys_iocall.h"
#include "svmsg.h"

void server(int32_t, int32_t);

int main(int argc, char *argv[])
{
    int32_t readid, writeid;

    readid = Msgget(MQ_KEY1, FILE_MODE | IPC_CREAT);
    writeid = Msgget(MQ_KEY2, FILE_MODE | IPC_CREAT);

    server(readid, writeid);

    exit(0);
}

void server(int32_t readid, int32_t writeid)
{
    FILE *fp;
    int32_t n;
    struct mymesg mesg;

    mesg.mesg_type = 1;
    if ( (n = Mesg_recv(readid, &mesg)) == 0 )
        err_quit("pathname missing");
    mesg.mesg_data[n] = '\0';

    if ( (fp = fopen(mesg.mesg_data, "r")) == NULL ) {
        snprintf(mesg.mesg_data + n, sizeof(mesg.mesg_data) - n, ": can't open, %s\n", strerror(errno));

        mesg.mesg_len = strlen(mesg.mesg_data);
        Mesg_send(writeid, &mesg);
    } else {
        while (Fgets(mesg.mesg_data, MAXMESGDATA, fp) != NULL) {
            mesg.mesg_len = strlen(mesg.mesg_data);
            Mesg_send(writeid, &mesg);
        }

        Fclose(fp);
    }

    mesg.mesg_len = 0;
    Mesg_send(writeid, &mesg);
}