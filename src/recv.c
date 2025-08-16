/* socket lib by @stsp */
/* Sybase Open Watcom Public License */

#include <sys/types.h>
#ifdef __WINDOWS__
#include <winsock.h>
#define RV char
#define RL int
#else
#include <sys/socket.h>
#define RV void
#define RL size_t
#endif
#include <errno.h>
#include <assert.h>
#include "csock.h"
#include "defs.h"

LDECL int CNV recv( SOCKET s, RV *buf, RL len, int flags )
{
    ULONG32       recvlen;
    int ret;

    assert(s < MAX_FDS);
    BCALL(ret, ___csock_recv(s, buf, len, &recvlen), !psock[s].nb);
    if (ret < 0) {
        errno = __csock_errno(ret);
        return -1;
    }
    return recvlen;
}
