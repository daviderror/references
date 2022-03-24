#include "tcp_server.h"

#include <iostream>

namespace tcp {
    int Tcp_server::open(size_t queue_lenght) {
        is_open_ = false;
        
        if (0 != Tcp::open(sin_server_, server_fd_, queue_lenght)) {
            return EXIT_FAILURE;
        }
        
        is_open_ = true;    

        return EXIT_SUCCESS;
    }
    
    int Tcp_server::recv(char *buffer, size_t buffer_len) {
        if (-1 == read(client_fd_, buffer, buffer_len)) {
            std::cerr << "read() failed" << std::endl;
            return (EXIT_FAILURE);
        }
        
        return EXIT_SUCCESS;
        
    }
    
    int Tcp_server::send (char *buffer, size_t buffer_len) {
        if (write(client_fd_, buffer, buffer_len)) {
            std::cerr << "write() failed" << std::endl;
        }

        return EXIT_SUCCESS;
    }
}
