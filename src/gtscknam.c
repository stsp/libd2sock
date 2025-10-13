/* socket lib by @stsp */
/* Sybase Open Watcom Public License */

#include <sys/types.h>
#ifdef __WINDOWS__
#include <winsock.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#endif
#include <errno.h>
#include "csock.h"
#include "defs.h"

LDECL int CNV getsockname( SOCKET s , struct sockaddr *name , socklen_t *namelen )
{
    struct sockaddr_in *sock_sa = (struct sockaddr_in *) name;
    ULONG32 sock_addr = 0;
    ULONG32 sock_port = 0;
    int err;

    _ENT();
    err = ___csock_getsockname(s, &sock_addr, &sock_port);
    if (err) {
        errno = __csock_errno(err);
        return SOCKET_ERROR;
    }
    *namelen = sizeof (struct sockaddr_in);

    sock_sa->sin_family = AF_INET;
    sock_sa->sin_addr.s_addr = sock_addr;
    sock_sa->sin_port = sock_port;
    return 0;
}

LDECL int CNV getpeername( SOCKET s , struct sockaddr *name , socklen_t *namelen )
{
    struct sockaddr_in *sock_sa = (struct sockaddr_in *) name;
    ULONG32 sock_addr = 0;
    ULONG32 sock_port = 0;
    int err;

    err = ___csock_getpeername(s, &sock_addr, &sock_port);
    if (err) {
        errno = __csock_errno(err);
        return SOCKET_ERROR;
    }
    *namelen = sizeof (struct sockaddr_in);

    sock_sa->sin_family = AF_INET;
    sock_sa->sin_addr.s_addr = sock_addr;
    sock_sa->sin_port = sock_port;
    return 0;
}
