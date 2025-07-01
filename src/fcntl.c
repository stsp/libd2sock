/* socket lib by @stsp */
/* Sybase Open Watcom Public License */

#include <fcntl.h>
#include <sys/fcntl.h>
#include <errno.h>
#include <stdarg.h>
#include "csock.h"

_WCRTLINK int fcntl(int fd, int command, ...)
{
    int ret = -1;
    unsigned int x = 1;
    int request;
    va_list ap;

    switch (command) {
    case F_SETFL:
        va_start(ap, command);
        request = va_arg(ap, int);
        va_end(ap);
        x = (request & O_NONBLOCK) == O_NONBLOCK;
        ret = ___csock_setnblkio(fd, x);
        break;

    case F_GETFL:
        ret = ___csock_getnblkio(fd, &x);
        if (ret) {
            errno = __csock_errno(ret);
            return -1;
        }
        ret = x;
        break;
    }

    return ret;
}
