#include "../common/err_func.h"
#include "../common/wrap_sys_sockcall.h"
#include "../common/utils.h"
#include "../common/wrap_sys_iocall.h"
#include <arpa/inet.h>

int main(int argc, char **argv)
{
    int32_t sockfd, n;
    int8_t  recvline[MAXLINE + 1];
    SockAddrStorage ss;
    uint32_t len;

    if (argc != 3)
        err_quit("usage: daytimecli02 <hostname/IPaddress> <service/port#>");

    sockfd = Tcp_connect(argv[1], argv[2]);

    len = sizeof(ss);
    Getpeername(sockfd, (SockAddr *)&ss, &len);
    printf("connected to %s\n", Sock_ntop_host((SockAddr *)&ss, len));

    while ( (n = Read(sockfd, recvline, MAXLINE)) > 0 ) {
        recvline[n] = 0;
        Fputs(recvline, stdout);
    }

    exit(0);
}