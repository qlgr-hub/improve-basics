#include "../../../common/err_func.h"
#include "../../../common/wrap_sys_ipc.h"
#include "../../../common/wrap_sys_iocall.h"
#include "../../../common/wrap_sys_proccall.h"
#include "svmsg.h"

void server(int32_t, int32_t);

int main(int argc, char *argv[])
{
    int32_t msqid;

    msqid = Msgget(MQ_KEY1, FILE_MODE | IPC_CREAT);

    server(msqid, msqid);

    exit(0);
}

void sig_chld(int signo)
{
    pid_t pid;
    int32_t stat;

    while ( (pid = waitpid(-1, &stat, WNOHANG)) > 0 );
    return;
}

void server(int32_t readid, int32_t writeid)
{
    FILE *fp;
    int8_t *ptr;
    pid_t pid;
    int32_t n;
    struct mymesg mesg;

    Signal(SIGCHLD, sig_chld);

    for ( ; ; ) {
        mesg.mesg_type = 1;
        if ( (n = Mesg_recv(readid, &mesg)) == 0 ) {
            err_msg("pathname missing");
            continue;
        }
        mesg.mesg_data[n] = '\0';

        if ( (ptr = strchr(mesg.mesg_data, ' ')) == NULL ) {
            err_msg("bogus request: %s", mesg.mesg_data);
            continue;
        }

        *ptr++ = 0;
        writeid = atoi(mesg.mesg_data);

        if (Fork() == 0) {
            if ( (fp = fopen(ptr, "r")) == NULL ) {
                snprintf(mesg.mesg_data + n, sizeof(mesg.mesg_data) - n, ": can't open, %s\n", strerror(errno));

                mesg.mesg_len = strlen(ptr);
                memmove(mesg.mesg_data, ptr, mesg.mesg_len);
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
            exit(0);
        }
    }
}