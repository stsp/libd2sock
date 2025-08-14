/* socket lib by @stsp */
/* Sybase Open Watcom Public License */

#include <sys/types.h>
#ifdef __WINDOWS__
#include <winsock.h>
#define SV char
#define SL int
#else
#include <sys/socket.h>
#include <netinet/in.h>
#define SV void
#define SL size_t
#endif
#include <errno.h>
#include "csock.h"
#include "defs.h"

LDECL int CNV sendto( SOCKET s, const SV *msg, SL len, int flags, const struct sockaddr *to, socklen_t tolen )
{
    ULONG32 sentlen;
    struct sockaddr_in *to_sa = (struct sockaddr_in *) to;
    int ret = ___csock_sendto(s, to_sa->sin_addr.s_addr,
            to_sa->sin_port, msg, len, &sentlen);
    if (ret < 0) {
        errno = __csock_errno(ret);
        return -1;
    }
    return sentlen;
}
