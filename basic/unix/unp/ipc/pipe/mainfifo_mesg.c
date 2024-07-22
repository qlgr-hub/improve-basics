#include "../../common/err_func.h"
#include "../../common/wrap_sys_ipc.h"
#include "../../common/wrap_sys_iocall.h"
#include "../../common/wrap_sys_proccall.h"
#include "../../common/wrap_sys_sockcall.h"
#include "fifo_common.h"

#define FIFO1  "/tmp/fifo.1"
#define FIFO2  "/tmp/fifo.2"  

void client(int32_t, int32_t), server(int32_t, int32_t);

int main(int argc, char *argv[])
{
    int32_t readfd, writefd;
    pid_t   childpid;

    if ( (mkfifo(FIFO1, FILE_MODE) < 0) && (errno != EEXIST) )
        err_sys("can't create %s", FIFO1);

    if ( (mkfifo(FIFO2, FILE_MODE) < 0) && (errno != EEXIST) ) {
        Unlink(FIFO1);

        err_sys("can't create %s", FIFO2);
    }

    if ( (childpid = Fork()) == 0) {
        readfd = Open(FIFO1, O_RDONLY, 0);
        writefd = Open(FIFO2, O_WRONLY, 0);

        server(readfd, writefd);
        exit(0);
    }

    writefd = Open(FIFO1, O_WRONLY, 0);
    readfd = Open(FIFO2, O_RDONLY, 0);
    

    client(readfd, writefd);

    Waitpid(childpid, NULL, 0);

    Close(readfd);
    Close(writefd);

    Unlink(FIFO1);
    Unlink(FIFO2);

    exit(0);
}

void client(int32_t readfd, int32_t writefd)
{
    uint32_t len;
    int32_t  n;
    struct mymesg mesg;

    Fgets(mesg.mesg_data, MAXMESGDATA, stdin);
    len = strlen(mesg.mesg_data);
    if (mesg.mesg_data[len - 1] == '\n')
        len--;
    mesg.mesg_len = len;
    mesg.mesg_type = 1;

    Mesg_send(writefd, &mesg);

    while ( (n = Mesg_recv(readfd, &mesg)) > 0 )
        Write(STDOUT_FILENO, mesg.mesg_data, n);
}

void server(int32_t readfd, int32_t writefd)
{
    FILE *fp;
    int32_t n;
    struct mymesg mesg;

    mesg.mesg_type = 1;
    if ( (n = Mesg_recv(readfd, &mesg)) == 0 )
        err_quit("pathname missing");
    mesg.mesg_data[n] = '\0';

    if ( (fp = Fopen(mesg.mesg_data, "r")) == NULL ) {
        snprintf(mesg.mesg_data + n, sizeof(mesg.mesg_data) - n, ": can't open, %s\n", strerror(errno));

        mesg.mesg_len = strlen(mesg.mesg_data);
        Mesg_send(writefd, &mesg);
    } else {
        while (Fgets(mesg.mesg_data, MAXMESGDATA, fp) != NULL) {
            mesg.mesg_len = strlen(mesg.mesg_data);
            Mesg_send(writefd, &mesg);
        }

        Fclose(fp);
    }

    mesg.mesg_len = 0;
    Mesg_send(writefd, &mesg);
}