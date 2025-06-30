/* socket lib by @stsp */
/* Sybase Open Watcom Public License */

#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include "csock.h"

_WCRTLINK int listen(int s, int backlog)
{
    int ret = ___csock_listen(s, backlog);
    if (ret < 0) {
        errno = __csock_errno(ret);
        return -1;
    }
    return ret;
}
