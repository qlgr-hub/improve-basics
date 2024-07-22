#include "err_func.h"
#include "wrap_sys_sockcall.h"
#include "utils.h"

static AddrInfo *host_serv(const int8_t *host, const int8_t *serv, int32_t family, int32_t socktype)
{
    int32_t n;
    AddrInfo hints, *res;

    bzero(&hints, sizeof(hints));
    hints.ai_flags = AI_CANONNAME;
    hints.ai_family = family;
    hints.ai_socktype = socktype;

    if ( (n = getaddrinfo(host, serv, &hints, &res)) != 0 )
        return (NULL);

    return (res);
}

AddrInfo *Host_serv(const int8_t *host, const int8_t *serv, int32_t family, int32_t socktype)
{
    return host_serv(host, serv, family, socktype);
}

static int32_t tcp_connect(const int8_t *host, const int8_t *serv)
{
    int32_t sockfd, n;
    AddrInfo hints, *res, *ressave;

    bzero(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if ( (n = getaddrinfo(host, serv, &hints, &res)) != 0 )
        err_quit("tcp_connect error for %s, %s: %s", host, serv, gai_strerror(n));

    ressave = res;

    do {
        sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
        if (sockfd < 0)
            continue;

        if (connect(sockfd, res->ai_addr, res->ai_addrlen) == 0)
            break;

        Close(sockfd);
    } while ( (res = res->ai_next) != NULL );

    if (res == NULL)
        err_sys("tcp_connect error for %s, %s", host, serv);

    freeaddrinfo(ressave);

    return (sockfd);
}

int32_t Tcp_connect(const int8_t *host, const int8_t *serv)
{
    return tcp_connect(host, serv);
}

int32_t tcp_listen(const int8_t *host, const int8_t *serv, uint32_t *addrlenp)
{
    int32_t listenfd, n;
    const int32_t on = 1;
    AddrInfo hints, *res, *ressave;

    bzero(&hints, sizeof(hints));
    hints.ai_flags = AI_PASSIVE;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if ( (n = getaddrinfo(host, serv, &hints, &res)) != 0 )
        err_quit("tcp_listen error for %s, %s: %s", host, serv, gai_strerror(n));

    ressave = res;

    do {
        listenfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
        if (listenfd < 0)
            continue;

        Setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
        if (bind(listenfd, res->ai_addr, res->ai_addrlen) == 0)
            break;

        Close(listenfd);
    } while ( (res = res->ai_next) != NULL );

    if (res == NULL)
        err_sys("tcp_listen error for %s, %s", host, serv);

    Listen(listenfd, LISTENQ);

    if (addrlenp)
        *addrlenp = res->ai_addrlen;

    freeaddrinfo(ressave);

    return (listenfd);
}

int32_t Tcp_listen(const int8_t *host, const int8_t *serv, uint32_t *addrlenp)
{
    return tcp_listen(host, serv, addrlenp);
}

int32_t udp_client(const int8_t *host, const int8_t *serv, SockAddr *servaddr, uint32_t *addrlenp)
{
    int32_t sockfd, n;
    AddrInfo hints, *res, *ressave;

    bzero(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;

    if ( (n = getaddrinfo(host, serv, &hints, &res)) != 0 )
        err_quit("udp_client error for %s, %s: %s", host, serv, gai_strerror(n));

    ressave = res;

    do {
        sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
        if (sockfd >= 0)
            break;
    } while ( (res = res->ai_next) != NULL );

    if (res == NULL)
        err_sys("udp_client error for %s, %s", host, serv);

    if (servaddr) {
        memcpy(servaddr, res->ai_addr, res->ai_addrlen);

        //if (addrlenp) // need
            *addrlenp = res->ai_addrlen;
    }
    
    freeaddrinfo(ressave);

    return (sockfd);
}

int32_t Udp_client(const int8_t *host, const int8_t *serv, SockAddr *servaddr, uint32_t *addrlenp)
{
    return udp_client(host, serv, servaddr, addrlenp);
}

int32_t udp_connect(const int8_t *host, const int8_t *serv)
{
    int32_t sockfd, n;
    AddrInfo hints, *res, *ressave;

    bzero(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;

    if ( (n = getaddrinfo(host, serv, &hints, &res)) != 0 )
        err_quit("udp_connect error for %s, %s: %s", host, serv, gai_strerror(n));

    ressave = res;

    do {
        sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
        if (sockfd < 0)
            continue;

        if (connect(sockfd, res->ai_addr, res->ai_addrlen) == 0)
            break;

        Close(sockfd);
    } while ( (res = res->ai_next) != NULL );

    if (res == NULL)
        err_sys("udp_connect error for %s, %s", host, serv);

    freeaddrinfo(ressave);

    return (sockfd);
}

int32_t Udp_connect(const int8_t *host, const int8_t *serv)
{
    return udp_connect(host, serv);
}

int32_t udp_server(const int8_t *host, const int8_t *serv, uint32_t *addrlenp)
{
    int32_t sockfd, n;
    AddrInfo hints, *res, *ressave;

    bzero(&hints, sizeof(hints));
    hints.ai_flags = AI_PASSIVE;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;

    if ( (n = getaddrinfo(host, serv, &hints, &res)) != 0 )
        err_quit("udp_server error for %s, %s: %s", host, serv, gai_strerror(n));

    ressave = res;

    do {
        sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
        if (sockfd < 0)
            continue;

        if (bind(sockfd, res->ai_addr, res->ai_addrlen) == 0)
            break;

        Close(sockfd);
    } while ( (res = res->ai_next) != NULL );

    if (res == NULL)
        err_sys("udp_server error for %s, %s", host, serv);

    if (addrlenp)
        *addrlenp = res->ai_addrlen;

    freeaddrinfo(ressave);

    return (sockfd);
}

int32_t Udp_server(const int8_t *host, const int8_t *serv, uint32_t *addrlenp)
{
    return udp_server(host, serv, addrlenp);
}