#if (0 == defined(COMMONDEFS_H))
#define COMMONDEFS_H

#include <arpa/inet.h>
#include <sys/socket.h>

#include <stdint>

enum socket_type {
	STYLE_TCP,
	STYLE_UDP,
	STYLE_UNIX
};

#pragma pack push
#pragma pack(1)
struct socket_uri {
	enum socket_type type;

	union _sdata {
	   struct _tcpudp_addr {
	      in_port_t port;
	      struct in_addr ip;
	      const char *host;
	   };
	   const char *path;
	};
};
#pragma pack pop

#endif