#include "../common/err_func.h"
#include "../common/wrap_sys_sockcall.h"
#include "../common/wrap_sys_iocall.h"
#include <time.h>

int main(int argc, char **argv)
{
    int32_t listenfd, connfd;
    SockAddrIn servaddr;
    int8_t buff[MAXLINE];
    time_t ticks;

    listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(13);

    Bind(listenfd, (SockAddr *)&servaddr, sizeof(servaddr));
    
    Listen(listenfd, LISTENQ);

    for ( ; ; ) {
        connfd = Accept(listenfd, (SockAddr *)NULL, NULL);

        ticks = time(NULL);
        bzero(buff, sizeof(buff));
        snprintf(buff, sizeof(buff)-1, "%.24s\r\n", ctime(&ticks));
        Write(connfd, buff, strlen(buff));

        Close(connfd);
    }
}