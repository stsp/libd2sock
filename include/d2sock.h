#ifndef _D2SOCK_H_INCLUDED
#define _D2SOCK_H_INCLUDED

#include <stddef.h>

#ifdef __WINDOWS__

_WCRTLINK void            freehostent(struct hostent *he);
_WCRTLINK struct hostent  *gethostbyname_ex( const char *__name, void *arg );
_WCRTLINK int aconnect(SOCKET s);

#endif

_WCRTLINK void d2s_set_blocking_hook(int (far *hook)(void *arg));
_WCRTLINK void d2s_set_blocking_arg(int fd, void *arg);
_WCRTLINK void d2s_set_close_hook(void (far *hook)(int, void *));
_WCRTLINK void d2s_set_close_arg(int s, void *arg);
_WCRTLINK void *d2s_get_close_arg(int s);
_WCRTLINK void d2s_set_debug_hook(void (far *hook)(const char *));

#endif
