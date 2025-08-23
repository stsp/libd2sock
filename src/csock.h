#ifndef CSOCK_H
#define CSOCK_H

#include <stdint.h>

#define LONG32 int32_t
#define ULONG32 uint32_t
#define __out
#define _V_FW(x)

struct driver_info_rec {
    uint32_t myip;
    uint32_t netmask;
    uint32_t gateway;
    uint32_t dnsserver;
    uint32_t timeserver;
    uint16_t mtu;
    uint8_t def_ttl;
    uint8_t def_tos;
    uint16_t tcp_mss;
    uint16_t tcp_rwin;
    uint16_t debug;
    char domain[255];
};

extern struct driver_info_rec driver_info;

LONG32 __cdecl ___csock_get_version(__out ULONG32 *ver, ULONG32 len, __out struct driver_info_rec *di);
LONG32 __cdecl ___csock_open(ULONG32 proto, __out ULONG32 *fd);
LONG32 __cdecl ___csock_close(ULONG32 fd);
LONG32 __cdecl ___csock_bind(ULONG32 fd, ULONG32 addr, ULONG32 port);
LONG32 __cdecl ___csock_sendto(ULONG32 fd, ULONG32 addr, ULONG32 port, const void _V_FW(1) *buf, ULONG32 len, __out ULONG32 *sent);
LONG32 __cdecl ___csock_send(ULONG32 fd, const void _V_FW(1) *buf, ULONG32 len, __out ULONG32 *sent);
LONG32 __cdecl ___csock_recvfrom(ULONG32 fd, __out void _V_FW(1) *buf, ULONG32 len, __out ULONG32 *rcvd, __out ULONG32 *addr, __out ULONG32 *port);
LONG32 __cdecl ___csock_recv(ULONG32 fd, __out void _V_FW(1) *buf, ULONG32 len, __out ULONG32 *rcvd);
LONG32 __cdecl ___csock_listen(ULONG32 fd, ULONG32 backlog);
LONG32 __cdecl ___csock_accept(ULONG32 fd, __out ULONG32 *afd, __out ULONG32 *addr, __out ULONG32 *port);
LONG32 __cdecl ___csock_select(ULONG32 *rfds, ULONG32 *wfds, ULONG32 *efds, ULONG32 *timeout);
LONG32 __cdecl ___csock_connect(ULONG32 fd, ULONG32 addr, ULONG32 port);
LONG32 __cdecl ___csock_getsockname(ULONG32 fd, __out ULONG32 *addr, __out ULONG32 *port);
LONG32 __cdecl ___csock_getpeername(ULONG32 fd, __out ULONG32 *addr, __out ULONG32 *port);
LONG32 __cdecl ___csock_getnblkio(ULONG32 fd, __out ULONG32 *nb);
LONG32 __cdecl ___csock_setnblkio(ULONG32 fd, ULONG32 nb);
LONG32 __cdecl ___csock_fionread(ULONG32 fd, __out ULONG32 *outq);
LONG32 __cdecl ___csock_getsoerr(ULONG32 fd, __out ULONG32 *outerr);

LONG32 __cdecl VxdGetEntry(ULONG32 id);
int csock_init(void);

/* --- Defines --- */

/* Error codes, taken from sock.h from Coda's sock.vxd source */
#define CSOCK_ERR_INVALID_PARAM       0x00000100
#define CSOCK_ERR_NO_MEMORY           0x00000200
#define CSOCK_ERR_INVALID_SOCKET      0x00000300
#define CSOCK_ERR_ALREADY_BOUND       0x00000400
#define CSOCK_ERR_NOT_BOUND           0x00000500
#define CSOCK_ERR_ACCESS              0x00000600
#define CSOCK_ERR_INTERNAL            0x00000700
#define CSOCK_ERR_FD_INUSE            0x00000800
#define CSOCK_ERR_INFINITE_WAIT       0x00000900
#define CSOCK_ERR_NOT_CONNECTED       0x00000a00
#define CSOCK_ERR_WOULD_BLOCK         0x00000b00
#define CSOCK_ERR_NOT_LISTENING       0x00000c00

/* Minimum error code - used to distinguish sock.vxd errors from TDI ones. */
#define CSOCK_ERR_MIN CSOCK_ERR_INVALID_PARAM

extern int __csock_errno (int /* i_errno */);

#define MAX_FDS 32
struct per_sock {
    unsigned int nb:1;
};
extern struct per_sock psock[MAX_FDS];

#endif
