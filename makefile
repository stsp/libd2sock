CC = owcc
CFLAGS = -Ihh -Ilh -Ih
LD = wlib

SOURCES = \
accept.c    gtpronam.c  inetnet.c   shutdown.c \
bind.c      gtpronum.c  inetneto.c \
gtscknam.c  inetntoa.c \
gtsckopt.c \
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

OBJECTS = $(SOURCES:.c=.o)
LIB = libsock.a

all: $(LIB)

$(LIB): $(OBJECTS)
	$(LD) -n $@ $^

clean:
	$(RM) *.o $(LIB)
