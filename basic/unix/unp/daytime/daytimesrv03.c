#include "../common/err_func.h"
#include "../common/wrap_sys_sockcall.h"
#include "../common/wrap_sys_iocall.h"
#include "../common/utils.h"
#include <time.h>

int main(int argc, char **argv)
{
    int32_t sockfd;
    int32_t n;
    uint32_t len;
    int8_t buff[MAXLINE];
    time_t ticks;
    SockAddrStorage cliaddr;

    if (argc == 2)
        sockfd = Udp_server(NULL, argv[1], NULL);
    else if (argc == 3)
        sockfd = Udp_server(argv[1], argv[2], NULL);
    else 
        err_quit("usage: daytimesrv03 [ <host> ] <service or port#>");

    for ( ; ; ) {
        len = sizeof(cliaddr);
        n = Recvfrom(sockfd, buff, MAXLINE, 0, (SockAddr *)&cliaddr, &len);
        printf("datagram from %s\n", Sock_ntop((SockAddr *)&cliaddr, len));

        ticks = time(NULL);
        bzero(buff, sizeof(buff));
        snprintf(buff, sizeof(buff)-1, "%.24s\r\n", ctime(&ticks));
        Sendto(sockfd, buff, strlen(buff), 0, (SockAddr *)&cliaddr, len);
    }
}