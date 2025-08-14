#ifndef DEFS_H
#define DEFS_H

#ifdef __WINDOWS__
#include <stdint.h>
#include <stddef.h>
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
#else
#define LDECL _WCRTLINK
#define CNV
#define SOCKET int
#endif

#endif
