/* socket lib by @stsp */
/* Sybase Open Watcom Public License */

#include "variety.h"
#include <sys/types.h>
#include <sys/socket.h>

#include "csock.h"

_WCRTLINK int listen(int s, int backlog)
{
    return ___csock_listen(s, backlog);
}
