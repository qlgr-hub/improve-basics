#include "../common/err_func.h"
#include "../common/wrap_sys_sockcall.h"
#include "../common/wrap_sys_iocall.h"
#include "../common/utils.h"
#include <time.h>

int main(int argc, char **argv)
{
    int32_t listenfd, connfd;
    uint32_t len;
    int8_t buff[MAXLINE];
    time_t ticks;
    SockAddrStorage cliaddr;

    if (argc != 2)
        err_quit("usage: daytimesrv01 <service or port#>");

    listenfd = Tcp_listen(NULL, argv[1], NULL);

    for ( ; ; ) {
        len = sizeof(cliaddr);
        connfd = Accept(listenfd, (SockAddr *)&cliaddr, &len);
        printf("connection from %s\n", Sock_ntop((SockAddr *)&cliaddr, len));

        ticks = time(NULL);
        bzero(buff, sizeof(buff));
        snprintf(buff, sizeof(buff)-1, "%.24s\r\n", ctime(&ticks));
        Write(connfd, buff, strlen(buff));

        Close(connfd);
    }
}