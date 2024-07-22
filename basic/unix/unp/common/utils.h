#ifndef _UTILS_H_
#define _UTILS_H_

#include "wrap_sys_type.h"

AddrInfo *Host_serv(const int8_t *host, const int8_t *serv, int32_t family, int32_t socktype);

int32_t Tcp_connect(const int8_t *host, const int8_t *serv);
int32_t Tcp_listen(const int8_t *host, const int8_t *serv, uint32_t *addrlenp);

int32_t Udp_client(const int8_t *host, const int8_t *serv, SockAddr *servaddr, uint32_t *addrlenp);
int32_t Udp_connect(const int8_t *host, const int8_t *serv);
int32_t Udp_server(const int8_t *host, const int8_t *serv, uint32_t *addrlenp);

#endif /* !_UTILS_H_ */
