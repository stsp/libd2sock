/* socket lib by @stsp */
/* Sybase Open Watcom Public License */

#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/* minimal getaddrinfo() */

_WCRTLINK int getaddrinfo(const char *host, const char *serv,
    const struct addrinfo *hint, struct addrinfo **res)
{
	struct addrinfo *ret = malloc(sizeof(*ret));
	struct sockaddr_in *sin = malloc(sizeof(*sin));
	struct hostent *h = gethostbyname(host);

	if (!h)
		return -1;
	ret->ai_flags = 0;
	ret->ai_family = AF_INET;
	ret->ai_socktype = SOCK_STREAM;
	ret->ai_protocol = IPPROTO_TCP;
	ret->ai_addrlen = sizeof(struct sockaddr_in);
	sin->sin_addr = *(struct in_addr *)h->h_addr;
	ret->ai_addr = (struct sockaddr *)sin;
	ret->ai_canonname = strdup(h->h_name);
	ret->ai_next = NULL;
	*res = ret;
	return 0;
}

_WCRTLINK void freeaddrinfo(struct addrinfo *res)
{
	free(res->ai_canonname);
	free(res->ai_addr);
	free(res);
}
