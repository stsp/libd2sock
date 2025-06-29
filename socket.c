/* socket lib by @stsp */
/* Sybase Open Watcom Public License */

#include "variety.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "csock.h"

static int initialized;
struct driver_info_rec driver_info;

static int socket_init(void)
{
    const int CSOCK_VXD_ID = 0x1235;
    unsigned int __csock_version = 0;
    int ret = VxdGetEntry (/*csock_entry, */CSOCK_VXD_ID);
    if (ret < 0)
        return ret;

    ret = ___csock_get_version(&__csock_version, sizeof(driver_info),
            &driver_info);
    if (ret < 0 || __csock_version < 2)
        return -1;
    return 0;
}

_WCRTLINK int socket( int domain, int type, int protocol )
{
    int err = 0;
    int proto;
    unsigned int fd;

    if (!initialized) {
        err = socket_init();
        initialized++;
    }
    if (err)
        return err;
    if (domain != AF_INET)
        return -1;
    if (protocol == 0) {
        switch (type) {
        case SOCK_STREAM:
            proto = IPPROTO_TCP;
            break;
        case SOCK_DGRAM:
            proto = IPPROTO_UDP;
            break;
        default:
            return -1;
        }
    } else {
        proto = protocol;
    }
    err = ___csock_open(proto, &fd);
    if (err)
        return -1;
    return fd;
}
