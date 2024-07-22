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
        err_quit("usage: daytimecli03 <hostname/IPaddress> <service/port#>");

    sockfd = Udp_client(argv[1], argv[2], (SockAddr *)&ss, &len);

    printf("sending to %s  (%d)\n", Sock_ntop((SockAddr *)&ss, len), len);

    Sendto(sockfd, "", 1, 0, (SockAddr *)&ss, len);

    n = Recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL);
    recvline[n] = 0;
    Fputs(recvline, stdout);

    exit(0);
}