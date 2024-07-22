#include "../common/err_func.h"
#include "../common/wrap_sys_sockcall.h"
#include "../common/wrap_sys_proccall.h"
#include "../common/wrap_sys_iocall.h"

#define SERV_PORT 9877
#define OPEN_MAX  1024
#define INFTIM    -1 

int main(int argc, char **argv)
{
    int32_t i, maxi, listenfd, connfd, sockfd;
    int32_t nready;
    uint32_t n;
    int8_t buf[MAXLINE];
    PollFD client[OPEN_MAX];
    uint32_t clilen;
    SockAddrIn cliaddr, servaddr;

    listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

    Bind(listenfd, (SockAddr *)&servaddr, sizeof(servaddr));
    
    Listen(listenfd, LISTENQ);

    client[0].fd = listenfd;
    client[0].events = POLLRDNORM;
    for (i = 1; i < OPEN_MAX; i++)
        client[i].fd = -1;

    maxi = 0;
    for ( ; ; ) {
        nready = Poll(client, maxi + 1, INFTIM);

        if (client[0].revents & POLLRDNORM) {
            clilen = sizeof(cliaddr);
            connfd = Accept(listenfd, (SockAddr *)&cliaddr, &clilen);

            for (i = 1; i < OPEN_MAX; i++)
                if (client[i].fd < 0) {
                    client[i].fd = connfd;
                    break;
                }

            if (i == OPEN_MAX)
                err_quit("too many clients");

            client[i].events = POLLRDNORM;
            if (i > maxi)
                maxi = i;

            if (--nready <= 0)
                continue;
        }

        for (i = 0; i <= maxi; i++) {
            if ( (sockfd = client[i].fd) < 0)
                continue;

            if (client[i].revents & ( POLLRDNORM | POLLERR)) {
                if ( (n = read(sockfd, buf, MAXLINE)) < 0 ) {
                    if (errno == ECONNRESET) {
                        Close(sockfd);
                        client[i].fd = -1;
                    } else {
                        err_sys("read error");
                    }
                } else if (n == 0) {
                    Close(sockfd);
                    client[i].fd = -1;
                } else {
                    Writen(sockfd, buf, n);
                }

                if (--nready <= 0)
                    break;
            }
        }
    }
}