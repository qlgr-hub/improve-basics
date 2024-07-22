#include "../common/err_func.h"
#include "../common/wrap_sys_sockcall.h"
#include "../common/wrap_sys_iocall.h"

#define SERV_PORT 9878

int main(int argc, char *argv[])
{
    int32_t  sockfd;
    uint32_t len;
    SockAddrIn servaddr, cliaddr;

    if (argc != 2)
        err_quit("usage: tcpcli <IPaddress>");

    sockfd = Socket(AF_INET, SOCK_DGRAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

    Connect(sockfd, (SockAddr *)&servaddr, sizeof(servaddr));

    len = sizeof(cliaddr);
    Getsockname(sockfd, (SockAddr *)&cliaddr, &len);
    printf("local address %s\n", Sock_ntop((SockAddr *)&cliaddr, len));

    exit(0);
}