/* socket lib by @stsp */
/* Sybase Open Watcom Public License */

#ifdef __WINDOWS__
#include <winsock.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#endif
#include <errno.h>
#include <assert.h>
#include "csock.h"
#include "defs.h"

LDECL int CNV connect(SOCKET s, const struct sockaddr *serv_addr, socklen_t addrlen)
{
    struct sockaddr_in *sai = (struct sockaddr_in *) serv_addr;
    int ret;

    _ENT();
    assert(s < MAX_FDS);
    DEBUG_STR("\tnb flag for %i: %i\n", s, psock[s].nb);
    BCALL(ret, ___csock_connect(s, sai->sin_addr.s_addr, sai->sin_port),
            !psock[s].nb, psock[s].blk_arg);
    if (ret < 0) {
        errno = __csock_errno(ret);
        DEBUG_STR("\tconnect error %i\n", errno);
        return SOCKET_ERROR;
    }
    return ret;
}
