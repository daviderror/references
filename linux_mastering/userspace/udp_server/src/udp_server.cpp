#include <iostream>

#include "udp_server.h"

namespace udp {
    int Udp_server::open(void) {
        is_open_ = false;
        
        if (0 != Udp::open(server_, socket_)) {
            return EXIT_FAILURE;
        }
        
        is_open_ = true;    

        return EXIT_SUCCESS;
    }
    
    int Udp_server::recv(char *buffer, size_t buffer_len, int flags = 0) {
        if (recvfrom(socket_, buffer, buffer_len, flags, 
                    reinterpret_cast<sockaddr *>(&client_), 
                    &sockaddr_in_size) < 0) {
            std::cerr << "recvfrom failed" << std::endl;
            return (EXIT_FAILURE);
        }
        
        return EXIT_SUCCESS;
        
    }
    
    int Udp_server::send (char *buffer, size_t buffer_len, int flags = 0) {
        if (sendto(socket_, buffer, buffer_len, 
                    flags,reinterpret_cast<sockaddr *>(&client_), 
                    sockaddr_in_size) < 0) {
            std::cerr << "sendto failed" << std::endl;
        }

        return EXIT_SUCCESS;
    }
}
