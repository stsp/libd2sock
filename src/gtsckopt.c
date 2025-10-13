/****************************************************************************
*
*                            Open Watcom Project
*
* Copyright (c) 2015-2016 The Open Watcom Contributors. All Rights Reserved.
*    Portions Copyright (c) 1983-2002 Sybase, Inc. All Rights Reserved.
*
*  ========================================================================
*
*    This file contains Original Code and/or Modifications of Original
*    Code as defined in and that are subject to the Sybase Open Watcom
*    Public License version 1.0 (the 'License'). You may not use this file
*    except in compliance with the License. BY USING THIS FILE YOU AGREE TO
*    ALL TERMS AND CONDITIONS OF THE LICENSE. A copy of the License is
*    provided with the Original Code and Modifications, and is also
*    available at www.sybase.com/developer/opensource.
*
*    The Original Code and all software distributed under the License are
*    distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
*    EXPRESS OR IMPLIED, AND SYBASE AND ALL CONTRIBUTORS HEREBY DISCLAIM
*    ALL SUCH WARRANTIES, INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF
*    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR
*    NON-INFRINGEMENT. Please see the License for the specific language
*    governing rights and limitations under the License.
*
*  ========================================================================
*
* Description:  Implementation of getsockopt() for Linux and RDOS.
*
****************************************************************************/

#include <string.h>
#include <sys/types.h>
#ifdef __WINDOWS__
#include <winsock.h>
#define GSO char
#else
#include <sys/socket.h>
#define GSO void
#endif
#include <errno.h>
#include <assert.h>
#include "csock.h"
#include "defs.h"

LDECL int CNV getsockopt( SOCKET s, int level, int optname, GSO *optval, socklen_t *optlen )
{
    if (level != SOL_SOCKET)
        return SOCKET_ERROR;
    switch (optname) {
        case SO_ERROR: {
            ULONG32 val;
            int ret;
            assert(*optlen == 2 || *optlen == 4);
            ret = ___csock_getsoerr(s, &val);
            if (!ret) {
                memcpy(optval, &val, *optlen);
                return 0;
            }
            errno = __csock_errno(ret);
            return SOCKET_ERROR;
        }
    }

    errno = ENOPROTOOPT;
    return SOCKET_ERROR;
}
