#include "../common/err_func.h"
#include "../common/wrap_sys_sockcall.h"
#include "unpifi.h"
#include <net/if_arp.h>
#include <sys/ioctl.h>

int main(int argc, char const *argv[])
{
    int sockfd;
    struct ifi_info *ifi, *ifihead;
    struct sockaddr *sa;
    struct arpreq arprq;
    u_char *ptr;
    int    i, family, doaliases;

    if (argc != 3)
        err_quit("usage: prifinfo <inet4|inet6> <doaliases>");

    if (strcmp(argv[1], "inet4") == 0)
        family = AF_INET;
    else if (strcmp(argv[1], "inet6") == 0)
        family = AF_INET6;
    else 
        err_quit("invalid <address family>");
    doaliases = atoi(argv[2]);

    sockfd = Socket(AF_INET, SOCK_DGRAM, 0);

    for (ifihead = ifi = get_ifi_info(family, doaliases); ifi != NULL; ifi = ifi->ifi_next) {
        printf("%s: ", ifi->ifi_name);
        if (ifi->ifi_index != 0)
            printf("(%d) ", ifi->ifi_index);

        printf("<");
        if (ifi->ifi_flags & IFF_UP)           printf("UP ");
        if (ifi->ifi_flags & IFF_BROADCAST)    printf("BCAST ");
        if (ifi->ifi_flags & IFF_MULTICAST)    printf("MCAST ");
        if (ifi->ifi_flags & IFF_LOOPBACK)     printf("LOOP ");
        if (ifi->ifi_flags & IFF_POINTOPOINT)  printf("P2P ");
        printf(">\n");

        if ( (i = ifi->ifi_hlen) > 0) {
            ptr = ifi->ifi_haddr;
            do {
                printf("%s%x", (i == ifi->ifi_hlen) ? "  " : ":", *ptr++);
            } while (--i > 0);
            printf("\n");
        }

        if (ifi->ifi_mtu != 0)
            printf("  MTU: %d\n", ifi->ifi_mtu);

        if ( (sa = ifi->ifi_addr) != NULL)
            printf("  IP addr: %s\n", Sock_ntop_host(sa, sizeof(*sa)));

        if ( (sa = ifi->ifi_brdaddr) != NULL)
            printf("  broadcast addr: %s\n", Sock_ntop_host(sa, sizeof(*sa)));

        if ( (sa = ifi->ifi_dstaddr) != NULL)
            printf("  destination addr: %s\n", Sock_ntop_host(sa, sizeof(*sa)));

        if (ioctl(sockfd, SIOCGARP, &arprq) < 0) {
            err_ret("ioctl SIOCGARP");
            continue;
        }

        ptr = &arprq.arp_ha.sa_data[0];
        printf("  MAC: %x:%x:%x:%x:%x:%x\n", *ptr, *(ptr + 1), *(ptr + 2), *(ptr + 3), *(ptr + 4), *(ptr + 5));
    }
    
    free_ifi_info(ifihead);
    exit(0);
}
