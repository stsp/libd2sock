/* socket lib by @stsp */
/* Sybase Open Watcom Public License */

#include <errno.h>
#ifdef __WINDOWS__
#include <winsock.h>
#else
#include <sys/ioctl.h>
#endif
#include "csock.h"
#include "defs.h"

LDECL int CNV ioctlsocket (SOCKET fd, long cmd, uint32_t *arg)
{
    int ret = -1;

    switch (cmd) {
    case FIONBIO:
        ret = ___csock_setnblkio(fd, *arg);
        break;
    case FIONREAD:
        ret = ___csock_fionread(fd, arg);
        break;
    default:
        errno = EINVAL;
        return ret;
    }
    if (ret < 0)
        errno = __csock_errno(ret);
    return ret;
}
