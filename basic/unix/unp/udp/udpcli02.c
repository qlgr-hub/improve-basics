#include "../common/err_func.h"
#include "../common/wrap_sys_sockcall.h"
#include "../common/wrap_sys_iocall.h"
#include "../common/wrap_std_alloc.h"

void dg_cli(FILE *fp, int32_t sockfd, const SockAddr *servaddr, uint32_t addrlen)
{
    int32_t n;
    uint8_t sendline[MAXLINE], recvline[MAXLINE + 1];
    uint32_t len;
    SockAddr *reply_addr;

    reply_addr = Malloc(addrlen);

    while (Fgets(sendline, MAXLINE, fp) != NULL) {
        Sendto(sockfd, sendline, strlen(sendline), 0, servaddr, addrlen);

        len = addrlen;
        n = Recvfrom(sockfd, recvline, MAXLINE, 0, reply_addr, &len);
        if (len != addrlen || memcmp(servaddr, reply_addr, len) != 0) {
            printf("reply from %s (ignored)\n", Sock_ntop(reply_addr, len));
            continue;
        }

        recvline[n] = 0;
        Fputs(recvline, stdout);
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