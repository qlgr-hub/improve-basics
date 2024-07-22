#include "../common/err_func.h"
#include "../common/wrap_sys_sockcall.h"

void dg_echo(int32_t sockfd, SockAddr *cliaddr, uint32_t clilen)
{
    int32_t  n;
    uint32_t len;
    uint8_t  mesg[MAXLINE];

    for ( ; ; ) {
        len = clilen;
        n = Recvfrom(sockfd, mesg, MAXLINE, 0, cliaddr, &len);

        Sendto(sockfd, mesg, n, 0, cliaddr, len); 
    }
}

#define SERV_PORT 9878

int main(int argc, char *argv[])
{
    int32_t sockfd;
    SockAddrIn servaddr, cliaddr;

    sockfd = Socket(AF_INET, SOCK_DGRAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

    Bind(sockfd, (SockAddr *)&servaddr, sizeof(servaddr));

    dg_echo(sockfd, (SockAddr *)&cliaddr, sizeof(cliaddr));

    exit(0);
}