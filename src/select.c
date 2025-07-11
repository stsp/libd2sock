/* socket lib by @stsp */
/* Sybase Open Watcom Public License */

#include <errno.h>
#include <sys/select.h>
#include "csock.h"

_WCRTLINK int select_s (int nfds, fd_set *readfds, fd_set *writefds,
              fd_set *exceptfds, struct timeval *timeout)
{
    ULONG32 to = timeout->tv_sec * 1000000 + timeout->tv_usec;
    fd_set dummy;
    int ret;

    /* Don't pass NULL to our select() */
    FD_ZERO(&dummy);
    if (!readfds)
        readfds = &dummy;
    if (!writefds)
        writefds = &dummy;
    if (!exceptfds)
        exceptfds = &dummy;
    ret = ___csock_select(readfds, writefds, exceptfds, &to);
    if (ret < 0) {
        errno = __csock_errno (ret);
        return -1;
    }
    return ret;
}
