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
* Description:  Implementation of setsockopt() for Linux and RDOS.
*
****************************************************************************/


#include <sys/types.h>
#ifdef __WINDOWS__
#include <winsock.h>
#define SV char
#else
#include <sys/socket.h>
#define SV void
#endif
#include <errno.h>
#include <assert.h>
#include "csock.h"
#include "defs.h"

LDECL int CNV setsockopt( SOCKET s, int level, int optname, const SV *optval, socklen_t optlen )
{
    _ENT();
    if (level != SOL_SOCKET)
        return SOCKET_ERROR;
    switch (optname) {
        case SO_LINGER: {
            int rc;
            const struct linger *lin = (const struct linger *)optval;
            assert(optlen == sizeof(*lin));
            rc = ___csock_setsolinger(s, lin->l_onoff, lin->l_linger);
            if (rc) {
                errno = __csock_errno(rc);
                return SOCKET_ERROR;
            }
            return 0;
        }
    }

    errno = ENOPROTOOPT;
    return SOCKET_ERROR;
}
