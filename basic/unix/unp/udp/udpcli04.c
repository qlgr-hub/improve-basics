#include "../common/err_func.h"
#include "../common/wrap_sys_sockcall.h"
#include "../common/wrap_sys_iocall.h"

#define NDG   2000
#define DGLEN 1400 

void dg_cli(FILE *fp, int32_t sockfd, const SockAddr *servaddr, uint32_t addrlen)
{
    int32_t i;
    uint8_t sendline[DGLEN];

    Connect(sockfd, (SockAddr *)servaddr, addrlen);

    for (i = 0; i < NDG; i++) {
        Sendto(sockfd, sendline, DGLEN, 0, servaddr, addrlen);
    }
}

#define SERV_PORT 9878

int main(int argc, char *argv[])
{
    int32_t sockfd;
    SockAddrIn servaddr;

    if (argc != 2)
        err_quit("usage: tcpcli <IPaddress>");

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

    sockfd = Socket(AF_INET, SOCK_DGRAM, 0);

    dg_cli(stdin, sockfd, &servaddr, sizeof(servaddr));

    exit(0);
}