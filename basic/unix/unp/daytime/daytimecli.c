#include "../common/err_func.h"
#include "../common/wrap_sys_sockcall.h"


int main(int argc, char **argv)
{
    int32_t sockfd, n;
    int8_t  recvline[MAXLINE];
    SockAddrIn servaddr;

    if (argc != 2)
        err_quit("usage: daytimecli <IPaddress>");

    sockfd = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(13);
    Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

    Connect(sockfd, (SockAddr *)&servaddr, sizeof(servaddr));

    while ( (n = read(sockfd, recvline, MAXLINE)) > 0 ) {
        recvline[n] = 0;
        if (fputs(recvline, stdout) == EOF)
            err_sys("fputs error");
    }

    if (n < 0)
        err_sys("read error");

    exit(0);
}