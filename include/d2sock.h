#ifndef _D2SOCK_H_INCLUDED
#define _D2SOCK_H_INCLUDED

#include <stddef.h>

#ifdef __WINDOWS__

_WCRTLINK extern void            freehostent(struct hostent *he);
_WCRTLINK extern struct hostent  *gethostbyname_ex( const char *__name, void *arg );

#endif

_WCRTLINK extern void d2s_set_blocking_hook(int (far *hook)(void *arg));
_WCRTLINK void d2s_set_debug_hook(void (far *hook)(const char *));

#endif
