/* socket lib by @stsp */
/* Sybase Open Watcom Public License */

#ifdef __WINDOWS__
#include <winsock.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#endif
#include <errno.h>
#include "csock.h"
#include "defs.h"

LDECL int CNV connect(SOCKET sockfd, const struct sockaddr *serv_addr, socklen_t addrlen)
{
    struct sockaddr_in *sai = (struct sockaddr_in *) serv_addr;
    int ret = ___csock_connect(sockfd, sai->sin_addr.s_addr, sai->sin_port);
    if (ret < 0) {
        errno = __csock_errno(ret);
        return -1;
    }
    return ret;
}
