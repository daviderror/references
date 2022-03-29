#include "uriparser.h"
#include "logging.h"
#include "macroutils.h"

#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <argp.h>

#include <stdio.h>
#include <stdlib.h>

bool host_resolve(enum socket_type kind, const char *host, struct in_addr *res)
{
    if (STYPE_UNIX == kind) {
    	return false;
    }

    struct addrinfo hint = {
        .ai_family = AF_INET	
    };

    struct addrinfo *req;

    int err = getaddrinfo(host, NULL, &hint, &req);

    if (err) {
    	log_crit("getaddrinfo for host '%s' returned %d ('%s')", host, err, gai_strerror(err));
    	return false;
    }
    
    struct sockaddr_in *tmp = (struct sockaddr_in *)(req->ai_addr);
    *res = tmp->sin_addr;
    
    freeaddrinfo(req);
    return true;
}