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

    _ENT();
    DEBUG_STR("\tfd:%i cmd:%lx\n", fd, cmd);
    switch (cmd) {
    case __IOC(FIONBIO):
        psock[fd].nb = *arg;
#ifndef __WINDOWS__
        ret = ___csock_setnblkio(fd, *arg);
#else
        ret = 0;
#endif
        break;
    case __IOC(FIONREAD):
        ret = ___csock_fionread(fd, arg);
        break;
    default:
        _debug_out("\tunsupported\n");
        errno = EINVAL;
        return ret;
    }
    if (ret < 0)
        errno = __csock_errno(ret);
    return ret;
}
