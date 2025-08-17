/* socket lib by @stsp */
/* Sybase Open Watcom Public License */

#include <unistd.h>
#include <string.h>
#ifdef __WINDOWS__
#include <winsock.h>
#define GNL int
#else
#include <netdb.h>
#define GNL size_t
#endif
#include "csock.h"
#include "defs.h"

LDECL int CNV gethostname( char *__name, GNL __len )
{
    strlcpy( __name, driver_info.domain, __len );
    return( 0 );
}
