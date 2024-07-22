#ifndef _WRAP_SYS_TYPE_H_
#define _WRAP_SYS_TYPE_H_

#define _GNU_SOURCE
#define _POSIX_C_SOURCE 200112

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <strings.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/select.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <netinet/ip6.h>
#include <poll.h>
#include <netinet/sctp.h>
#include <string.h>
#include <netdb.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include <mqueue.h>
#include <stdarg.h>
#include <getopt.h>
#include <pthread.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <math.h>
#include <fcntl.h>
//#include <vadefs.h>
//#include <net/if_dl.h>

#define MAXLINE 4096
#define BUFSIZE 8192
#define LISTENQ 5

#define FILE_MODE  (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

#define MIN(a, b) (a) < (b) ? (a) : (b)
#define MAX(a, b) (a) > (b) ? (a) : (b)

typedef void Sigfunc(int32_t);
typedef	void Sigfunc_rt(int32_t, siginfo_t *, void *);


typedef struct in_addr          InAddr;
typedef struct sockaddr_storage SockAddrStorage;
typedef struct sockaddr         SockAddr;
typedef struct sockaddr_in      SockAddrIn;
typedef struct sockaddr_in6     SockAddrIn6;
typedef struct sockaddr_un      SockAddrUn;
#ifdef	AF_LINK
typedef struct sockaddr_dl      SockAddrDl;
#endif // AF_LINK
typedef struct pollfd       PollFD;
typedef struct linger       Linger;
typedef struct timeval      Timeval;
typedef struct hostent      Hostent;
typedef struct servent      Servent;
typedef struct addrinfo     AddrInfo;


typedef struct sctp_sndrcvinfo      SctpSndRcvInfo;
typedef struct sctp_event_subscribe SctpEventSubscribe;
typedef struct sctp_status          SctpStatus;
typedef struct sctp_paddrparams     SctpPAddrParams;
typedef struct sctp_initmsg         SctpInitMsg;

typedef struct cmsgcred             CMsgCred;
typedef struct cmsghdr              CMsgHdr;
typedef struct msghdr               MsgHdr;
typedef struct iovec                IoVec;

#endif // !_WRAP_SYS_TYPE_H_