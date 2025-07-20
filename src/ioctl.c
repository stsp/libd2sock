/* socket lib by @stsp */
/* Sybase Open Watcom Public License */

#include <errno.h>
#include <sys/ioctl.h>
#include "csock.h"

_WCRTLINK int ioctlsocket (int fd, int cmd, uint32_t *arg)
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
