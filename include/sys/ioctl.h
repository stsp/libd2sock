#ifndef SYS_IOCTL_H
#define SYS_IOCTL_H

#include <stdint.h>

enum { FIONBIO, FIONREAD };

_WCRTLINK int ioctlsocket (int fd, long cmd, uint32_t *arg);

#endif
