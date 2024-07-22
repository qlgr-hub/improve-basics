#include "../common/err_func.h"
#include "../common/wrap_sys_sockcall.h"
#include "../common/wrap_sys_iocall.h"
#include "../common/wrap_std_alloc.h"

void dg_cli(FILE *fp, int32_t sockfd, const SockAddr *servaddr, uint32_t addrlen)
{
    int32_t n;
    uint8_t sendline[MAXLINE], recvline[MAXLINE + 1];

    while (Fgets(sendline, MAXLINE, fp) != NULL) {
        Sendto(sockfd, sendline, strlen(sendline), 0, servaddr, addrlen);

        n = Recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL);

        recvline[n] = 0;
        Fputs(recvline, stdout);
    }
}

#define UNIXDG_PATH "/tmp/unix.dg"

int main(int argc, char *argv[])
{
    int32_t sockfd;
    SockAddrUn servaddr, cliaddr;

    sockfd = Socket(AF_LOCAL, SOCK_DGRAM, 0);

    bzero(&cliaddr, sizeof(cliaddr));
    cliaddr.sun_family = AF_LOCAL;
    strncpy(cliaddr.sun_path, tmpnam(NULL), sizeof(servaddr.sun_path) - 1);

    Bind(sockfd, (SockAddr *)&cliaddr, sizeof(cliaddr));

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sun_family = AF_LOCAL;
    strncpy(servaddr.sun_path, UNIXDG_PATH, sizeof(servaddr.sun_path) - 1);

    dg_cli(stdin, sockfd, &servaddr, sizeof(servaddr));

    exit(0);
}