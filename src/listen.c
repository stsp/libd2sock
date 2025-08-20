/* socket lib by @stsp */
/* Sybase Open Watcom Public License */

#include <sys/types.h>
#ifdef __WINDOWS__
#include <winsock.h>
#else
#include <sys/socket.h>
#endif
#include <errno.h>
#include "csock.h"
#include "defs.h"

LDECL int CNV listen(SOCKET s, int backlog)
{
    int ret;

    _ENT();
    ret = ___csock_listen(s, backlog);
    if (ret < 0) {
        errno = __csock_errno(ret);
        return -1;
    }
    return ret;
}
