/* socket lib by @stsp */
/* Sybase Open Watcom Public License */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "csock.h"

_WCRTLINK int connect(int sockfd, const struct sockaddr *serv_addr, socklen_t addrlen)
{
    struct sockaddr_in *sai = (struct sockaddr_in *) serv_addr;
    return ___csock_connect(sockfd, sai->sin_addr.s_addr, sai->sin_port);
}
