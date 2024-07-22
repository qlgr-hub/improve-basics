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

    if (argc == 2)
        listenfd = Tcp_listen(NULL, argv[1], NULL);
    else if (argc == 3)
        listenfd = Tcp_listen(argv[1], argv[2], NULL);
    else 
        err_quit("usage: daytimesrv02 [ <host> ] <service or port#>");

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