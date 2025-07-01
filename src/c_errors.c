/* socket lib by @stsp */
/* Sybase Open Watcom Public License */

#include <errno.h>
#include "csock.h"

int __csock_errno (int i_errno)
{
    switch (i_errno) {
	    /* SOCK.VXD errors */
	case -CSOCK_ERR_INVALID_PARAM:
	    return (EINVAL);
	case -CSOCK_ERR_NO_MEMORY:
	    return (ENOMEM);
	case -CSOCK_ERR_INVALID_SOCKET:
	    return (EBADF);
	case -CSOCK_ERR_ALREADY_BOUND:
	    return (EINVAL);
	case -CSOCK_ERR_NOT_BOUND:
	    /* RD: What was I thinking here? */
	    /*return (EDESTADDRREQ);*/
	    /* This a bit generic, but it's probably the most sensible error
	     * return here. */
	    return(EINVAL);
	case -CSOCK_ERR_ACCESS:
	    return (EACCES);
	case -CSOCK_ERR_INTERNAL:
	    return (EAGAIN);	       /* TODO: Hmmm */
	case -CSOCK_ERR_FD_INUSE:
	    return (EBUSY);	       /* TODO: Hmmm */
	case -CSOCK_ERR_INFINITE_WAIT:
	    return (EBUSY);	       /* TODO: Hmmm */
	case -CSOCK_ERR_NOT_CONNECTED:
	    return (EINVAL);
	case -CSOCK_ERR_WOULD_BLOCK:
	    return (EAGAIN);

	    /*default:                        return(EINVAL); */
	    /* Return the current errno by default */
	default:
	    return (errno);
    }
}
