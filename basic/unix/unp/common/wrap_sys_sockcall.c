#include "wrap_sys_sockcall.h"
#include "err_func.h"
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

int32_t Socket(int32_t family, int32_t type, int32_t protocal)
{
    int32_t ret;
    if ( (ret = socket(family, type, protocal)) < 0 )
    {
#ifdef _UNP_DEMO_
        err_sys("socket error");
#endif // _UNP_DEMO_
    }

    return ret;
}

int32_t Bind(int32_t sockfd, const SockAddr *myaddr, uint32_t addrlen)
{
    int32_t ret;
    if ( (ret = bind(sockfd, myaddr, addrlen)) < 0 )
    {
#ifdef _UNP_DEMO_
        err_sys("bind error");
#endif // _UNP_DEMO_
    }

    return ret;
}

int32_t Listen(int32_t sockfd, int32_t backlog)
{
    int32_t ret;
    int8_t  *ptr;

    if ( (ptr = getenv("LISTENQ")) != NULL)
        backlog = atoi((const int8_t *)ptr);
 
    if ( (ret = listen(sockfd, backlog)) < 0 )
    {
#ifdef _UNP_DEMO_
        err_sys("listen error");
#endif // _UNP_DEMO_
    }

    return ret;
}

int32_t Accept(int32_t sockfd, SockAddr *cliaddr, uint32_t *addrlen)
{
    int32_t ret;

again:
    if ( (ret = accept(sockfd, cliaddr, addrlen)) < 0 )
    {
#ifdef EPROTO
        if (errno == EPROTO || errno == ECONNABORTED)
#else
        if (errno == ECONNABORTED)
#endif // EPROTO
            goto again;
        else
#ifdef _UNP_DEMO_
            err_sys("accept error");
#endif // _UNP_DEMO_
    }

    return (ret);
}

int32_t Connect(int32_t sockfd, const SockAddr *servaddr, uint32_t addrlen)
{
    int32_t ret;
    if ( (ret = connect(sockfd, servaddr, addrlen)) < 0 )
    {
#ifdef _UNP_DEMO_
        err_sys("connect error");
#endif // _UNP_DEMO_
    }

    return ret;
}

int32_t Shutdown(int32_t sockfd, int32_t howto)
{
    int32_t ret;
    if ( (ret = shutdown(sockfd, howto)) < 0 )
    {
#ifdef _UNP_DEMO_
        err_sys("shutdown error");
#endif // _UNP_DEMO_
    }

    return ret;
}

const int8_t *Inet_ntop(int family, const void *addrptr, int8_t *strptr, uint32_t len)
{
    const int8_t * ret;
    if ( (ret = inet_ntop(family, addrptr, strptr, len)) == NULL )
    {
#ifdef _UNP_DEMO_
        err_sys("inet_ntop error");
#endif // _UNP_DEMO_
    }

    return ret;
}

int32_t Inet_pton(int family, const int8_t *strptr, void *addrptr)
{
    int32_t ret;
    if ( (ret = inet_pton(family, strptr, addrptr)) < 0 )
    {
#ifdef _UNP_DEMO_
        err_sys("inet_pton error");
#endif // _UNP_DEMO_
    }

    return ret;
}

static int8_t *sock_ntop(const SockAddr *sa, uint32_t salen)
{
    int8_t		  portstr[8];
    static int8_t str[128];		/* Unix domain is largest */

	switch (sa->sa_family) {
	case AF_INET: {
		SockAddrIn *sin = (SockAddrIn *) sa;

		if (inet_ntop(AF_INET, &sin->sin_addr, str, sizeof(str)) == NULL)
			return(NULL);
		if (ntohs(sin->sin_port) != 0) {
			snprintf(portstr, sizeof(portstr), ":%d", ntohs(sin->sin_port));
			strcat(str, portstr);
		}
		return(str);
	}

#ifdef	AF_INET6
	case AF_INET6: {
		SockAddrIn6	*sin6 = (SockAddrIn6 *) sa;

		str[0] = '[';
		if (inet_ntop(AF_INET6, &sin6->sin6_addr, str + 1, sizeof(str) - 1) == NULL)
			return(NULL);
		if (ntohs(sin6->sin6_port) != 0) {
			snprintf(portstr, sizeof(portstr), "]:%d", ntohs(sin6->sin6_port));
			strcat(str, portstr);
			return(str);
		}
		return (str + 1);
	}
#endif

#ifdef	AF_UNIX
	case AF_UNIX: {
		SockAddrUn *unp = (SockAddrUn *) sa;

			/* OK to have no pathname bound to the socket: happens on
			   every connect() unless client calls bind() first. */
		if (unp->sun_path[0] == 0)
			strcpy(str, "(no pathname bound)");
		else
			snprintf(str, sizeof(str), "%s", unp->sun_path);
		return(str);
	}
#endif

#ifdef	AF_LINK
	case AF_LINK: {
		SockAddrDl *sdl = (SockAddrDl *) sa;

		if (sdl->sdl_nlen > 0)
			snprintf(str, sizeof(str), "%*s (index %d)",
					 sdl->sdl_nlen, &sdl->sdl_data[0], sdl->sdl_index);
		else
			snprintf(str, sizeof(str), "AF_LINK, index=%d", sdl->sdl_index);
		return(str);
	}
#endif
	default:
		snprintf(str, sizeof(str), "sock_ntop: unknown AF_xxx: %d, len %d",
				 sa->sa_family, salen);
		return(str);
	}
    return (NULL);
}

