/* socket lib by @stsp */
/* Sybase Open Watcom Public License */

#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include "csock.h"

_WCRTLINK int recvfrom(int s, void *buf, size_t len, int flags, struct sockaddr *from, socklen_t *fromlen)
{
    ULONG32 recvlen;
    int ret = ___csock_recv(s, buf, len, &recvlen);
    if (ret < 0) {
        errno = __csock_errno(ret);
        return -1;
    }
    return recvlen;
}

