/* socket lib by @stsp */
/* Sybase Open Watcom Public License */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include "csock.h"

_WCRTLINK int recvfrom(int s, void *buf, size_t len, int flags, struct sockaddr *from, socklen_t *fromlen)
{
    ULONG32 recvlen;
    ULONG32 port = 0;
    struct sockaddr_in *from_sa = (struct sockaddr_in *) from;
    int ret = ___csock_recvfrom(s, buf, len, &recvlen,
            &from_sa->sin_addr.s_addr, &port);
    if (ret < 0) {
        errno = __csock_errno(ret);
        return -1;
    }
    from_sa->sin_port = port;
    return recvlen;
}