int8_t *Sock_ntop(const SockAddr *addr, uint32_t addrlen)
{
    int8_t *ptr;

	if ( (ptr = sock_ntop(addr, addrlen)) == NULL ) {
#ifdef _UNP_DEMO_
		err_sys("sock_ntop error");	/* inet_ntop() sets errno */
#endif // _UNP_DEMO_
    }

	return(ptr);
}


static int8_t *sock_ntop_host(const SockAddr *sa, uint32_t salen)
{
    static char str[128];		/* Unix domain is largest */

	switch (sa->sa_family) {
	case AF_INET: {
		SockAddrIn	*sin = (SockAddrIn *) sa;

		if (inet_ntop(AF_INET, &sin->sin_addr, str, sizeof(str)) == NULL)
			return(NULL);
		return(str);
	}

#ifdef	AF_INET6
	case AF_INET6: {
		SockAddrIn6	*sin6 = (SockAddrIn6 *) sa;

		if (inet_ntop(AF_INET6, &sin6->sin6_addr, str, sizeof(str)) == NULL)
			return(NULL);

		return(str);
	}
#endif // AF_INET6

#ifdef	AF_UNIX
	case AF_UNIX: {
		SockAddrUn *unp = (SockAddrUn *) sa;

			/* OK to have no pathname bound to the socket: happens on
			   every connect() unless client calls bind() first. */
		if (unp->sun_path[0] == 0)
			strcpy(str, "(no pathname bound)");
		else
			snprintf(str, sizeof(str), "%s", unp->sun_path);

		return (str);
	}
#endif // AF_UNIX

#ifdef	AF_LINK
	case AF_LINK: {
		SockAddrDl *sdl = (SockAddrDl *) sa;

		if (sdl->sdl_nlen > 0)
			snprintf(str, sizeof(str), "%*s", sdl->sdl_nlen, &sdl->sdl_data[0]);
		else
			snprintf(str, sizeof(str), "AF_LINK, index=%d", sdl->sdl_index);

		return(str);
	}
#endif // AF_LINK
	default:
		snprintf(str, sizeof(str), "sock_ntop_host: unknown AF_xxx: %d, len %d",
				 sa->sa_family, salen);

		return(str);
	}

    return (NULL);
}

int8_t *Sock_ntop_host(const SockAddr *addr, uint32_t addrlen)
{
    int8_t *ptr;

	if ( (ptr = sock_ntop_host(addr, addrlen)) == NULL ) {
#ifdef _UNP_DEMO_
		err_sys("sock_ntop_host error");	/* sock_ntop_host() sets errno */
#endif // _UNP_DEMO_
    }

	return(ptr);
}

int32_t Setsockopt(int32_t sockfd, int32_t level, int32_t optname, const void *optval, uint32_t optlen)
{
    int32_t ret;
    if ( (ret = setsockopt(sockfd, level, optname, optval, optlen)) < 0 )
    {
#ifdef _UNP_DEMO_
        err_sys("setsockopt error");
#endif // _UNP_DEMO_
    }

    return ret;
}

int32_t Getsockopt(int32_t sockfd, int32_t level, int32_t optname, void *optval, uint32_t *optlenptr)
{
    int32_t ret;
    if ( (ret = getsockopt(sockfd, level, optname, optval, optlenptr)) < 0 )
    {
#ifdef _UNP_DEMO_
        err_sys("getsockopt error");
#endif // _UNP_DEMO_
    }
    
    return ret;
}

