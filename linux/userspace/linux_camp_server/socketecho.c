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

int main(int argc, char *argv[]) 
{
	log_info("Size of struct socket_uri %lu", (unsigned long)sizeof(struct socket_uri));

    struct socket_uri uri = {0};
    if (!uri_parse("tcp://google.com:1234", &uri)) {
    	log_err("Wrong arguments");
    	exit(EXIT_FAILURE);
    }

    if (STYPE_UNIX != uri.type && NULL != uri.host) {
    	if (!host_resolve(uri.type, uri.host, &uri.ip)) {
    		log_crit("Could not get addr for host %s", uri.host);
    		exit(EXIT_FAILURE);
    	}

    	log_warn("Converted host '%s' to addr '%s'", uri.host, inet_ntoa(uri.ip));
        free(uri.host);
        uri.host = NULL;
    }

    int sock = socket(STYPE_UNIX == uri.type ? AF_UNIX : AF_INET, 
    	              STYPE_UDP == uri.type ? SOCK_DGRAM : SOCK_STREAM, 
    	              0);
    
    struct sockaddr_in addr = {
    	.sin_family = AF_INET,
    	.sin_port = uri.port,
    	.sin_addr = uri.ip
    };
  
    return 0;
}