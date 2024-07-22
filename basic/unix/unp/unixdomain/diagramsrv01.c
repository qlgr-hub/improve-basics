#include "../common/err_func.h"
#include "../common/wrap_sys_sockcall.h"
#include "../common/wrap_sys_proccall.h"


void dg_echo(int32_t sockfd, SockAddr *cliaddr, uint32_t clilen)
{
    uint32_t len;
    uint8_t  mesg[MAXLINE];

    for ( ; ; ) {
        len = clilen;
        Recvfrom(sockfd, mesg, MAXLINE, 0, cliaddr, &len);

        Sendto(sockfd, mesg, strlen(mesg), 0, cliaddr, len);
    }
}

#define UNIXDG_PATH "/tmp/unix.dg"

int main(int argc, char *argv[])
{
    int32_t sockfd;
    SockAddrUn servaddr, cliaddr;

    sockfd = Socket(AF_LOCAL, SOCK_DGRAM, 0);

    unlink(UNIXDG_PATH);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sun_family = AF_LOCAL;
    strncpy(servaddr.sun_path, UNIXDG_PATH, sizeof(servaddr.sun_path) - 1);

    Bind(sockfd, (SockAddr *)&servaddr, sizeof(servaddr));

    dg_echo(sockfd, (SockAddr *)&cliaddr, sizeof(cliaddr));

    exit(0);
}