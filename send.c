/* socket lib by @stsp */
/* Sybase Open Watcom Public License */

#include <sys/types.h>
#include <sys/socket.h>

#include "csock.h"

_WCRTLINK int send(int s, const void *msg, size_t len, int flags)
{
    ULONG32 sentlen;
    int ret = ___csock_send(s, msg, len, &sentlen);
    if (ret < 0)
        return -1;
    return sentlen;
}
