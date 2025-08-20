/****************************************************************************
*
*                            Open Watcom Project
*
* Copyright (c) 2015-2019 The Open Watcom Contributors. All Rights Reserved.
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
* Description:  Implementation of gethostbyname() for Linux and RDOS.
*
* Author: J. Armstrong
*
****************************************************************************/

#include "_resolve.h"
#include <stdio.h>
#include <sys/types.h>
#ifdef __WINDOWS__
#include <winsock.h>
#else
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#endif
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "csock.h"
#include "defs.h"

#if 0
static struct hostent *__check_hostdb( const char *name )
{
    int             i;
    struct hostent  *one;
    int             alias;

    one = NULL;
    if( name != NULL ) {
        alias = 0;
        sethostent( 1 );
        while( alias == 0 && (one = gethostent()) != NULL ) {
            if( one->h_name != NULL && strcmp( one->h_name, name ) == 0 )
                break;
            for( i = 0; one->h_aliases[i] != NULL; i++ ) {
                if( strcmp( one->h_aliases[i], name ) == 0 ) {
                    alias = 1;
                    break;
                }
            }
        }
        endhostent();
    }
    return( one );
}
#endif

/* Messy function for retrieving the "last" indexed nameserver
 * from the DNS resolution config file
 */
static int __get_nameserver( int last, in_addr_t *dnsaddr )
{
    if (last)
        return 0;
    if (!driver_info.dnsserver)
        csock_init();
    if (!driver_info.dnsserver)
        return 0;
    *dnsaddr = driver_info.dnsserver;
    return 1;
}

static struct hostent *__check_dns_4( const char *name )
{
    in_addr_t               dnsaddr;
    int                     servercount;
    int                     dns_success;
#if 0
    static struct hostent   ret;
#else
    struct hostent *_ret = malloc(sizeof(*_ret));
    #define ret (*_ret)
#endif

    dns_success = 0;
    for( servercount = 0; __get_nameserver( servercount, &dnsaddr ); servercount++ ) {
        dns_success = _dns_query( name, DNSQ_TYPE_A, dnsaddr, &ret );
        if( dns_success > 0 ) {
            return( &ret );
        }
    }
    #undef ret
    switch( -dns_success ) {
    case EINVAL:
    case ENOMEM:
    case EAGAIN:
//    case ENOMSG:
    case ESRCH:
        h_errno = TRY_AGAIN;
        break;
    case ENOENT:
        h_errno = HOST_NOT_FOUND;
        break;
    case 0:
        h_errno = NO_DATA;
        break;
    }
    return( NULL );
}

LDECL struct hostent * CNV gethostbyname( const char *name )
{
    struct hostent *ret;
//    ret = __check_hostdb( name );
//    if( ret == NULL )
        ret = __check_dns_4( name );
    return( ret );
}

_WCRTLINK void freehostent(struct hostent *he)
{
    char **h;
    free(he->h_name);
    for (h = he->h_aliases; *h; h++)
        free(*h);
    free(he->h_aliases);
    for (h = he->h_addr_list; *h; h++)
        free(*h);
    free(he->h_addr_list);
    free(he);
}
