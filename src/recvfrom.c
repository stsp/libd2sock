/* socket lib by @stsp */
/* Sybase Open Watcom Public License */

#include <sys/types.h>
#ifdef __WINDOWS__
#include <winsock.h>
#define RV char
#define RL int
#else
#include <sys/socket.h>
#include <netinet/in.h>
#define RV void
#define RL size_t
#endif
#include <errno.h>
#include <assert.h>
#include "csock.h"
#include "defs.h"

LDECL int CNV recvfrom(SOCKET s, RV *buf, RL len, int flags, struct sockaddr *from, socklen_t *fromlen)
{
    ULONG32 recvlen;
    ULONG32 port = 0;
    struct sockaddr_in *from_sa = (struct sockaddr_in *) from;
    int ret;

    _ENT();
    assert(s < MAX_FDS);
    BCALL(ret, ___csock_recvfrom(s, buf, len, &recvlen,
            &from_sa->sin_addr.s_addr, &port),
            !(psock[s].nb || (flags & MSG_DONTWAIT)));
    if (ret < 0) {
        errno = __csock_errno(ret);
        return -1;
    }
    from_sa->sin_port = port;
    return recvlen;
}

