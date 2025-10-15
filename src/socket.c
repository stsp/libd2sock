/* socket lib by @stsp */
/* Sybase Open Watcom Public License */

#ifdef __WINDOWS__
#include <winsock.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#endif
#include <assert.h>
#include <errno.h>
#include <d2sock.h>
#include "csock.h"
#include "defs.h"

static int initialized;
struct driver_info_rec driver_info;
struct per_sock psock[MAX_FDS];

static int (far *__blocking_hook)(void *);
static void (far *__debug_hook)(const char *);

_WCRTLINK int _blocking_hook(void *arg)
{
    if (__blocking_hook)
        return __blocking_hook(arg);
    return 1;
}

_WCRTLINK void d2s_set_blocking_hook(int (far *hook)(void *))
{
    __blocking_hook = hook;
}

_WCRTLINK void _debug_out(const char *msg)
{
    if (__debug_hook)
        __debug_hook(msg);
}

_WCRTLINK void d2s_set_debug_hook(void (far *hook)(const char *))
{
    __debug_hook = hook;
}

int csock_init(void)
{
    const int CSOCK_VXD_ID = 0x1235;
    ULONG32 __csock_version = 0;
    int ret = VxdGetEntry (/*csock_entry, */CSOCK_VXD_ID);
    if (ret < 0)
        return ret;

    ret = ___csock_get_version(&__csock_version, sizeof(driver_info),
            &driver_info);
    if (ret < 0 || __csock_version < 2)
        return -1;
    return 0;
}

LDECL SOCKET CNV socket( int domain, int type, int protocol )
{
    int err = 0;
    int proto;
    ULONG32 fd;

    _ENT();
    if (!initialized) {
        err = csock_init();
        if (!err)
            initialized++;
    }
    if (err)
        return err;
    if (domain != AF_INET)
        return INVALID_SOCKET;
    if (protocol == 0) {
        switch (type) {
        case SOCK_STREAM:
            proto = IPPROTO_TCP;
            break;
        case SOCK_DGRAM:
            proto = IPPROTO_UDP;
            break;
        default:
            return INVALID_SOCKET;
        }
    } else {
        proto = protocol;
    }
    err = ___csock_open(proto, &fd);
    if (err) {
        errno = __csock_errno(err);
        return INVALID_SOCKET;
    }
    assert(fd < MAX_FDS);
    psock[fd].nb = 0;
    psock[fd].blk_arg = NULL;

#ifdef __WINDOWS__
    ___csock_setnblkio(fd, 1);
#endif
    DEBUG_STR("\topened socket %i\n", fd);
    return fd;
}

LDECL int CNV closesocket (SOCKET s)
{
    _ENT();
    DEBUG_STR("\tclosing socket %i\n", s);
    return ___csock_close(s);
}

void set_blk_arg(int fd, void *arg)
{
    assert(fd < MAX_FDS);
    psock[fd].blk_arg = arg;
}
