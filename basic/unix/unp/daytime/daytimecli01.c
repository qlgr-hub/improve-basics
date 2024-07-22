#include "../common/err_func.h"
#include "../common/wrap_sys_sockcall.h"
#include "../common/wrap_sys_iocall.h"
#include <arpa/inet.h>

int main(int argc, char **argv)
{
    int32_t sockfd, n;
    int8_t  recvline[MAXLINE + 1];
    SockAddrIn servaddr;
    InAddr  **pptr;
    InAddr  *inetaddrp[2];
    InAddr  inetaddr;
    Hostent *hp;
    Servent *sp;

    if (argc != 3)
        err_quit("usage: daytimecli01 <hostname> <service>");

    if ( (hp = gethostbyname(argv[1])) == NULL) {
        if (inet_aton(argv[1], &inetaddr) == 0) {
            err_quit("hostname error for %s: %s", argv[1], hstrerror(h_errno));
        } else {
            inetaddrp[0] = &inetaddr;
            inetaddrp[1] = NULL;
            pptr = inetaddrp;
        }
    } else {
        pptr = (InAddr **)hp->h_addr_list;
    }

    if ( (sp = getservbyname(argv[2], "tcp")) == NULL)
        err_quit("getservbyname error for %s", argv[2]);

    for ( ; *pptr != NULL; pptr++)
    {
        sockfd = Socket(AF_INET, SOCK_STREAM, 0);

        bzero(&servaddr, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        servaddr.sin_port = sp->s_port;
        memcpy(&servaddr.sin_addr, *pptr, sizeof(InAddr));
        printf("trying %s\n", Sock_ntop((SockAddr *)&servaddr, sizeof(servaddr)));

        if (connect(sockfd, (SockAddr *)&servaddr, sizeof(servaddr)) == 0)
            break;
        err_ret("connect error");
        Close(sockfd);
    }

    if (*pptr == NULL)
        err_quit("uable to connect");
    

    while ( (n = Read(sockfd, recvline, MAXLINE)) > 0 ) {
        recvline[n] = 0;
        Fputs(recvline, stdout);
    }

    exit(0);
}