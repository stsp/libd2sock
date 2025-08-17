#ifndef DEFS_H
#define DEFS_H

#ifdef __WINDOWS__
#include <stdint.h>
#include <stddef.h>
#define INET_ADDRSTRLEN 16
#define LDECL
#define CNV far pascal
#define socklen_t int
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

_WCRTLINK extern void _set_blocking_hook(int (far *hook)(void));
_WCRTLINK extern int _blocking_hook( void );
#define BCALL(r, c, b) do { \
    r = c; \
} while ((b) && (r) < 0 && __csock_errno(r) == EAGAIN && _blocking_hook() == 1)
#define BCALL_TO(r, c, s, e) do { \
    r = c; \
} while (( \
          ((e) == 0xffffffff) || \
          ((s) && (GetTickCount() < (s) + (e))) \
         ) && \
        (r) < 0 && __csock_errno(r) == EAGAIN && _blocking_hook() == 1)
#else
#define LDECL _WCRTLINK
#define CNV
#define SOCKET int
#define BCALL(r, c, b) r = c
#define BCALL_TO(r, c, s, e) r = c
#endif

#endif
