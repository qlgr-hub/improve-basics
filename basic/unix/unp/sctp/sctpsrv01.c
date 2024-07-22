#include "../common/err_func.h"
#include "../common/wrap_sys_sockcall.h"
#include "../common/wrap_sys_iocall.h"

#define SERV_PORT 9879

int main(int argc, char *argv[])
{
    int32_t sockfd, msg_flags;
    int8_t  readbuf[BUFSIZE];
    SockAddrIn servaddr, cliaddr;
    SctpSndRcvInfo sri;
    SctpEventSubscribe events;
    int32_t stream_increment = 1;
    uint32_t len;
    uint32_t rd_sz;

    if (argc == 2)
        stream_increment = atoi(argv[1]);

    sockfd = Socket(AF_INET, SOCK_SEQPACKET, IPPROTO_SCTP);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

    Bind(sockfd, (SockAddr *)&servaddr, sizeof(servaddr));

    bzero(&events, sizeof(events));
    events.sctp_data_io_event = 1;
    Setsockopt(sockfd, IPPROTO_SCTP, SCTP_EVENTS, &events, sizeof(events));

    Listen(sockfd, LISTENQ);

    for ( ; ; ) {
        len = sizeof(SockAddrIn);
        rd_sz = Sctp_recvmsg(sockfd, readbuf, sizeof(readbuf), (SockAddr *)&cliaddr, &len, &sri, &msg_flags);
        if (stream_increment) {
            sri.sinfo_stream++;
            if (sri.sinfo_stream >= sctp_get_no_strms_linux(sockfd, sri.sinfo_assoc_id))
                sri.sinfo_stream = 0;
        }
        Sctp_sendmsg(sockfd, readbuf, rd_sz, (SockAddr *)&cliaddr, len, sri.sinfo_ppid, sri.sinfo_flags, sri.sinfo_stream, 0, 0);
    }
}