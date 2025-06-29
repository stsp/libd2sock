/* socket lib by @stsp */
/* Sybase Open Watcom Public License */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "csock.h"

_WCRTLINK int bind( int sockfd, const struct sockaddr *my_addr, socklen_t addrlen )
{
    struct sockaddr_in *my_sa = (struct sockaddr_in *) my_addr;

    return ___csock_bind(sockfd, my_sa->sin_addr.s_addr, my_sa->sin_port);
}
