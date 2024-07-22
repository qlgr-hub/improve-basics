#ifndef _WRAP_SYS_SOCKCALL_H_
#define _WRAP_SYS_SOCKCALL_H_

#include "wrap_sys_type.h"

int32_t Socket(int32_t family, int32_t type, int32_t protocal);
int32_t Bind(int32_t sockfd, const SockAddr *myaddr, uint32_t addrlen);
int32_t Listen(int32_t sockfd, int32_t backlog);
int32_t Accept(int32_t sockfd, SockAddr *cliaddr, uint32_t *addrlen);
int32_t Connect(int32_t sockfd, const SockAddr *servaddr, uint32_t addrlen);
int32_t Shutdown(int32_t sockfd, int32_t howto);

const int8_t *Inet_ntop(int family, const void *addrptr, int8_t *strptr, uint32_t len);
int32_t		  Inet_pton(int family, const int8_t *strptr, void *addrptr);
int8_t	     *Sock_ntop(const SockAddr *addr, uint32_t addrlen);
int8_t	     *Sock_ntop_host(const SockAddr *addr, uint32_t addrlen);

int32_t Setsockopt(int32_t sockfd, int32_t level, int32_t optname, const void *optval, uint32_t optlen);
int32_t Getsockopt(int32_t sockfd, int32_t level, int32_t optname, void *optval, uint32_t *optlenptr);

int32_t Sendto(int32_t sockfd, const void *buff, uint32_t nbytes, int32_t flags, const SockAddr *to, uint32_t addrlen);
int32_t Recvfrom(int32_t sockfd, void *buff, uint32_t nbytes, int32_t flags, SockAddr *from, uint32_t *addrlen);

int32_t Getsockname(int32_t sockfd, SockAddr *addr, uint32_t *addrlen);
int32_t Getpeername(int32_t sockfd, SockAddr *addr, uint32_t *addrlen);

int32_t Sctp_sendmsg(int32_t sockfd, const void *msg, uint32_t msgsz, SockAddr *to, uint32_t tolen, 
                     uint32_t ppid, uint32_t flags, uint16_t stream, uint32_t timetolive, uint32_t context);
int32_t Sctp_recvmsg(int32_t sockfd, void *msg, uint32_t msgsz, SockAddr *from, uint32_t *fromlen, SctpSndRcvInfo *sinfo, int32_t *msg_flags);
int32_t sctp_get_no_strms(int32_t sock_fd, SockAddr *to, uint32_t tolen);
int32_t sctp_get_no_strms_linux(int32_t sock_fd, sctp_assoc_t associd);

int32_t Socketpair(int32_t family, int32_t type, int32_t protocol, int32_t *fd);

#endif // !_WRAP_SYS_SOCKCALL_H_