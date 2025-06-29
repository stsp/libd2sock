#ifndef CSOCK_H
#define CSOCK_H

#define LONG32 int
#define ULONG32 unsigned int
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
LONG32 __cdecl ___csock_bind(ULONG32 fd, ULONG32 addr, unsigned short port);
LONG32 __cdecl ___csock_sendto(ULONG32 fd, ULONG32 addr, unsigned short port, const void _V_FW(1) *buf, ULONG32 len, __out ULONG32 *sent);
LONG32 __cdecl ___csock_send(ULONG32 fd, const void _V_FW(1) *buf, ULONG32 len, __out ULONG32 *sent);
LONG32 __cdecl ___csock_recvfrom(ULONG32 fd, __out void _V_FW(1) *buf, ULONG32 len, __out ULONG32 *rcvd, __out ULONG32 *addr, __out unsigned short *port);
LONG32 __cdecl ___csock_recv(ULONG32 fd, __out void _V_FW(1) *buf, ULONG32 len, __out ULONG32 *rcvd);
LONG32 __cdecl ___csock_listen(ULONG32 fd, ULONG32 backlog);
LONG32 __cdecl ___csock_accept(ULONG32 fd, __out ULONG32 *afd, __out ULONG32 *addr, __out unsigned short *port);
LONG32 __cdecl ___csock_select(ULONG32 *rfds, ULONG32 *wfds, ULONG32 *efds, ULONG32 *timeout);
LONG32 __cdecl ___csock_connect(ULONG32 fd, ULONG32 addr, unsigned short port);
LONG32 __cdecl ___csock_getsockname(ULONG32 fd, __out ULONG32 *addr, __out unsigned short *port);
LONG32 __cdecl ___csock_getpeername(ULONG32 fd, __out ULONG32 *addr, __out unsigned short *port);
LONG32 __cdecl ___csock_getnblkio(ULONG32 fd, __out ULONG32 *nb);
LONG32 __cdecl ___csock_setnblkio(ULONG32 fd, __out ULONG32 nb);

LONG32 __cdecl VxdGetEntry(ULONG32 id);

#endif
