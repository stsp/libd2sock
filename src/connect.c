/* socket lib by @stsp */
/* Sybase Open Watcom Public License */

#ifdef __WINDOWS__
#include <winsock.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#endif
#include <errno.h>
#include <assert.h>
#include "csock.h"
#include "defs.h"

LDECL int CNV connect(SOCKET s, const struct sockaddr *serv_addr, socklen_t addrlen)
{
    struct sockaddr_in *sai = (struct sockaddr_in *) serv_addr;
    int ret;

    _ENT();
    assert(s < MAX_FDS);
    DEBUG_STR("\tnb flag for %i: %i\n", s, psock[s].nb);
    BCALL(ret, ___csock_connect(s, sai->sin_addr.s_addr, sai->sin_port),
            !psock[s].nb, psock[s].blk_arg);
    if (ret < 0) {
        if (ret == -CSOCK_ERR_WOULD_BLOCK)
            psock[s].state = SF_CONNECTING;
        errno = __csock_errno(ret);
        DEBUG_STR("\tconnect error %i\n", errno);
        return SOCKET_ERROR;
    }
    return ret;
}

/* took from goperus sources */
static int is_connected(int s)
{
    fd_set set;
    struct timeval t;
    int res, rc;
    socklen_t sizeofint = sizeof(int);

    t.tv_sec = 0;
    t.tv_usec = 0;
    FD_ZERO(&set);
    FD_SET(s, &set);
    /* check socket for writeability */
    res = select(s + 1, NULL, &set, NULL, &t);
    if (res < 0) return(-1);
    if (res == 0) return(0);
    /* use getsockopt(2) to read the SO_ERROR option at level SOL_SOCKET to
     * determine whether connect() completed successfully (SO_ERROR is zero) */
    rc = getsockopt(s, SOL_SOCKET, SO_ERROR, (void *)&res, &sizeofint);
    if (rc == -1 && errno == ENOPROTOOPT) return(1);  // unsupported
    if (rc != 0) return(-1);
    /* do not trust actual value of res */
    if (res != 0) return(-1);
    return(1);
}

_WCRTLINK int aconnect(SOCKET s)
{
//    _ENT();
    assert(s < MAX_FDS);
    if (psock[s].state != SF_CONNECTING) {
        errno = EINVAL;
        return -1;
    }
    switch (is_connected(s)) {
        case -1:
            psock[s].state = SF_NONE;
            errno = EIO;
            return -1;
        case 0:
            errno = EAGAIN;
            return -1;
        /* case 1: success */
    }
    psock[s].state = SF_NONE;
    return 0;
}
