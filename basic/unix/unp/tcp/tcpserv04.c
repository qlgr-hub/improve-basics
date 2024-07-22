#include "../common/err_func.h"
#include "../common/wrap_sys_sockcall.h"
#include "../common/wrap_sys_proccall.h"
#include "../common/wrap_sys_iocall.h"

void sig_chld(int32_t signo)
{
    int32_t pid;
    int32_t stat;

    while ( (pid = waitpid(-1, &stat, WNOHANG)) > 0 )
        printf("child %d terminated\n", pid);
    return;
}

void str_echo(int32_t sockfd)
{
    uint32_t n;
    int8_t   buf[MAXLINE];

again:
    while ( (n = Read(sockfd, buf, MAXLINE)) > 0 )
        Writen(sockfd, buf, n);

    if (n < 0 && errno == EINTR)
        goto again;
    else if (n < 0)
        err_sys("str_echo: read error");
}


#define SERV_PORT 9877

int main(int argc, char **argv)
{
    int32_t listenfd, connfd;
    int32_t childpid;
    uint32_t clilen;
    SockAddrIn cliaddr, servaddr;

    listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);
    Bind(listenfd, (SockAddr *)&servaddr, sizeof(servaddr));
    Listen(listenfd, LISTENQ);

    Signal(SIGCHLD, sig_chld);

    for ( ; ; ) {
        clilen = sizeof(cliaddr);
        //connfd = Accept(listenfd, (SockAddr *)&cliaddr, &clilen);
        if ( (connfd = accept(listenfd, (SockAddr *)&cliaddr, &clilen)) < 0 ) {
            if (errno == EINTR)
                continue;
            else
                err_sys("accept error");
        }

        if ( (childpid = Fork()) == 0 ) {
            Close(listenfd);
            str_echo(connfd);
            exit(0);
        }

        Close(connfd);
    }
}