int32_t Sendto(int32_t sockfd, const void *buff, uint32_t nbytes, int32_t flags, const SockAddr *to, uint32_t addrlen)
{
    int32_t ret;
    if ( (ret = sendto(sockfd, buff, nbytes, flags, to, addrlen)) != (int32_t)nbytes )
    {
#ifdef _UNP_DEMO_
        err_sys("sendto error");
#endif // _UNP_DEMO_
    }
    
    return ret;
}

int32_t Recvfrom(int32_t sockfd, void *buff, uint32_t nbytes, int32_t flags, SockAddr *from, uint32_t *addrlen)
{
    int32_t ret;
    if ( (ret = recvfrom(sockfd, buff, nbytes, flags, from, addrlen)) < 0 )
    {
#ifdef _UNP_DEMO_
        err_sys("recvfrom error");
#endif // _UNP_DEMO_
    }
    
    return ret;
}

int32_t Getsockname(int32_t sockfd, SockAddr *addr, uint32_t *addrlen)
{
    int32_t ret;
    if ( (ret = getsockname(sockfd, addr, addrlen)) < 0 )
    {
#ifdef _UNP_DEMO_
        err_sys("getsockname error");
#endif // _UNP_DEMO_
    }
    
    return ret;
}

int32_t Getpeername(int32_t sockfd, SockAddr *addr, uint32_t *addrlen)
{
    int32_t ret;
    if ( (ret = getpeername(sockfd, addr, addrlen)) < 0 )
    {
#ifdef _UNP_DEMO_
        err_sys("getpeername error");
#endif // _UNP_DEMO_
    }
    
    return ret;
}

int32_t Sctp_sendmsg(int32_t sockfd, const void *msg, uint32_t msgsz, SockAddr *to, uint32_t tolen, 
    uint32_t ppid, uint32_t flags, uint16_t stream, uint32_t timetolive, uint32_t context)
{
    int32_t ret;
    if ( (ret = sctp_sendmsg(sockfd, msg, msgsz, to, tolen, ppid, flags, stream, timetolive, context)) < 0 )
    {
#ifdef _UNP_DEMO_
        err_sys("sctp_sendmsg error");
#endif // _UNP_DEMO_
    }
    
    return ret;
}

int32_t Sctp_recvmsg(int32_t sockfd, void *msg, uint32_t msgsz, SockAddr *from, uint32_t *fromlen, SctpSndRcvInfo *sinfo, int32_t *msg_flags)
{
    int32_t ret;
    if ( (ret = sctp_recvmsg(sockfd, msg, msgsz, from, fromlen, sinfo, msg_flags)) < 0 )
    {
#ifdef _UNP_DEMO_
        err_sys("sctp_recvmsg error");
#endif // _UNP_DEMO_
    }
    
    return ret;
}

static sctp_assoc_t sctp_address_to_associd(int32_t sock_fd, SockAddr *sa, uint32_t salen)
{
    SctpPAddrParams sp;
	uint32_t siz;

	siz = sizeof(SctpPAddrParams);
	bzero(&sp, siz);
	memcpy(&sp.spp_address, sa, salen);
	sctp_opt_info(sock_fd, 0, SCTP_PEER_ADDR_PARAMS, &sp, &siz); //SCTP_PEER_ADDR_PARAMS linux上不行

	return (sp.spp_assoc_id);
}

int32_t sctp_get_no_strms(int32_t sock_fd, SockAddr *to, uint32_t tolen)
{
    uint32_t retsz;
	SctpStatus status;
	retsz = sizeof(status);	
	bzero(&status,sizeof(status));

	status.sstat_assoc_id = sctp_address_to_associd(sock_fd, to, tolen);
	Getsockopt(sock_fd, IPPROTO_SCTP, SCTP_STATUS, &status, &retsz);

	return (status.sstat_outstrms);
}

int32_t sctp_get_no_strms_linux(int32_t sock_fd, sctp_assoc_t associd)
{
    uint32_t retsz;
	SctpStatus status;
	retsz = sizeof(status);	
	bzero(&status,sizeof(status));

	status.sstat_assoc_id = associd;
	Getsockopt(sock_fd, IPPROTO_SCTP, SCTP_STATUS, &status, &retsz);

	return (status.sstat_outstrms);
}

int32_t Socketpair(int32_t family, int32_t type, int32_t protocol, int32_t *fd)
{
	int32_t	ret;

	if ( (ret = socketpair(family, type, protocol, fd)) < 0 )
    {
#ifdef _UNP_DEMO_
        err_sys("socketpair error");
#endif // _UNP_DEMO_
    }
	
    return (ret);
}