#include <string.h>
#include <iostream>

#include "udp.h"

namespace udp {
    Udp::Udp (sockaddr_in &udp, udp_init init, int &socket_hnd) {
        
        socket_hnd = socket(init.family, SOCK_DGRAM, 0);
        
        // exeption is neede
        if (-1 == socket_hnd){
            std::cerr << "socket failed" << std::endl;
            exit(EXIT_FAILURE);
        }
        
        memset(&udp, 0, sizeof (sockaddr_in));
        
        if (EXIT_FAILURE == set_addr_(udp.sin_addr.s_addr, init.s_addr.c_str())) {
            exit(EXIT_FAILURE);
        }
              
        set_port_(udp.sin_port, init.port);
        set_family_(udp.sin_family, init.family);
    }
    
    int Udp::open(sockaddr_in &udp_sock, int &socket_hnd) {
        if ((bind(socket_hnd,(const sockaddr *) &udp_sock, sizeof(sockaddr_in))) < 0) {
             std::cerr << "bind failed" << std::endl;
             return EXIT_FAILURE;
         }
         
        return EXIT_SUCCESS;
    }
    
    int Udp::set_addr_(uint32_t &addr, const char *c_addr){
        if (NULL == c_addr) {
            std::cerr << "IP address is empty" << std::endl;
            return EXIT_FAILURE;
        }
        
        addr = inet_addr(c_addr); 

        return EXIT_SUCCESS;
    }
}
