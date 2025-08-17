TARGET = $(lastword $(subst /, ,$(CURDIR)))
vpath %.c ..
vpath %.S ..

AS = wasm
ifeq ($(TARGET),W16)
CFLAGS = -I$(WATCOM)/h/win
TARG = -bt=WINDOWS
CF = -3 -ml -bd -zc -zw -zu
ASF = -3ps
CC = wcc
else
ifeq ($(TARGET),D16)
TARG = -bt=dos
CF = -3 -ml
ASF = -3rs
CC = wcc
else
ifeq ($(TARGET),W32)
TARG = -bt=NT_DLL
CF = -3r
ASF = -3ps -d__USE32
CC = wcc386
else
ifeq ($(TARGET),D32)
TARG = -bt=dos4g
CF = -3r
ASF = -3ps -d__USE32
CC = wcc386
else
ifeq ($(filter clean,$(MAKECMDGOALS)),)
$(error unsupported target $(TARGET))
endif
endif
endif
endif
endif
CFLAGS += -i=../include -i=h $(TARG) $(CF) -d3
ASFLAGS = $(TARG) $(ASF) -d3
LD = wlib

SOURCES = \
accept.c    gtpronam.c  inetnet.c   shutdown.c \
bind.c      gtpronum.c  inetneto.c  gethname.c \
gtscknam.c  inetntoa.c  select.c \
gtsckopt.c  gaddrinf.c  presaddr.c \
connect.c   gtsrvent.c  listen.c \
gtsrvnam.c  ntohl.c     c_errors.c \
gtsrvprt.c  ntohs.c     recv.c      socket.c \
gthstadr.c  _h_errno.c  recvfrom.c  stsckopt.c \
gthstent.c  htonl.c     _prscfg.c   recvmsg.c  \
gthstnam.c  htons.c     _resolve.c \
gtnetadr.c  inetaddr.c  fcntl.c     ioctl.c \
gtnetent.c  inetaton.c  send.c \
gtnetnam.c  inetlnof.c  sendmsg.c \
gtproent.c  inetmkad.c  sendto.c

ASM_SOURCES = \
s_fnread.S  s_close.S   s_gprnm.S   s_listen.S  s_select.S  s_snblk.S \
s_accept.S  s_connct.S  s_gscknm.S  s_recvfr.S  s_send.S    s_socket.S \
s_bind.S    s_gnblk.S   s_initnt.S  s_recv.S    s_sendto.S  vxd.S

OBJECTS = $(SOURCES:.c=.o) $(ASM_SOURCES:.S=.o)
LIB = libd2sock.lib

all: $(LIB)

$(LIB): $(OBJECTS)
	$(LD) -n $@ $^

.S.o:
	$(AS) $(ASFLAGS) -fo=$@ $<

.c.o:
	$(CC) $(CFLAGS) -fo=$@ $<

clean:
	$(RM) *.o $(LIB)
