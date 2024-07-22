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
        Writen(sockfd, sendline, strlen(sendline));

        if (Readline(sockfd, recvline, MAXLINE) == 0)
            err_quit("str_cli: server terminated prematurely");

        Fputs(recvline, stdout);
    }
}


#define UNIXSTR_PATH "/tmp/unix.str"  

int main(int argc, char **argv)
{
    int32_t sockfd;
    SockAddrUn servaddr;

    sockfd = Socket(AF_LOCAL, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sun_family = AF_LOCAL;
    strncpy(servaddr.sun_path, UNIXSTR_PATH, sizeof(servaddr.sun_path) - 1);

    Connect(sockfd, (SockAddr *)&servaddr, sizeof(servaddr));

    str_cli(stdin, sockfd);

    exit(0);
}