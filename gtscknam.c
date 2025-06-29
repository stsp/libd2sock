/* socket lib by @stsp */
/* Sybase Open Watcom Public License */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "csock.h"

_WCRTLINK int getsockname( int s , struct sockaddr *name , socklen_t *namelen )
{
    struct sockaddr_in *sock_sa = (struct sockaddr_in *) name;
    ULONG32 sock_addr = 0;
    unsigned short sock_port = 0;
    int err;

    err = ___csock_getsockname(s, &sock_addr, &sock_port);
    if (err)
        return -1;
    *namelen = sizeof (struct sockaddr_in);

    sock_sa->sin_family = AF_INET;
    sock_sa->sin_addr.s_addr = sock_addr;
    sock_sa->sin_port = sock_port;
    return 0;
}

_WCRTLINK int getpeername( int s , struct sockaddr *name , socklen_t *namelen )
{
    struct sockaddr_in *sock_sa = (struct sockaddr_in *) name;
    ULONG32 sock_addr = 0;
    unsigned short sock_port = 0;
    int err;

    err = ___csock_getpeername(s, &sock_addr, &sock_port);
    if (err)
        return -1;
    *namelen = sizeof (struct sockaddr_in);

    sock_sa->sin_family = AF_INET;
    sock_sa->sin_addr.s_addr = sock_addr;
    sock_sa->sin_port = sock_port;
    return 0;
}
