#include "../common/err_func.h"
#include "../common/wrap_sys_sockcall.h"
#include "../common/wrap_sys_proccall.h"

static void recvfrom_int(int32_t);
static int32_t count;

void dg_echo(int32_t sockfd, SockAddr *cliaddr, uint32_t clilen)
{
    uint32_t len;
    uint8_t  mesg[MAXLINE];

    Signal(SIGINT, recvfrom_int);

    for ( ; ; ) {
        len = clilen;
        Recvfrom(sockfd, mesg, MAXLINE, 0, cliaddr, &len);

        count++;
    }
}

static void recvfrom_int(int32_t signo)
{   
    printf("\nreceived %d datagrams\n", count);
    exit(0);
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