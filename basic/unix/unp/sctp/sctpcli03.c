#include "../common/err_func.h"
#include "../common/wrap_sys_sockcall.h"
#include "../common/wrap_sys_iocall.h"

void sctpstr_cli(FILE *fp, int32_t sockfd, SockAddr *to, uint32_t tolen);
void sctpstr_cli_echoall(FILE *fp, int32_t sockfd, SockAddr *to, uint32_t tolen);

#define SERV_PORT 9879

int main(int argc, char *argv[])
{
    int32_t sockfd;
    SockAddrIn servaddr;
    SctpEventSubscribe events;
    int32_t echo_to_all = 0;
    int8_t byemsg[10];

    if (argc < 2)
        err_quit("Missing host argument - use '%s host [echo]'\n", argv[0]);
    if (argc > 2) {
        printf("Echoing messages to all streams\n");
        echo_to_all = 1;
    }

    sockfd = Socket(AF_INET, SOCK_SEQPACKET, IPPROTO_SCTP);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);
    Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

    bzero(&events, sizeof(events));
    events.sctp_data_io_event = 1;
    Setsockopt(sockfd, IPPROTO_SCTP, SCTP_EVENTS, &events, sizeof(events));

    if (echo_to_all == 0)
        sctpstr_cli(stdin, sockfd, (SockAddr *)&servaddr, sizeof(servaddr));
    else
        sctpstr_cli_echoall(stdin, sockfd, (SockAddr *)&servaddr, sizeof(servaddr));

    strncpy(byemsg, "goodbye", strlen("goodbye"));
    Sctp_sendmsg(sockfd, byemsg, strlen(byemsg), (SockAddr *)&servaddr, sizeof(servaddr), 0, SCTP_ABORT, 0, 0, 0);

    Close(sockfd);
    return (0);
}

void sctpstr_cli(FILE *fp, int32_t sockfd, SockAddr *to, uint32_t tolen)
{
    SockAddrIn peeraddr;
    SctpSndRcvInfo sri;
    int8_t sendline[MAXLINE], recvline[MAXLINE];
    uint32_t len;
    int32_t out_sz, rd_sz;
    int32_t msg_flags;

    bzero(&sri, sizeof(sri));
    while (fgets(sendline, MAXLINE, fp) != NULL) {
        if (sendline[0] != '[') {
            printf("Error, line must be of the form '[streamnum]text'\n");
            continue;
        }

        sri.sinfo_stream = strtol(&sendline[1], NULL, 0);
        out_sz = strlen(sendline);
        Sctp_sendmsg(sockfd, sendline, out_sz, to, tolen, 0, 0, sri.sinfo_stream, 0, 0);

        len = sizeof(peeraddr);
        rd_sz = Sctp_recvmsg(sockfd, recvline, sizeof(recvline), (SockAddr *)&peeraddr, &len, &sri, &msg_flags);

        printf("From str:%d seq:%d (assoc:0x%x):", sri.sinfo_stream, sri.sinfo_ssn, (uint32_t)sri.sinfo_assoc_id);
        printf("%.*s", rd_sz, recvline);
    }
}

#define	SCTP_MAXLINE        800
#define SERV_MAX_SCTP_STRM	10

void sctpstr_cli_echoall(FILE *fp, int32_t sockfd, SockAddr *to, uint32_t tolen)
{
    SockAddrIn peeraddr;
    SctpSndRcvInfo sri;
    int8_t sendline[SCTP_MAXLINE], recvline[SCTP_MAXLINE];
    uint32_t len;
    int32_t strsz, i, rd_sz;
    int32_t msg_flags;

    bzero(sendline, sizeof(sendline));
    bzero(&sri, sizeof(sri));
    while (fgets(sendline, SCTP_MAXLINE - 9, fp) != NULL) {
        strsz = strlen(sendline);
        if (sendline[strsz - 1] == '\n') {
            sendline[strsz - 1] = '\0';
            strsz--;
        }

        for (i = 0; i < SERV_MAX_SCTP_STRM; i++)
        {
            snprintf(sendline + strsz, sizeof(sendline) - strsz, ".msg.%d", i);
            Sctp_sendmsg(sockfd, sendline, sizeof(sendline), to, tolen, 0, 0, i, 0, 0);
        }
        
        for (i = 0; i < SERV_MAX_SCTP_STRM; i++)
        {
            len = sizeof(peeraddr);
            rd_sz = Sctp_recvmsg(sockfd, recvline, sizeof(recvline), (SockAddr *)&peeraddr, &len, &sri, &msg_flags);

            printf("From str:%d seq:%d (assoc:0x%x):", sri.sinfo_stream, sri.sinfo_ssn, (uint32_t)sri.sinfo_assoc_id);
            printf("%.*s\n", rd_sz, recvline);
        }
    }
}