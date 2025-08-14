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

LDECL int CNV bind( SOCKET sockfd, const struct sockaddr *my_addr, socklen_t addrlen )
{
    struct sockaddr_in *my_sa = (struct sockaddr_in *) my_addr;
    int ret = ___csock_bind(sockfd, my_sa->sin_addr.s_addr, my_sa->sin_port);
    if (ret < 0) {
        errno = __csock_errno(ret);
        return -1;
    }
    return ret;
}
