
#include "../common/err_func.h"
#include "../common/wrap_sys_sockcall.h"
#include "../common/wrap_std_alloc.h"
#include "unpifi.h"
#include <sys/ioctl.h>

struct ifi_info *get_ifi_info(int family, int doaliases)
{
    struct ifi_info *ifi, *ifihead, **ifipnext;
    int     sockfd, len, lastlen, flags, myflags, idx = 0, hlen = 0;
    char   *ptr, *buf, lastname[IF_NAMESIZE], *cptr, *haddr, *sdlname;
    struct ifconf   ifc;
    struct ifreq    *ifr, ifrcopy;
    struct sockaddr_in  *sinptr;
    struct sockaddr_in6 *sin6ptr;

    sockfd = Socket(AF_INET, SOCK_DGRAM, 0);

    lastlen = 0;
    len = 100 * sizeof(struct ifreq);
    for ( ; ; ) {
        buf = Malloc(len);
        ifc.ifc_len = len;
        ifc.ifc_buf = buf;
        if (ioctl(sockfd, SIOCGIFCONF, &ifc) < 0) {
            if (errno != EINVAL || lastlen != 0)
                err_sys("ioctl error");
        } else {
            if (ifc.ifc_len == lastlen)
                break;
            lastlen = ifc.ifc_len;
        }
        len += 10 * sizeof(struct ifreq);
        free(buf);
    }

    //printf("[get_ifi_info] get len = %d(%d)\n", ifc.ifc_len, sizeof(struct ifreq));

    ifihead = NULL;
    ifipnext = &ifihead;
    lastname[0] = 0;
    sdlname = NULL;

    for (ptr = buf; ptr < buf + ifc.ifc_len; ) {
        ifr = (struct ifreq *)ptr;

        switch (ifr->ifr_addr.sa_family)
        {
        case AF_INET6:
            len = sizeof(struct sockaddr_in6);
            break;
        case AF_INET:
        default:
            len = sizeof(struct sockaddr);
            break;
        }

        ptr +=  sizeof(struct ifreq);//sizeof(ifr->ifr_name) + len;

        /* AF_LINK ignore */

        if (ifr->ifr_addr.sa_family != family)
            continue;

        myflags = 0;
        if ( (cptr = strchr(ifr->ifr_name, ':')) != NULL )
            *cptr = 0;

        if (strncmp(lastname, ifr->ifr_name, IF_NAMESIZE) == 0) {
            if (doaliases == 0)
                continue;
            myflags = IFI_ALIAS;
        }
        memcpy(lastname, ifr->ifr_name, IF_NAMESIZE);

        ifrcopy = *ifr;
        ioctl(sockfd, SIOCGIFFLAGS, &ifrcopy);
        flags = ifrcopy.ifr_flags;
        if ( (flags & IFF_UP) == 0)
            continue;

        ifi = calloc(1, sizeof(struct ifi_info));
        *ifipnext = ifi;
        ifipnext = &ifi->ifi_next;

        ifi->ifi_flags = flags;
        ifi->ifi_myflags = myflags;

        ioctl(sockfd, SIOCGIFMTU, &ifrcopy);
        ifi->ifi_mtu = ifrcopy.ifr_mtu;

        memcpy(ifi->ifi_name, ifr->ifr_name, IFI_NAME);
        ifi->ifi_name[IFI_NAME - 1] = '\0';
        
        if (sdlname == NULL || strcmp(sdlname, ifr->ifr_name) != 0)
            idx = hlen = 0;

        ifi->ifi_index = idx;
        ifi->ifi_hlen = hlen;
        if (ifi->ifi_hlen > IFI_HADDR)
            ifi->ifi_hlen = IFI_HADDR;

        if (hlen)
            memcpy(ifi->ifi_haddr, haddr, ifi->ifi_hlen);

        switch (ifr->ifr_addr.sa_family) {
            case AF_INET:
                sinptr = (struct sockaddr_in *) &(ifr->ifr_addr);
                ifi->ifi_addr = calloc(1, sizeof(struct sockaddr_in));
                memcpy(ifi->ifi_addr, sinptr, sizeof(struct sockaddr_in));

                if (flags & IFF_BROADCAST) {
                    ioctl(sockfd, SIOCGIFBRDADDR, &ifrcopy);
                    sinptr = (struct sockaddr_in *) &(ifrcopy.ifr_broadaddr);
                    ifi->ifi_brdaddr = calloc(1, sizeof(struct sockaddr_in));
                    memcpy(ifi->ifi_brdaddr, sinptr, sizeof(struct sockaddr_in));
                }

                if (flags & IFF_POINTOPOINT) {
                    ioctl(sockfd, SIOCGIFDSTADDR, &ifrcopy);
                    sinptr = (struct sockaddr_in *) &(ifrcopy.ifr_dstaddr);
                    ifi->ifi_dstaddr = calloc(1, sizeof(struct sockaddr_in));
                    memcpy(ifi->ifi_dstaddr, sinptr, sizeof(struct sockaddr_in));
                }

                break;

            case AF_INET6:
                sin6ptr = (struct sockaddr_in6 *) &(ifr->ifr_addr);
                ifi->ifi_addr = calloc(1, sizeof(struct sockaddr_in6));
                memcpy(ifi->ifi_addr, sin6ptr, sizeof(struct sockaddr_in6));

                if (flags & IFF_POINTOPOINT) {
                    ioctl(sockfd, SIOCGIFDSTADDR, &ifrcopy);
                    sin6ptr = (struct sockaddr_in6 *) &(ifrcopy.ifr_dstaddr);
                    ifi->ifi_dstaddr = calloc(1, sizeof(struct sockaddr_in6));
                    memcpy(ifi->ifi_dstaddr, sin6ptr, sizeof(struct sockaddr_in6));
                }

                break;

            default:
                break;
        }
    }

    free(buf);
    return (ifihead);
}

void  free_ifi_info(struct ifi_info *ifihead)
{
    struct ifi_info *ifi, *ifinext;

    for (ifi = ifihead; ifi != NULL; ifi = ifinext) {
        if (ifi->ifi_addr != NULL)
            free(ifi->ifi_addr);
        if (ifi->ifi_brdaddr != NULL)
            free(ifi->ifi_brdaddr);
        if (ifi->ifi_dstaddr != NULL)
            free(ifi->ifi_dstaddr);

        ifinext = ifi->ifi_next;
        free(ifi);
    }
}