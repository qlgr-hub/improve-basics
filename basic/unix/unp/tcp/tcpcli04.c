#include "../common/err_func.h"
#include "../common/wrap_sys_sockcall.h"
#include "../common/wrap_sys_proccall.h"
#include "../common/wrap_sys_iocall.h"
#include <strings.h>
#include <errno.h>
#include <stdio.h>

void str_cli(FILE *fp, int32_t sockfd)
{
    int8_t sendline[MAXLINE], recvline[MAXLINE];

    while (Fgets(sendline, MAXLINE, fp) != NULL) {
        Writen(sockfd, sendline, 1);
        sleep(1);
        Writen(sockfd, sendline + 1, strlen(sendline) - 1);

        if (Readline(sockfd, recvline, MAXLINE) == 0)
            err_quit("str_cli: server terminated prematurely");

        Fputs(recvline, stdout);
    }
}


#define SERV_PORT 9877

int main(int argc, char **argv)
{
    int32_t    sockfd;
    SockAddrIn servaddr;

    if (argc != 2)
        err_quit("usage: tcpcli <IPaddress>");

    sockfd = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

    Connect(sockfd, (SockAddr *)&servaddr, sizeof(servaddr));

    Signal(SIGPIPE, SIG_IGN);

    str_cli(stdin, sockfd);

    exit(0);
}