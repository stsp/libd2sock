/* socket lib by @stsp */
/* Sybase Open Watcom Public License */

#include "variety.h"
#include <sys/types.h>
#include <sys/socket.h>

#include "csock.h"

_WCRTLINK int recv( int s, void *buf, size_t len, int flags )
{
    ULONG32       recvlen;
    int ret = ___csock_recv(s, buf, len, &recvlen);
    if (ret < 0)
        return -1;
    return recvlen;
}
