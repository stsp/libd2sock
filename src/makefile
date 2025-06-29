CC = owcc
CFLAGS = -I../include -Ih
LD = wlib

SOURCES = \
accept.c    gtpronam.c  inetnet.c   shutdown.c \
bind.c      gtpronum.c  inetneto.c \
gtscknam.c  inetntoa.c \
gtsckopt.c  gaddrinf.c \
connect.c   gtsrvent.c  listen.c \
gtsrvnam.c  ntohl.c \
gtsrvprt.c  ntohs.c     recv.c      socket.c \
gthstadr.c  _h_errno.c  recvfrom.c  stsckopt.c \
gthstent.c  htonl.c     _prscfg.c   recvmsg.c  \
gthstnam.c  htons.c     _resolve.c \
gtnetadr.c  inetaddr.c \
gtnetent.c  inetaton.c  send.c \
gtnetnam.c  inetlnof.c  sendmsg.c \
gtproent.c  inetmkad.c  sendto.c

ASM_SOURCES = \
            s_close.S   s_gprnm.S   s_listen.S  s_select.S  s_snblk.S \
s_accept.S  s_connct.S  s_gscknm.S  s_recvfr.S  s_send.S    s_socket.S \
s_bind.S    s_gnblk.S   s_initnt.S  s_recv.S    s_sendto.S  vxd.S

OBJECTS = $(SOURCES:.c=.o) $(ASM_SOURCES:.S=.o)
LIB = libcsock.a

all: $(LIB)

$(LIB): $(OBJECTS)
	$(LD) -n $@ $^

clean:
	$(RM) *.o $(LIB)
