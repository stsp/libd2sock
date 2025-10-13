#ifndef DEFS_H
#define DEFS_H

#include <stdio.h>
#ifdef __WINDOWS__
#include <stdint.h>
#include <stddef.h>
#define INET_ADDRSTRLEN 16
#define MSG_DONTWAIT 0x40
#define LDECL
#define CNV far pascal
#define socklen_t int
#define ENOPROTOOPT WSAENOPROTOOPT
#undef h_errno
_WCRTDATA extern int h_errno;
typedef uint32_t in_addr_t;
typedef uint16_t in_port_t;
_WCRTLINK extern struct hostent  *gethostent(void);
_WCRTLINK extern void            sethostent( int __stayopen );
_WCRTLINK extern void            endhostent( void );
_WCRTLINK extern struct protoent *getprotoent( void );
_WCRTLINK extern void            setprotoent( int __stayopen );
_WCRTLINK extern void            endprotoent( void );
_WCRTLINK extern struct servent  *getservent( void );
_WCRTLINK extern void            setservent( int __stayopen );
_WCRTLINK extern void            endservent( void );
_WCRTLINK extern struct netent   *getnetent( void );
_WCRTLINK extern void            setnetent( int __stayopen );
_WCRTLINK extern void            endnetent( void );
_WCRTLINK extern void            freehostent(struct hostent *he);
_WCRTLINK extern struct hostent  *gethostbyname_ex( const char *__name, void *arg );

_WCRTLINK extern void _set_blocking_hook(int (far *hook)(void *arg));
_WCRTLINK extern int _blocking_hook( void *arg );
#define BCALL(r, c, b, a) do { \
    r = c; \
} while ((b) && (r) < 0 && __csock_errno(r) == EAGAIN && _blocking_hook(a) == 1)
#define BCALL_TO(r, c, s, e, a) do { \
    r = c; \
} while (( \
          ((e) == 0xffffffff) || \
          ((s) && (GetTickCount() < (s) + (e))) \
         ) && \
        (r) < 0 && __csock_errno(r) == EAGAIN && _blocking_hook(a) == 1)

#define __IOC(x) ((x) & 0xffff)
#define _FD_ISSET(x, y) FDIsSet(x, y)
#else
#define LDECL _WCRTLINK
#define CNV
#define SOCKET int
#define SOCKET_ERROR -1
#define INVALID_SOCKET -1
#define BCALL(r, c, b, a) r = c
#define BCALL_TO(r, c, s, e, a) r = c
#define __IOC(x) (x)
#define _FD_ISSET(x, y) FD_ISSET(x, y)
#endif

_WCRTLINK void _set_debug_hook(void (far *hook)(const char *));
_WCRTLINK void _debug_out(const char *msg);
#define _ENT() _debug_out("enter: " __FUNCTION__ "\r\n")
#define DEBUG_STR(...) { \
	char _buf[128]; \
	snprintf(_buf, sizeof(_buf), __VA_ARGS__); \
	_debug_out(_buf); \
}

void set_blk_arg(int fd, void *arg);

#endif
