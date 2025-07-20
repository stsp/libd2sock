/* socket lib by @stsp */
/* Sybase Open Watcom Public License */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include "csock.h"

_WCRTLINK int accept(int s, struct sockaddr *addr, socklen_t *addrlen)
{
    ULONG32 fd;
    int err;
    ULONG32 dest_port = 0;
    ULONG32 dest_addr = 0;
    struct sockaddr_in *addr_sa = (struct sockaddr_in *) addr;

    err = ___csock_accept(s, &fd, &dest_addr, &dest_port);
    if (err) {
        errno = __csock_errno(err);
        return -1;
    }
    /* Copy the peer address */
    addr_sa->sin_family      = AF_INET;
    addr_sa->sin_addr.s_addr = dest_addr;
    addr_sa->sin_port        = dest_port;
    *addrlen                 = sizeof(struct sockaddr_in);
    return fd;
}
