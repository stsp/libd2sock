/* socket lib by @stsp */
/* Sybase Open Watcom Public License */

#include <string.h>
#include <errno.h>
#ifdef __WINDOWS__
#include <winsock.h>
#define NM select
#else
#include <sys/select.h>
#define NM select_s
#endif
#include "csock.h"
#include "defs.h"

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

LDECL int CNV NM (int nfds, fd_set *readfds, fd_set *writefds,
              fd_set *exceptfds, const struct timeval *timeout)
{
#ifdef __WINDOWS__
    ULONG32 expi = timeout ? timeout->tv_sec * 1000 + timeout->tv_usec / 1000 :
            0xffffffff;
    ULONG32 start = (timeout && expi) ? GetTickCount() : 0;
    ULONG32 to = 0;
#else
    ULONG32 to = timeout ? timeout->tv_sec * 1000000 + timeout->tv_usec :
            0xffffffff;
#endif
    ULONG32 _readfds, _writefds, _exceptfds;
    int ret;

    _ENT();
    _readfds = to_int(readfds);
    _writefds = to_int(writefds);
    _exceptfds = to_int(exceptfds);
    BCALL_TO(ret, ___csock_select(&_readfds, &_writefds, &_exceptfds, &to),
            start, expi, NULL);
    if (ret < 0) {
        errno = __csock_errno (ret);
        DEBUG_STR("\treturning error %i\n", errno);
        return SOCKET_ERROR;
    }
    to_fds(_readfds, readfds);
    to_fds(_writefds, writefds);
    to_fds(_exceptfds, exceptfds);
    DEBUG_STR("\treturning %i\n", ret);
    return ret;
}
