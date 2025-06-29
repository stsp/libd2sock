/* socket lib by @stsp */
/* Sybase Open Watcom Public License */

#include "variety.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "csock.h"

_WCRTLINK int sendto( int s, const void *msg, size_t len, int flags, const struct sockaddr *to, socklen_t tolen )
{
    ULONG32 sentlen;
    struct sockaddr_in *to_sa = (struct sockaddr_in *) to;
    int ret = ___csock_sendto(s, to_sa->sin_addr.s_addr,
            to_sa->sin_port, msg, len, &sentlen);
    if (ret < 0)
        return -1;
    return sentlen;
}
