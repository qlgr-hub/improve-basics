#include "../common/err_func.h"
#include "../common/wrap_sys_sockcall.h"
#include "../common/wrap_sys_iocall.h"
#include "../common/wrap_sys_proccall.h"
#include "../common/utils.h"
#include <time.h>

extern int32_t daemon_proc;

int main(int argc, char **argv)
{
    int32_t sockfd;
    int32_t n;
    uint32_t len;
    int8_t buff[MAXLINE];
    time_t ticks;
    SockAddrStorage cliaddr;

    if (argc < 2 || argc > 3)
        err_quit("usage: daytimesrv03 [ <host> ] <service or port#>");

    daemon_init(argv[0], 0);

    if (argc == 2)
        sockfd = Udp_server(NULL, argv[1], NULL);
    else
        sockfd = Udp_server(argv[1], argv[2], NULL);
        

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