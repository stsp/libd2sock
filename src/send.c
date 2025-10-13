/* socket lib by @stsp */
/* Sybase Open Watcom Public License */

#include <sys/types.h>
#ifdef __WINDOWS__
#include <winsock.h>
#define SV char
#define SL int
#define SVP "%i"
#else
#include <sys/socket.h>
#define SV void
#define SL size_t
#define SVP "%zu"
#endif
#include <errno.h>
#include "csock.h"
#include "defs.h"

LDECL int CNV send(SOCKET s, const SV *msg, SL len, int flags)
{
    ULONG32 sentlen;
    int ret;

    _ENT();
    ret = ___csock_send(s, msg, len, &sentlen);
    if (ret < 0) {
        errno = __csock_errno(ret);
        DEBUG_STR("\treturning error %i\n", errno);
        return SOCKET_ERROR;
    }
    DEBUG_STR("\treturning "SVP"\n", sentlen);
    return sentlen;
}
