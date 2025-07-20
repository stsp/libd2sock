/* socket lib by @stsp */
/* Sybase Open Watcom Public License */

#include <string.h>
#include <errno.h>
#include <sys/select.h>
#include "csock.h"

static ULONG32 to_int(fd_set *set)
{
    int i;
    ULONG32 ret = 0;

    if (!set)
        return ret;
    for (i = 0; i < 32; i++) {
        if (FD_ISSET(i, set))
            ret |= 1 << i;
    }
    return ret;
}

static void to_fds(ULONG32 mask, fd_set *set)
{
    int i;

    if (!set)
        return;
    FD_ZERO(set);
    for (i = 0; i < 32; i++) {
        if (mask & (1 << i))
            FD_SET(i, set);
    }
}

_WCRTLINK int select_s (int nfds, fd_set *readfds, fd_set *writefds,
              fd_set *exceptfds, struct timeval *timeout)
{
    ULONG32 to = timeout->tv_sec * 1000000 + timeout->tv_usec;
    ULONG32 _readfds, _writefds, _exceptfds;
    int ret;

    _readfds = to_int(readfds);
    _writefds = to_int(writefds);
    _exceptfds = to_int(exceptfds);
    ret = ___csock_select(&_readfds, &_writefds, &_exceptfds, &to);
    if (ret < 0) {
        errno = __csock_errno (ret);
        return -1;
    }
    to_fds(_readfds, readfds);
    to_fds(_writefds, writefds);
    to_fds(_exceptfds, exceptfds);
    return ret;
}
